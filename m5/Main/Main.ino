#include <M5Stack.h>
#include <WiFi.h>
#include <esp_wifi.h>
WiFiClient wifi_client;

// PubSubClient external library.
#include <PubSubClient.h>
PubSubClient ps_client( wifi_client );

//Local Libraries
#include "Timer.h"
#include "Pedometer.h"

//JSON
#include <ArduinoJson.h>
StaticJsonDocument<500> JSONin; //intialise JSON OBJECT, allocates statically from stack, can also use heap variant if not enough space
StaticJsonDocument<500> JSONprofile;
StaticJsonDocument<500> JSONstep;
char requestDefault[] = "{\"user_type\":\"user\",\"user_id\":\"1234\",\"user_name\":\"User1\",\"total_steps\":\"2200\",\"remaining_sec\":\"2200\",\"current_time\":\"2020-02-30T08:35:30.0108Z\"}";
String stepMsg;
String profileMsg;

//mqtt client setup 
uint8_t guestMacAddress[6] = {0x8C, 0xB8, 0xA4, 0x8B, 0x38, 0x70};
const char* ssid = "VM5649012"; // Set name of Wifi Network
const char* password = "cr5jdMktTnp7";   
const char* MQTT_clientname = "m5stack"; // Make up a short name
const char* MQTT_sub_topic = "doordie_web"; // pub/sub topics
const char* mainTopic = "doordie_web"; // You might want to create your own
const char* stepTopic = "doordie_steps"; // You might want to create your own
const uint16_t BACKGROUNDCOLOR = 0x0000;

const char* server = "broker.mqttdashboard.com";
const int port = 1883;

//DoOrDie Variables
String user_name = "Mario";
int total_steps = 0;
int max_sec = 10000;
int remaining_sec = 6013;
Pedometer step_counter;
Timer pullTimer(5000, true);
String showMe;
Timer drawTimer(100,true);

void setup()
{
  M5.begin();
  M5.Power.begin();
  Wire.begin();

  Serial.begin(115200);
  delay(10);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("*** RESET ***\n");
  M5.Lcd.println("Connecting...");
  setupWifiWithPassword();
  //setupWifi();
  step_counter.setup();
  setupJSON();
  setupMQTT();
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

  drawTimeBar(false);
  if(drawTimer.isReady()) {
    drawBean();
    drawTimer.reset();
  }
  
  M5.Lcd.setCursor(0, 200); M5.Lcd.println(showMe); //showMe is the string that gets updated with what we want on the screen at any time
  //M5.Lcd.setCursor(0, 0); M5.Lcd.printf("Time: %10d", remaining_sec);
  M5.Lcd.setCursor(240, 0); M5.Lcd.printf("Steps: %6d", total_steps);
 
} //loop

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
    drawTimeBar(true);  
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

void drawTimeBar(bool clearBackground)
{
  int x = 0;
  int y = 0;
  int w = 100;
  int h = 10;
  uint8_t val = (remaining_sec * 100) / max_sec;
  if(clearBackground){
    M5.Lcd.fillRect(x+1,y+1,w,h,BACKGROUNDCOLOR);
  }
    
  M5.Lcd.progressBar(x+1,y+1,w,h, val);
  M5.Lcd.drawRect(x,y,w+2,h+2,0xFFFF);
}

void drawBean() 
{
  int eyeWidth = 30;
  int r = 60;
  int x = M5.Lcd.width()/2;
  int y = M5.Lcd.height()/2;
  M5.Lcd.fillCircle(x, y, r, 0xFC9F);
  drawEye(x-eyeWidth,y-10,20);
  drawEye(x+eyeWidth,y-10,20);
}

void drawEye(int x, int y, int r)
{
  M5.Lcd.fillCircle(x, y, r, 0xFFFF);
  M5.Lcd.fillCircle(x,y+(r/2),r/2,0x0000);
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
