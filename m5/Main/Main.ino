#include <M5Stack.h>
#include <WiFi.h>
#include <esp_wifi.h>
WiFiClient wifi_client;
#define MQTT_MAX_PACKET_SIZE 1024
#include <PubSubClient.h>
PubSubClient ps_client( wifi_client );

enum currentView {
  home,
  camp,
  statistics,
};

typedef struct campaign {
  String name;
  String description;
  int endTime;
  int stepGoal;
  int reward;
} campaign;

//GLOBAL VARIABLES
String user_name = "Mario";
int total_steps = 0;
int max_sec = 10000;
int remaining_sec = 6013;
const uint16_t BACKGROUNDCOLOR = 0xFFFF;
const uint16_t TEXTCOLOR = 0x0000;
const uint16_t BEANCOLOR = 0xFC9F;
int lifeleft; // value between 0 and 100 representing % of life left
int maxlife = 100;
currentView currView;
boolean campRequested = true;
boolean statsRequested = true;
boolean dead = false;



//Classes
#include "Timer.h"
#include "Pedometer.h"
#include "Bean.h"
#include "TextBox.h"
#include "TimeBar.h"
#include "View.h"
#include "CampaignsView.h"
#include "StatsView.h"

extern unsigned char logo[];

//JSON
#include <ArduinoJson.h>
StaticJsonDocument<500> JSONprofile;
StaticJsonDocument<500> JSONstep;
StaticJsonDocument<500> JSONstats;
StaticJsonDocument<1000> JSONcamps;
String stepMsg;
String profileMsg;
String statsMsg;
String campsMsg;

//MQTT Variables
uint8_t guestMacAddress[6] = {0x8C, 0xB8, 0xA4, 0x8B, 0x38, 0x70};
const char* ssid = "VM5649012"; // Set name of Wifi Network
const char* password = "cr5jdMktTnp7";
const char* MQTT_clientname = "m5stack"; //Useless.
const char* server = "broker.mqttdashboard.com";
const int port = 1883;

const char* MQTT_sub_topic = "doordie_web"; // Only topic used for message reading
const char* mainTopic = "doordie_web"; // Topic used for all other communication
const char* stepTopic = "doordie_steps"; // Topic reserved for step updating


//Other Variables
Pedometer step_counter;
Timer pullTimer(5000, true);
String showMe;
View homeScreen;
CampaignsView campaignsView;
StatsView statsView;

void setup()
{
  M5.begin(); M5.Power.begin(); Wire.begin(); //Start M5
  Serial.begin(115200); delay(10); //Start Serial (for debugging)
  M5.Lcd.setTextSize(1);
  m5.Lcd.setTextColor(BACKGROUNDCOLOR);
  M5.Lcd.drawBitmap(0, 0, 320, 240, (uint16_t *)logo);
  setupWifiWithPassword();
  step_counter.setup();
  setupJSON();
  setupMQTT();
  currView = home;
  M5.Lcd.setCursor(140, 220); M5.Lcd.print("Ready!");
  delay(1000);
  M5.Lcd.fillScreen(BACKGROUNDCOLOR);

} //setup

void loop()
{
  //MQTT PUBLISHING
  if (!ps_client.connected()) {
    reconnect();
  }
  ps_client.loop();

  if (!dead) {
    //Send Pull Profile request to server every X milliseconds
    if (pullTimer.isReady()) {
      pullProfile();
      pullTimer.reset();
    }

    //If a step is taken, perform onStepTaken(), i.e. increase local step counter and publish step on MQTT
    if (step_counter.loop()) {
      onStepTaken();
    }

    lifeleft = (remaining_sec * maxlife) / max_sec;
    if (currView == home) {
      homeScreen.loop();
    } else if (currView == camp) {
      if (!campRequested) {
        publishMessage(campsMsg, mainTopic);
        campRequested = true;
        campaignsView.setReady(false);
      }
      campaignsView.loop();
    } else if (currView == statistics) {
      if (!statsRequested) {
        publishMessage("Give me stats!", mainTopic);
        statsRequested = true;
        statsView.setReady(false);
      }
      statsView.loop();
    }
    if (remaining_sec == 0) {
      dead = true;
      Bean bean;
      bean.drawdead();
    }
  }//dead
} //loop

//MQTT BROKER FUNCTIONS
void publishMessage( String message , const char* topic)
{
  if ( ps_client.connected() ) {
    // Make sure the message isn't blank.
    if ( message.length() > 0 ) {

      // Convert to char array
      char msg[ message.length() + 1];
      message.toCharArray( msg, message.length() + 1 );

      // Send
      ps_client.publish( topic, msg );
    }
  } else {
    M5.Lcd.println("Can't publish message: Not connected to MQTT :( ");
  }
}

void callback(char* topic, byte* payload, unsigned int length)
{
  String in_str = "";

  // Copy chars to a String for convenience.
  for (int i = 0; i < length; i++) {
    in_str += (char)payload[i];
  }
  Serial.println(in_str);

  if (in_str.equals("Give me stats!")) { //This would be replaced by a JSON deserialization of a real message from the database
    statsView.setupStats(37000, 70000, 10000);
    statsView.setReady(true);
  }

  DynamicJsonDocument JSONin(2048); //intialise JSON OBJECT, allocates statically from stack, can also use heap variant if not enough space
  deserializeJson(JSONin, in_str);
  if ( JSONin["type"].as<String>() == "push profile" && JSONin["user_name"] == user_name) {
    total_steps = JSONin["total_steps"];
    remaining_sec = JSONin["remaining_sec"];
  }

  if ( JSONin["type"].as<String>() == "push user challenges" && JSONin["user_name"] == user_name) {
    campaignsView.clearCampaigns();
    JsonArray challenges = JSONin["challenges"];
    Serial.println(challenges.size());
    for (JsonObject challenge : challenges) {
      String challengeName = challenge["challenge_name"];
      String description = challenge["description"];
      int endTime = challenge["end_time"];
      int stepGoal = challenge["step_goal"];
      int reward = challenge["reward"];
      Serial.println(challengeName);
      campaignsView.addCampaign(challengeName, description, endTime, stepGoal, reward);
    }
    campaignsView.setReady(true);
  }
}

void setupJSON()
{
  JSONstep["type"] = "push step";
  JSONstep["user_name"] = user_name;
  serializeJson(JSONstep, stepMsg);
  JSONprofile["type"] = "pull profile";
  JSONprofile["user_name"] = user_name;
  serializeJson(JSONprofile, profileMsg);
  JSONprofile["type"] = "pull user challenges";
  JSONprofile["user_name"] = user_name;
  serializeJson(JSONprofile, campsMsg);
  
}

void pullProfile()
{
  publishMessage(profileMsg, mainTopic);
}

void onStepTaken()
{
  total_steps++;
  publishMessage(stepMsg, stepTopic );
}

/* ************************************************************************************
 *  ***********************************************************************************
 *  ***********************************************************************************
    END OF CODE - DON'T CHANGE BEYOND THIS POINT
 *  ***********************************************************************************
 *  ***********************************************************************************
 * *************************************************************************************/


void setupMQTT()
{
  ps_client.setServer(server, port);
  ps_client.setCallback(callback);
}

void setupWifi()
{
  Serial.println("Original MAC address: " + String(WiFi.macAddress()));
  esp_base_mac_addr_set(guestMacAddress);
  Serial.println("Borrowed MAC address: " + String(WiFi.macAddress()));

  Serial.println("Connecting to network: " + String(ssid));
  WiFi.begin(ssid );
  while (WiFi.status() != WL_CONNECTED) delay(5000);
  M5.Lcd.println("IP address allocated: " + String(WiFi.localIP()));
}

void setupWifiWithPassword()
{
  Serial.println("Original MAC address: " + String(WiFi.macAddress()));
  //esp_base_mac_addr_set(guestMacAddress); Commented out to use original M5 MAC address
  Serial.println("Borrowed MAC address: " + String(WiFi.macAddress()));
  Serial.println("Connecting to network: " + String(ssid));
  WiFi.begin(ssid, password);
  int dotsAmount = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.drawBitmap(0, 0, 320, 240, (uint16_t *)logo);
    M5.Lcd.setCursor(140, 200); M5.Lcd.print("CONNECTING ");
    for (int i = 0; i < dotsAmount; i++) {
      M5.Lcd.print(". ");
    }
    dotsAmount = (dotsAmount + 1) % 4;
  }
  Serial.println("IP address allocated: " + String(WiFi.localIP()));

}

void reconnect()
{
  // Loop until we're reconnected
  while (!ps_client.connected()) {
    M5.Lcd.setCursor(0, 60);
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // Sometimes a connection with HiveMQ is refused
    // because an old Client ID is not erased.  So to
    // get around this, we just generate new ID's
    // every time we need to reconnect.
    String new_id = generateID();

    Serial.print("connecting with ID ");
    Serial.println( new_id );

    char id_array[ (int)new_id.length() ];
    new_id.toCharArray(id_array, sizeof( id_array ) );

    if (ps_client.connect( id_array ) ) {
      Serial.println("connected");

      // Once connected, publish an announcement...
      ps_client.publish( stepTopic, "reconnected");
      // ... and resubscribe
      ps_client.subscribe( MQTT_sub_topic );
    } else {
      M5.Lcd.println(" - Coudn't connect to HiveMQ :(");
      M5.Lcd.println("   Trying again.");
      Serial.print("failed, rc=");
      Serial.print(ps_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  showMe = " - Success!  Connected to HiveMQ\n\n";
}

String generateID()
{
  String id_str = MQTT_clientname;
  id_str += random(0, 9999);
  return id_str;
}
