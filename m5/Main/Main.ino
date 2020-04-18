#include <M5Stack.h>
#include <WiFi.h>
#include <esp_wifi.h>
WiFiClient wifi_client;
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
}campaign;

//GLOBAL VARIABLES
String user_name = "Mario";
int total_steps = 0;
int max_sec = 10000;
int remaining_sec = 6013;
const uint16_t BACKGROUNDCOLOR = 0x0000;
const uint16_t BEANCOLOR = 0xFC9F;
int lifeleft; // value between 0 and 100 representing % of life left 
currentView currView;



//Classes
#include "Timer.h"
#include "Pedometer.h"
#include "Bean.h"
#include "TextBox.h"
#include "TimeBar.h"
#include "View.h"
#include "CampaignsView.h"



//JSON
#include <ArduinoJson.h>
StaticJsonDocument<500> JSONin; //intialise JSON OBJECT, allocates statically from stack, can also use heap variant if not enough space
StaticJsonDocument<500> JSONprofile;
StaticJsonDocument<500> JSONstep;
String stepMsg;
String profileMsg;

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
campaign **campaigns;
CampaignsView campaignsView;

void setup()
{
  M5.begin(); M5.Power.begin(); Wire.begin(); //Start M5
  Serial.begin(115200); delay(10); //Start Serial (for debugging)
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("*** RESET ***\n");
  M5.Lcd.println("Connecting...");
  setupWifiWithPassword();
  step_counter.setup();
  setupJSON();
  setupMQTT();
  currView = home;
  /*getCampaigns(3);
  campaignsView = CampaignsView(campaigns,3);*/
  M5.Lcd.println("SETUP COMPLETE\n");
  delay(3000);
  M5.Lcd.fillScreen(BLACK);
} //setup

void loop()
{
   //MQTT PUBLISHING
   if (!ps_client.connected()) {
     reconnect();
   }
   ps_client.loop();

  //Send Pull Profile request to server every X milliseconds 
  if(pullTimer.isReady()) {
    pullProfile();
    pullTimer.reset();
  }

  //If a step is taken, perform onStepTaken(), i.e. increase local step counter and publish step on MQTT
  if(step_counter.loop()) {
    onStepTaken();
  }

  lifeleft = (remaining_sec * 100) / max_sec;
  if(currView==home) {
    homeScreen.loop();
  } else if (currView==camp) {
    /*campaignsView.loop();*/
  }
 
} //loop

void getCampaigns(int campaignsAmount) {
  campaigns = (campaign **)malloc(campaignsAmount*sizeof(campaign *));
  //This would happen during the callback
  campaigns[0] = addCampaign("Campaign One", "This is your first campaign, congratulations !!");
  campaigns[1] = addCampaign("Run to Stop COVID19", "Campaign sponsored by COOLCOMPANY&CO ");
  campaigns[2] = addCampaign("Fun Campaign Woop Woop", "This campaign is a very fun, you'll love it! ");
}

campaign* addCampaign(String name, String description) {
  campaign *c;
  c = (campaign *)malloc(sizeof(campaign));
  c->name = name;
  c->description = description;
  return c;
}

//MQTT BROKER FUNCTIONS
void publishMessage( String message , const char* topic)
{
  if( ps_client.connected() ) {
    // Make sure the message isn't blank.
    if( message.length() > 0 ) {

      // Convert to char array
      char msg[ message.length()+1];
      message.toCharArray( msg, message.length()+1 );

      // Send
      ps_client.publish( topic, msg );
    }
  } else {
    M5.Lcd.println("Can't publish message: Not connected to MQTT :( ");
  }
}

void callback(char* topic, byte* payload, unsigned int length)
{
  M5.Lcd.fillScreen(0x0000);
  String in_str = "";

  // Copy chars to a String for convenience.
  for (int i=0;i<length;i++) {
    in_str += (char)payload[i];
  }
  Serial.println(in_str);

  showMe = topic;
  showMe += ":\n";
  showMe += in_str;

  deserializeJson(JSONin, in_str);
  if ( JSONin["type"].as<String>() == "push profile" && JSONin["user_name"] == user_name) {
    total_steps = JSONin["total_steps"];
    remaining_sec = JSONin["remaining_sec"];
  }
}

void setupJSON() 
{
  JSONstep["type"]="push step";
  JSONstep["user_name"]=user_name;
  serializeJson(JSONstep, stepMsg);
  JSONprofile["type"]="pull profile";
  JSONprofile["user_name"]=user_name;
  serializeJson(JSONprofile, profileMsg);
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
 *  END OF CODE - DON'T CHANGE BEYOND THIS POINT
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
    M5.Lcd.println("Original MAC address: " + String(WiFi.macAddress()));
    //esp_base_mac_addr_set(guestMacAddress); Commented out to use original M5 MAC address
    M5.Lcd.println("Borrowed MAC address: " + String(WiFi.macAddress()));

    M5.Lcd.println("Connecting to network: " + String(ssid));
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      M5.Lcd.println("CONNECTING...");
    }
    M5.Lcd.println("IP address allocated: " + String(WiFi.localIP()));

}

void reconnect()
{
  // Loop until we're reconnected
  while (!ps_client.connected()) {
    M5.Lcd.setCursor(0,60);
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
  id_str += random(0,9999);
  return id_str;
}
