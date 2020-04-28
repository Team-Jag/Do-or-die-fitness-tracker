// User interaction logic calling data (model) and views
String username;
int button_state = 0;

void clientConnected() {
   println("client connected to broker");
   client.subscribe(MQTT_steps_topic);
   client.subscribe(MQTT_web_topic);
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
            username = json.getString("user_name");
            println("enrolling challenge to user" + username);
            u_api.addChallengeToUser(username, json.getString("challenge_id"));
            break;
         case(RequestType.PULL + DataType.WEBPROFILE):
            username = json.getString("user_name");
            println("pushing web profile of " + username);
            u_api.pushWebProfile(username, topic);
            break;
         case(RequestType.PUSH + DataType.NEWPROFILE):
            username = json.getString("user_name");
            String usertype = json.getString("user_type");
            if(usertype.equals("user")) {
               println("adding new user " + username);
               u_api.addNewUserToDB(json);
            } else if(usertype.equals("sponsor")) {
               println("adding new sponsor " + username);
               s_api.addNewSponsorToDB(json);
            }      
            break;
         case(RequestType.PULL + DataType.USERSTATS):
            username = json.getString("user_name");
            println("pushing user stats of " + username);
            u_api.pushUserStats(username, topic);
            break;
         default:
            return;
      }
   } catch(RuntimeException e) {
      println("String could not be parsed from topic " + topic);
   }
   // u_api.saveUsertoDB(db.users);
   refreshData();
   refreshDashboardData();
}


void controlEvent(ControlEvent theEvent) {
    int positionY=950;
    String chartType="";
    int dropDownType;
    
    //placeholder for a potential stats class
    int[] dataAllTime = {1,5,12,35,56,79,100,220,340,325};
    int[] dataWeekly = {1,5,23,353,345,243,450};
    int[] dataMonthly = {123,131,432,345,456,123,345};
    int[] dataDaily = {123,234,123,477,234,123,123};
    
   // search bar button listener
   if (theEvent.getController().getName() == "search" || key == ENTER) {
     String username = "";
     username = cp5.get(Textfield.class,"search_user").getText();
     
     println(theEvent.getController().getName());
     println("from listener "+username);
   
       
      view.buildProfile(username);  
   }
   
   //for resolving charts
   if (theEvent.isController()) {
     println("DROPDOWN CONTROLLER "+theEvent.getController().getValue()); //value gives a float
     dropDownType = int(theEvent.getController().getValue()); //is it weekly, daily, all time data etc
     println("event: "+theEvent.getName());
     //what specific data we want
     if (theEvent.getName()=="challenge view") {
       println("challenge dropdown ");
       positionY = 70;
       chartType = "CHALLENGE";
       
     } else if (theEvent.getName()=="user view") {
       println("user dropdown ");
       positionY = 270;
       chartType = "USER";
       
     } else if (theEvent.getName()=="sponsor view") {
       println("sponsor dropdown");
       positionY = 470;
       chartType = "SPONSOR";
     } else {
       println("invalid dropdown");
     }
     
     view.resetChart(chartType);
     
     switch(dropDownType) {
       case 0:
         view.buildChart(Chart.LINE, chartType, dataDaily, 10, positionY, 35, -30, 500);
         break;
       case 1:
         view.buildChart(Chart.LINE, chartType, dataWeekly, 10, positionY, 35, -30, 500);
         break;
       case 2:
        view.buildChart(Chart.LINE, chartType, dataMonthly, 10, positionY, 35, -30, 500);
         break;
       case 3:
         view.buildChart(Chart.LINE, chartType, dataAllTime, 10, positionY, 35, -30, 500);
         break;
       default:
         break;
     }
   }
   view.resetSelectionList();
   view.build_expanded();
 }
 
 void search(int buttonVal) {
   
   println("search callback");
   if (buttonVal == 0) {
      buttonVal = 1; 
   }
 }
 
 
 /*
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
