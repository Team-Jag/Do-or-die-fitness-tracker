// to do:
// Check if null is returned before performing operations on the new JSONObject in case the String content could not be parsed.
// Make sure the API is returning values correctly.

void run_tests() {
  test_user();
}

void test_user() {
  String userid = "1234";
  assert api.getUserByID("1234").getString("user_id").equals("1234");
  assert api.getUserByID(userid).getString("user_name").equals("User1");
  assert api.getUserByID("1234").getString("total_steps").equals("2200");
  assert api.getUserByID("1234").getString("remaining_sec").equals("2200");
  assert api.getUserByID("1234").getString("current_time").equals("2020-02-30T08:35:30.0108Z");
}

void test_updatesteps() {
  api.updateUserStep("1234", "1000");
    assert api.getUserByID("1234").getString("total_steps").equals("1000");
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
