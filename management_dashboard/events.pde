// User interaction logic calling data (model) and views
String username;
int button_state = 0;

void clientConnected() {
   println("client connected to broker");
   client.subscribe(MQTT_steps_topic);
   client.subscribe(MQTT_web_topic);
   client.subscribe(MQTT_m5_topic);
}

void connectionLost() {
   println("connection lost");
}

void messageReceived(String topic, byte[] payload) {
   try {
      JSONObject json = parseJSONObject(new String(payload));
      println("Received message from " + topic);
      String request_type = json.getString("type");
      println(request_type);
      switch(request_type) {
         case(RequestType.PUSH + DataType.STEP):
            username = json.getString("user_name");
            println("updating steps of " + username);
            u_api.updateUserStep(username);
            break;
         case(RequestType.PULL + DataType.PROFILE):
            username = json.getString("user_name");
            println("pushing profile of " + username);
            u_api.pushUserProfile(username, topic);
            break;
         case(RequestType.PULL + DataType.USERCHALLENGES):
            username = json.getString("user_name");
            println("pushing user challenges of " + username);
            u_api.pushUserChallenges(username, topic);
            break;
         case(RequestType.PULL + DataType.ALLCHALLENGES):
            println("pushing all challenges to " + topic);
            c_api.pushAllChallenges(topic);
            break;
         case(RequestType.PUSH + DataType.NEWCHALLENGE):
            println("adding new challenge to database");
            c_api.addNewChallenge(json);
            break;
         case(RequestType.PUSH + DataType.SELECTCHALLENGE):
            println("enrolling challenge to user" + username);
            
            break;
         default:
            return;
      }
   } catch(RuntimeException e) {
      println("String could not be parsed from topic " + topic);
   }
   // u_api.saveUsertoDB(db.users);
   // refreshData();
   //refreshDashboardData();
}

/*
void controlEvent(ControlEvent theEvent) {
 // expand order if clicked via API call
 if (theEvent.getController().getValueLabel().getText().contains("O") == true) {
 // call the api and get the JSON packet
 expanded_order = api.getOrdersByStatus(theEvent.getController().getName())[(int) theEvent.getController().getValue()].getString("order_id");
 view.build_expanded_order(expanded_order);
 }
 }
 
 // call back on button click
 public void accept(int theValue) {
 if (button_state > 2) {
 api.updateOrderStatus(expanded_order, Status.PROCESSING);
 }
 button_state = button_state + 1;
 }
 
 // call back on button click
 public void cancel(int theValue) {
 if (button_state > 2) {
 api.updateOrderStatus(expanded_order, Status.CLOSED);
 }
 button_state = button_state + 1;
 }
 
 // call back on button click
 public void ready(int theValue) {
 if (button_state > 2) {
 api.updateOrderStatus(expanded_order, Status.INTRANSIT);
 }
 button_state = button_state + 1;
 }*/
