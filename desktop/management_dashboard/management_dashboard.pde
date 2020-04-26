import java.util.*;
import java.text.*;
import mqtt.*;
import controlP5.*;

String MQTT_steps_topic = "doordie_steps";
String MQTT_web_topic = "doordie_web";

ControlP5 cp5;
MQTTClient client;
Dashboard_view view = new Dashboard_view();
UserData u_api = new UserData();
ChallengeData c_api = new ChallengeData();
SponsorData s_api = new SponsorData();
Database db = new Database();

void setup() {
   cp5 = new ControlP5(this);
   size(900, 700);
   // connect to the broker
   client = new MQTTClient(this);
   // connect to the broker and use a random string for clientid
   client.connect("mqtt://try:try@broker.hivemq.com", "processing_desktop" + str(random(3)));
   delay(100);
   refreshData();
   // run_tests();

   // refresh the dashboard with the information
   updateDashboardData();
}

// we don't really use the draw function as controlP5 does the work
void draw() {
  background(0);
  // updates time left for users in database
  if(millis() - time >= 1000) {
     u_api.updateTimeRemaining();
     time = millis();
  }
}
