// to do:
// Check if null is returned before performing operations on the new JSONObject in case the String content could not be parsed.
// Make sure the API is returning values correctly.

void run_tests() {
   test_user();
   //test_updatesteps();
}

void test_user() {
   String name = "Mario";
   assert u_api.getUserByName(name).getString("user_name").equals("Mario");
   assert u_api.getUserByName(name).getInt("total_steps") == 2200;
   assert u_api.getUserByName(name).getString("remaining_sec").equals("2000");
   assert u_api.getUserByName(name).getString("current_time").equals("2020-02-30T08:35:30.0108Z");
   name = "Luigi";
   assert u_api.getUserByName(name).getString("user_name").equals("Luigi");
   assert u_api.getUserByName(name).getInt("total_steps") == 0;
   assert u_api.getUserByName(name).getString("remaining_sec").equals("3000");
   assert u_api.getUserByName(name).getString("current_time").equals("2020-02-30T08:35:30.0108Z");
}
/*
void test_updatesteps() {
 String userid = "1";
 api.updateUserStep(userid, 1000);
 assert api.getUserByID(userid).getInt("total_steps") == 1000;
 api.updateUserStep(userid, 2200);
 userid = "2";
 api.updateUserStep(userid, 3);
 assert api.getUserByID(userid).getInt("total_steps") == 3;
 api.updateUserStep(userid, 0);  
 }
/*
 void test_challenge() {
 assert challenge_id == "1";
 assert challenge_name == "10K Step Challenge";
 assert description == "blabla";
 assert end_time == "20-02-28 14:20";
 assert step_goal == "10000";
 assert reward == "800";
 assert current_time == "2020-02-30T08:35:30.0108Z";
 }
 
 void test_sponsor() {
 assert sponsor_id == "11";
 assert challenge_id[0] == "1";
 assert challenge_id[1] == "5";
 }*/
