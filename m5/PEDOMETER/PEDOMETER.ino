/* MPU9250 Basic Example Code
 by: Kris Winer
 date: April 1, 2014
 license: Beerware - Use this code however you'd like. If you
 find it useful you can buy me a beer some time.
 Modified by Brent Wilkins July 19, 2016
 */
#include <ArduinoJson.h>
#include <M5Stack.h>
#include "utility/MPU9250.h"
#include "utility/quaternionFilters.h"

#include <WiFi.h>
#include <esp_wifi.h>
WiFiClient wifi_client;

// PubSubClient external library.
#include <PubSubClient.h>
PubSubClient ps_client( wifi_client );

#include "Timer.h"

#define processing_out false
#define AHRS true         // Set to false for basic data read
#define SerialDebug true  // Set to true to get Serial output for debugging
#define LCD
#define ELEMENTS 20

MPU9250 IMU;
// Kalman kalmanX, kalmanY, kalmanZ; // Create the Kalman instances

//JSON STUFF
StaticJsonDocument<500> doc; //intialise JSON OBJECT, allocates statically from stack, can also use heap variant if not enough space
char requestDefault[] = "{\"user_type\":\"user\",\"user_id\":\"1234\",\"user_name\":\"User1\",\"total_steps\":\"2200\",\"remaining_sec\":\"2200\",\"current_time\":\"2020-02-30T08:35:30.0108Z\"}";

//setup globals for step calculations
int total_steps = 0; //this is the key one which we send in request
int curr_z;
int curr_x;
int curr_y;
int sum;
int readings_array[20]; //contains elements
String json_status;
float moving_average = 0; //sum of all elements divided by ELEMENTS
bool step_flag = false;

//mqtt client setup 
uint8_t guestMacAddress[6] = {0x8C, 0xB8, 0xA4, 0x8B, 0x38, 0x70};

const char* ssid = "UoB Guest";                 // Set name of Wifi Network
const char* password = "cr5jdMktTnp7";   


const char* MQTT_clientname = "m5stack"; // Make up a short name
const char* MQTT_sub_topic = "doordie_m5"; // pub/sub topics
const char* MQTT_pub_topic = "doordie_m5"; // You might want to create your own

const char* server = "broker.mqttdashboard.com";
const int port = 1883;

Timer publishing_timer(2000);

//global time LEFT FOR LIFE
int defaultTime = 1000;

void setup() {
  M5.begin();
  M5.Power.begin();
  Wire.begin();

  Serial.begin(115200);
    delay(10);
    Serial.println("*** RESET ***\n");
   //mqtt stuff here
  M5.Lcd.println("Reset, connecting...");
  //setupWifiWithPassword();
  setupWifi();
  setupMQTT();
  M5.Lcd.println("SETUP COMPLETE\n");
  
  screenSetup();
  testingStuff();
  //userSetup();
  
 
} //END OF SETUP

void loop() {
  // If intPin goes high, all data registers have new data
  // On interrupt, check if data ready interrupt
  if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {  
    readGyro();
  } // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)

  // Must be called before updating quaternions!
  IMU.updateTime();

  //info about sensor itself and x/y rotation alignment
  //MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
  MahonyQuaternionUpdate(IMU.ax, IMU.ay, IMU.az, IMU.gx*DEG_TO_RAD,
                         IMU.gy*DEG_TO_RAD, IMU.gz*DEG_TO_RAD, IMU.my,
                         IMU.mx, IMU.mz, IMU.deltat);

  if (!AHRS)
  {
    IMU.delt_t = millis() - IMU.count;
    if (IMU.delt_t > 500)
    {
      if(SerialDebug)
      {
        printValues();
      }

#ifdef LCD
     setupLCD();
#endif // LCD

      IMU.count = millis();
      // digitalWrite(myLed, !digitalRead(myLed));  // toggle led
    } // if (IMU.delt_t > 500)
  } // if (!AHRS)
  else
  {
    // Serial print and/or display at 0.5 s rate independent of data rates
    IMU.delt_t = millis() - IMU.count;

    // update LCD once per half-second independent of read rate
    // if (IMU.delt_t > 500)
    if (IMU.delt_t > 100)
    {
      if(SerialDebug)
      {
        debugInfo();
      }

//true north correction
// http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
// which has additional links.
      IMU.yaw   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ() *
                    *(getQ()+3)), *getQ() * *getQ() + *(getQ()+1) * *(getQ()+1)
                    - *(getQ()+2) * *(getQ()+2) - *(getQ()+3) * *(getQ()+3));
      IMU.pitch = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ() *
                    *(getQ()+2)));
      IMU.roll  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2) *
                    *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1) * *(getQ()+1)
                    - *(getQ()+2) * *(getQ()+2) + *(getQ()+3) * *(getQ()+3));
      IMU.pitch *= RAD_TO_DEG;
      IMU.yaw   *= RAD_TO_DEG;
      // Declination of SparkFun Electronics (40°05'26.6"N 105°11'05.9"W) is
      // 	8° 30' E  ± 0° 21' (or 8.5°) on 2016-07-19
      // - http://www.ngdc.noaa.gov/geomag-web/#declination
      IMU.yaw   -= 8.5;
      IMU.roll  *= RAD_TO_DEG;

      if(SerialDebug)
      {
        yawPitchRollDebug();
      }

#ifdef LCD
      // M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setTextFont(2);

      M5.Lcd.setCursor(0, 0); M5.Lcd.print("     x       y       z ");
      M5.Lcd.setCursor(0,  24);
      M5.Lcd.printf("% 6d  % 6d  % 6d     mg   \r\n",  (int)(1000*IMU.ax), (int)(1000*IMU.ay), (int)(1000*IMU.az)); 
      M5.Lcd.setCursor(0,  44);
      M5.Lcd.printf("% 6d  % 6d  % 6d      o/s  \r\n", (int)(IMU.gx), (int)(IMU.gy), (int)(IMU.gz)); // this is accelration remains constant unless moving, WE NEED THIS ONE
      M5.Lcd.setCursor(0,  64);
      M5.Lcd.printf("% 6d  % 6d  % 6d     mG    \r\n",  (int)(IMU.mx), (int)(IMU.my), (int)(IMU.mz));
  
      M5.Lcd.setCursor(0,  100);
      M5.Lcd.printf("  yaw: % 5.2f    pitch: % 5.2f    roll: % 5.2f   \r\n",(IMU.yaw), (IMU.pitch), (IMU.roll));

      //info about sample rate
      // M5.Lcd.setCursor(0, 60);
      // M5.Lcd.printf("yaw:%6.2f   pitch:%6.2f   roll:%6.2f  ypr \r\n",(IMU.yaw), (IMU.pitch), (IMU.roll));
      M5.Lcd.setCursor(12, 144); 
      M5.Lcd.print("rt: ");
      M5.Lcd.print((float) IMU.sumCount / IMU.sum, 2);
      M5.Lcd.print(" Hz");

      //MQTT PUBLISHING
      

      //UPDATE STEPS HERE
      updateSteps();
      if (!ps_client.connected()) {
        M5.Lcd.println("Reconnecting...");
        reconnect();
      }
      M5.Lcd.printf(" total steps so far %d\n", total_steps);
      
#endif // LCD

      IMU.count = millis();
      IMU.sumCount = 0;
      IMU.sum = 0;

#if(processing_out)
      Serial.print(((IMU.yaw)));    Serial.print(";");
      Serial.print(((IMU.pitch))); Serial.print(";");
      Serial.print(((IMU.roll)));   Serial.print(";");
      Serial.print(26.5);    Serial.print(";");
      Serial.print(0.01);    Serial.print(";");
      Serial.print(0.02);    Serial.println();
#endif
    } // if (IMU.delt_t > 500)
  } // if (AHRS)
} //END OF MAIN LOOP

void testingStuff() {
   //test printing
  //M5.Lcd.print("TESTING FUNCTION CALL");
 
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

void userSetup() {
  //when first starting up, send request to shiftr to recieve user data
  //populate the class with info including global steps/challenges etc
  //recieveRequest()
  M5.Lcd.print("Setting up user...");
}

void updateJSON() {
  //format json object before sending with info from the stepcounter ie step incrementations
  
}

void sendRequest() {
  //we have a json object, updated from default request
  //updateJSON(); to update relevent fields ie time and stepcount, timestamps etc
  //serializeJson into a string
  //send through broker
  M5.Lcd.print("\nUPDATED GLOBAL STEPS\n");
  if (publishing_timer.isReady()) {
    String new_string = requestDefault;
    new_string += millis();
    publishMessage( new_string );
    publishing_timer.reset();  
  }
}

void watchBroker() {
  //watch shiftr for request pertaining to this device, or whenever it is updated
  //if (newRequest), recieve request
  //if shiftr has watchdog this is fine
}

void recieveRequest() {
  //recieve json on startup
  //recieve just a normal escaped string
  //deserialize it with DeserializeJson to see if parsed fine ie not malformed request
  //run tests make sure all fields are there
  //update globals ie current user name, state, etc
  //return
}

void calculateTime() {
  //time calculation algorithm here
  //base on time
}

//actual pedometer, subject to change
void updateSteps() {
      curr_x=IMU.gx;
      curr_y=IMU.gy;
      curr_z=IMU.gz;

      if (curr_x < 0) {
        curr_x *= -1;  
      }

      if (curr_y < 0) {
        curr_y *= -1;  
      }

      if (curr_z < 0) {
        curr_z *= -1;  
      }
      
      sum = curr_x+curr_y+curr_z;

      //if we are not currently in a "step", but goes outside threshold
      if ((sum >= 350 || sum < -350) && step_flag == false) {
        step_flag = true;
        total_steps++;
        sendRequest(); //each time we update step count we send a request of global total steps
      }

      if ((sum < 350 && sum > -350) && step_flag == true) {
          step_flag = false;  
      }
}

//MQTT BROKER FUNCTIONS

void publishMessage( String message ) {

  if( ps_client.connected() ) {

    // Make sure the message isn't blank.
    if( message.length() > 0 ) {

      // Convert to char array
      char msg[ message.length() ];
      message.toCharArray( msg, message.length() );

      //M5.Lcd.println( message );

      // Send
      ps_client.publish( MQTT_pub_topic, msg );
    }

  } else {
    Serial.println("Can't publish message: Not connected to MQTT :( ");

  }


}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String in_str = "";

  // Copy chars to a String for convenience.
  // Also prints to USB serial for debugging
  for (int i=0;i<length;i++) {
    in_str += (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //M5.Lcd.print(" << Rx: " );
  //M5.Lcd.println( in_str );


}

void setupMQTT() {
    ps_client.setServer(server, port);
    ps_client.setCallback(callback);
}

void setupWifi() {

    byte mac[6];
    Serial.println("Original MAC address: " + String(WiFi.macAddress()));
    esp_base_mac_addr_set(guestMacAddress);
    Serial.println("Borrowed MAC address: " + String(WiFi.macAddress()));

    Serial.println("Connecting to network: " + String(ssid));
    WiFi.begin(ssid );
    while (WiFi.status() != WL_CONNECTED) delay(5000);
    M5.Lcd.println("IP address allocated: " + String(WiFi.localIP()));
}

void setupWifiWithPassword( ) {

    byte mac[6];
    Serial.println("Original MAC address: " + String(WiFi.macAddress()));
    esp_base_mac_addr_set(guestMacAddress); //HACK - USE PHONE MAC WHEN CONNECTED
    M5.Lcd.println("Borrowed MAC address: " + String(WiFi.macAddress()));

    M5.Lcd.println("Connecting to network: " + String(ssid));
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      M5.Lcd.println("CONNECTING...");
    }
    M5.Lcd.println("IP address allocated: " + String(WiFi.localIP()));

}

void reconnect() {

  // Loop until we're reconnected
  while (!ps_client.connected()) {

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
  M5.Lcd.println(" - Success!  Connected to HiveMQ\n\n");
}

String generateID() {

  String id_str = MQTT_clientname;
  id_str += random(0,9999);

  return id_str;
}

//END OF MQTT, NOW IT'S THE EXAMPLE CODE STUFF BELOW
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  M5.Lcd.print("MESSAGE RECIEVED\n");
}

//example functions
void screenSetup() {
  
  // if (c == 0x71) // WHO_AM_I should always be 0x68
  {
    Serial.println("MPU9250 is online...");

    // Start by performing self test and reporting values
    IMU.MPU9250SelfTest(IMU.SelfTest);
    Serial.print("x-axis self test: acceleration trim within : ");
    Serial.print(IMU.SelfTest[0],1); Serial.println("% of factory value");
    Serial.print("y-axis self test: acceleration trim within : ");
    Serial.print(IMU.SelfTest[1],1); Serial.println("% of factory value");
    Serial.print("z-axis self test: acceleration trim within : ");
    Serial.print(IMU.SelfTest[2],1); Serial.println("% of factory value");
    Serial.print("x-axis self test: gyration trim within : ");
    Serial.print(IMU.SelfTest[3],1); Serial.println("% of factory value");
    Serial.print("y-axis self test: gyration trim within : ");
    Serial.print(IMU.SelfTest[4],1); Serial.println("% of factory value");
    Serial.print("z-axis self test: gyration trim within : ");
    Serial.print(IMU.SelfTest[5],1); Serial.println("% of factory value");

    // Calibrate gyro and accelerometers, load biases in bias registers
    IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);

#ifdef LCD
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(0, 0); M5.Lcd.print("MPU9250 bias");
    M5.Lcd.setCursor(0, 16); M5.Lcd.print(" x   y   z  ");

    M5.Lcd.setCursor(0,  32); M5.Lcd.print((int)(1000*IMU.accelBias[0]));
    M5.Lcd.setCursor(32, 32); M5.Lcd.print((int)(1000*IMU.accelBias[1]));
    M5.Lcd.setCursor(64, 32); M5.Lcd.print((int)(1000*IMU.accelBias[2]));
    M5.Lcd.setCursor(96, 32); M5.Lcd.print("mg");

    M5.Lcd.setCursor(0,  48); M5.Lcd.print(IMU.gyroBias[0], 1);
    M5.Lcd.setCursor(32, 48); M5.Lcd.print(IMU.gyroBias[1], 1);
    M5.Lcd.setCursor(64, 48); M5.Lcd.print(IMU.gyroBias[2], 1);
    M5.Lcd.setCursor(96, 48); M5.Lcd.print("o/s");
    delay(1000);
#endif // LCD

    IMU.initMPU9250();
    // Initialize device for active mode read of acclerometer, gyroscope, and
    // temperature
    Serial.println("MPU9250 initialized for active data mode....");

    // Read the WHO_AM_I register of the magnetometer, this is a good test of
    // communication
    byte d = IMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
    Serial.print("AK8963 "); Serial.print("I AM "); Serial.print(d, HEX);
    Serial.print(" I should be "); Serial.println(0x48, HEX);

#ifdef LCD
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(20,0); M5.Lcd.print("AK8963");
    M5.Lcd.setCursor(0,10); M5.Lcd.print("I AM");
    M5.Lcd.setCursor(0,20); M5.Lcd.print(d, HEX);
    M5.Lcd.setCursor(0,30); M5.Lcd.print("I Should Be");
    M5.Lcd.setCursor(0,40); M5.Lcd.print(0x48, HEX);
    delay(1000);
#endif // LCD

    // Get magnetometer calibration from AK8963 ROM
    IMU.initAK8963(IMU.magCalibration);
    // Initialize device for active mode read of magnetometer
    Serial.println("AK8963 initialized for active data mode....");
    if (Serial)
    {
      //  Serial.println("Calibration values: ");
      Serial.print("X-Axis sensitivity adjustment value ");
      Serial.println(IMU.magCalibration[0], 2);
      Serial.print("Y-Axis sensitivity adjustment value ");
      Serial.println(IMU.magCalibration[1], 2);
      Serial.print("Z-Axis sensitivity adjustment value ");
      Serial.println(IMU.magCalibration[2], 2);
    }

#ifdef LCD
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(20,0); M5.Lcd.print("AK8963");
    M5.Lcd.setCursor(0,10); M5.Lcd.print("ASAX "); M5.Lcd.setCursor(50,10);
    M5.Lcd.print(IMU.magCalibration[0], 2);
    M5.Lcd.setCursor(0,20); M5.Lcd.print("ASAY "); M5.Lcd.setCursor(50,20);
    M5.Lcd.print(IMU.magCalibration[1], 2);
    M5.Lcd.setCursor(0,30); M5.Lcd.print("ASAZ "); M5.Lcd.setCursor(50,30);
    M5.Lcd.print(IMU.magCalibration[2], 2);
    delay(1000);
    #endif // LCD
  } // if (c == 0x71)
  // else
  // {
  //   Serial.print("Could not connect to MPU9250: 0x");
  //   Serial.println(c, HEX);
  //   while(1) ; // Loop forever if communication doesn't happen
  // }

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(GREEN ,BLACK);
  M5.Lcd.fillScreen(BLACK);
  
}

void readGyro() {
   //DATA IS HERE
    IMU.readAccelData(IMU.accelCount);  // Read the x/y/z adc values
    IMU.getAres();

    // Now we'll calculate the accleration value into actual g's
    // This depends on scale being set
    IMU.ax = (float)IMU.accelCount[0]*IMU.aRes; // - accelBias[0];
    IMU.ay = (float)IMU.accelCount[1]*IMU.aRes; // - accelBias[1];
    IMU.az = (float)IMU.accelCount[2]*IMU.aRes; // - accelBias[2];

    IMU.readGyroData(IMU.gyroCount);  // Read the x/y/z adc values
    IMU.getGres();

    // Calculate the gyro value into actual degrees per second
    // This depends on scale being set
    IMU.gx = (float)IMU.gyroCount[0]*IMU.gRes;
    IMU.gy = (float)IMU.gyroCount[1]*IMU.gRes;
    IMU.gz = (float)IMU.gyroCount[2]*IMU.gRes;

    IMU.readMagData(IMU.magCount);  // Read the x/y/z adc values
    IMU.getMres();
    // User environmental x-axis correction in milliGauss, should be
    // automatically calculated
    IMU.magbias[0] = +470.;
    // User environmental x-axis correction in milliGauss TODO axis??
    IMU.magbias[1] = +120.;
    // User environmental x-axis correction in milliGauss
    IMU.magbias[2] = +125.;

    // Calculate the magnetometer values in milliGauss
    // Include factory calibration per data sheet and user environmental
    // corrections
    // Get actual magnetometer value, this depends on scale being set
    IMU.mx = (float)IMU.magCount[0]*IMU.mRes*IMU.magCalibration[0] -
               IMU.magbias[0];
    IMU.my = (float)IMU.magCount[1]*IMU.mRes*IMU.magCalibration[1] -
               IMU.magbias[1];
    IMU.mz = (float)IMU.magCount[2]*IMU.mRes*IMU.magCalibration[2] -
               IMU.magbias[2];  
}

void debugInfo() {
  Serial.print("ax = "); Serial.print((int)1000*IMU.ax);
        Serial.print(" ay = "); Serial.print((int)1000*IMU.ay);
        Serial.print(" az = "); Serial.print((int)1000*IMU.az);
        Serial.println(" mg");

        Serial.print("gx = "); Serial.print( IMU.gx, 2);
        Serial.print(" gy = "); Serial.print( IMU.gy, 2);
        Serial.print(" gz = "); Serial.print( IMU.gz, 2);
        Serial.println(" deg/s");

        Serial.print("mx = "); Serial.print( (int)IMU.mx );
        Serial.print(" my = "); Serial.print( (int)IMU.my );
        Serial.print(" mz = "); Serial.print( (int)IMU.mz );
        Serial.println(" mG");

        Serial.print("q0 = "); Serial.print(*getQ());
        Serial.print(" qx = "); Serial.print(*(getQ() + 1));
        Serial.print(" qy = "); Serial.print(*(getQ() + 2));
        Serial.print(" qz = "); Serial.println(*(getQ() + 3));  
}

void printValues() {
  // Print acceleration values in milligs!
        Serial.print("X-acceleration: "); Serial.print(1000*IMU.ax);
        Serial.print(" mg ");
        Serial.print("Y-acceleration: "); Serial.print(1000*IMU.ay);
        Serial.print(" mg ");
        Serial.print("Z-acceleration: "); Serial.print(1000*IMU.az); //we need this value
        Serial.println(" mg ");

        // Print gyro values in degree/sec
        Serial.print("X-gyro rate: "); Serial.print(IMU.gx, 3);
        Serial.print(" degrees/sec ");
        Serial.print("Y-gyro rate: "); Serial.print(IMU.gy, 3);
        Serial.print(" degrees/sec ");
        Serial.print("Z-gyro rate: "); Serial.print(IMU.gz, 3);
        Serial.println(" degrees/sec");

        // Print mag values in degree/sec
        Serial.print("X-mag field: "); Serial.print(IMU.mx);
        Serial.print(" mG ");
        Serial.print("Y-mag field: "); Serial.print(IMU.my);
        Serial.print(" mG ");
        Serial.print("Z-mag field: "); Serial.print(IMU.mz);
        Serial.println(" mG");

        IMU.tempCount = IMU.readTempData();  // Read the adc values
        // Temperature in degrees Centigrade
        IMU.temperature = ((float) IMU.tempCount) / 333.87 + 21.0;
        // Print temperature in degrees Centigrade
        Serial.print("Temperature is ");  Serial.print(IMU.temperature, 1);
        Serial.println(" degrees C");
        Serial.println("");  
}

void setupLCD() {
  M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setTextColor(GREEN ,BLACK);
      M5.Lcd.setCursor(0, 0); M5.Lcd.print("MPU9250/AK8963");
      M5.Lcd.setCursor(0, 32); M5.Lcd.print(" x   y   z  ");

      M5.Lcd.setCursor(0,  48); M5.Lcd.print((int)(1000*IMU.ax));
      M5.Lcd.setCursor(32, 48); M5.Lcd.print((int)(1000*IMU.ay));
      M5.Lcd.setCursor(64, 48); M5.Lcd.print((int)(1000*IMU.az));
      M5.Lcd.setCursor(96, 48); M5.Lcd.print("mg");

      M5.Lcd.setCursor(0,  64); M5.Lcd.print((int)(IMU.gx));
      M5.Lcd.setCursor(32, 64); M5.Lcd.print((int)(IMU.gy));
      M5.Lcd.setCursor(64, 64); M5.Lcd.print((int)(IMU.gz));
      M5.Lcd.setCursor(96, 64); M5.Lcd.print("o/s");

      M5.Lcd.setCursor(0,  96); M5.Lcd.print((int)(IMU.mx));
      M5.Lcd.setCursor(32, 96); M5.Lcd.print((int)(IMU.my));
      M5.Lcd.setCursor(64, 96); M5.Lcd.print((int)(IMU.mz));
      M5.Lcd.setCursor(96, 96); M5.Lcd.print("mG");

      M5.Lcd.setCursor(0,  128); M5.Lcd.print("Gyro T ");
      M5.Lcd.setCursor(50,  128); M5.Lcd.print(IMU.temperature, 1);
      M5.Lcd.print(" C");  
}

void yawPitchRollDebug() {
  Serial.print("Yaw, Pitch, Roll: ");
        Serial.print(IMU.yaw, 2);
        Serial.print(", ");
        Serial.print(IMU.pitch, 2);
        Serial.print(", ");
        Serial.println(IMU.roll, 2);

        Serial.print("rate = ");
        Serial.print((float)IMU.sumCount/IMU.sum, 2);
        Serial.println(" Hz");
        Serial.println("");  
}
