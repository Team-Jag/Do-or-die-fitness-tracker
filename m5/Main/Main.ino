#include <M5Stack.h>
#include <WiFi.h>
#include <esp_wifi.h>
WiFiClient wifi_client;

// PubSubClient external library.
#include <PubSubClient.h>
PubSubClient ps_client( wifi_client );

#include "Timer.h"
#include "Pedometer.h"

//JSON
#include <ArduinoJson.h>
StaticJsonDocument<500> doc; //intialise JSON OBJECT, allocates statically from stack, can also use heap variant if not enough space
char requestDefault[] = "{\"user_type\":\"user\",\"user_id\":\"1234\",\"user_name\":\"User1\",\"total_steps\":\"2200\",\"remaining_sec\":\"2200\",\"current_time\":\"2020-02-30T08:35:30.0108Z\"}";
String json_status;

//DoOrDie Variables
String stack_id = "stack1";
int total_steps = 0;
int defaultTime = 1000;
Pedometer step_counter;

//mqtt client setup 
uint8_t guestMacAddress[6] = {0x8C, 0xB8, 0xA4, 0x8B, 0x38, 0x70};

const char* ssid = "VM5649012"; // Set name of Wifi Network
const char* password = "cr5jdMktTnp7";   

const char* MQTT_clientname = "m5stack"; // Make up a short name
const char* MQTT_sub_topic = "doordie_steps"; // pub/sub topics
const char* MQTT_pub_topic = "doordie_steps"; // You might want to create your own

const char* server = "broker.mqttdashboard.com";
const int port = 1883;

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
  setupMQTT();
  M5.Lcd.println("SETUP COMPLETE\n");
  delay(3000);
  M5.Lcd.fillScreen(BLACK);
  
  testingStuff();
} //END OF SETUP

void loop()
{
  if(step_counter.loop()) {
    total_steps++; // we don't need this, just send request type
    sendRequest("push step"); //each time we update step count we send a request of global total steps
  }

   //MQTT PUBLISHING
   if (!ps_client.connected()) {
     reconnect();
   }
   ps_client.loop();
   M5.Lcd.setCursor(200, 0); M5.Lcd.printf("Steps: %6d", total_steps);
   M5.Lcd.setCursor(0, 60);
     if( M5.Lcd.getCursorY() > M5.Lcd.height() ) {
    M5.Lcd.fillScreen( BLACK );
    M5.Lcd.setCursor( 0, 10 );
  }
} //END OF MAIN LOOP

void testingStuff()
{
  //test JSON
  DeserializationError error = deserializeJson(doc, requestDefault); //make a valid JSON STRING into a json tree object, do this on recieving request
  //serializeJson(doc, "validjsonobject") //this is the inverse, and makes a string from JSON TREE OBJECT do this before sending request
  
  if (error) {
    //M5.Lcd.print("deserializeJson() failure: \n");
    json_status = "deserializeJson failed, invalidJSon\n";
    M5.Lcd.print(error.c_str());  
  } else {
    json_status = "JSON fine\n";
    M5.Lcd.print("JSON fine\n");  
  }
}

void sendRequest(String type)
{
  //we have a json object, updated from default request
  //updateJSON(); to update relevent fields ie time and stepcount, timestamps etc
  //serializeJson into a string
  //send through broker
  String request_type;
  //{
    //"type": "push step",
    //"user_id": "1"
  //}
  
  if (type == "push step") {
      String new_string = "{\"type\":\"push step\", \"user_id\":\"1\"}"; //HACK
      //new_string += millis();
      publishMessage( new_string );
  }
}

//MQTT BROKER FUNCTIONS
void publishMessage( String message )
{

  if( ps_client.connected() ) {
    // Make sure the message isn't blank.
    if( message.length() > 0 ) {

      // Convert to char array
      char msg[ message.length()+1];
      message.toCharArray( msg, message.length()+1 );

      //M5.Lcd.println( message );

      // Send
      ps_client.publish( MQTT_pub_topic, msg );
    }

  } else {
    Serial.println("Can't publish message: Not connected to MQTT :( ");
  }
}

void callback(char* topic, byte* payload, unsigned int length)
{
  //this is listener, watch on network
  M5.Lcd.setTextColor( WHITE );
  m5.Lcd.setCursor(0,90);
  M5.Lcd.print("Message arrived [");
  M5.Lcd.print(topic);
  M5.Lcd.print("] ");

  String in_str = "";

  // Copy chars to a String for convenience.
  // Also prints to USB serial for debugging
  for (int i=0;i<length;i++) {
    in_str += (char)payload[i];
  }
  M5.Lcd.println();
  M5.Lcd.print(" << Rx: " );
  M5.Lcd.println( in_str );
}

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
      ps_client.publish( MQTT_pub_topic, "reconnected");
      // ... and resubscribe
      M5.Lcd.println(ps_client.subscribe( MQTT_sub_topic ));
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
  M5.Lcd.println(" - Success!  Connected to HiveMQ\n\n");
}

String generateID()
{
  String id_str = MQTT_clientname;
  id_str += random(0,9999);
  return id_str;
}
