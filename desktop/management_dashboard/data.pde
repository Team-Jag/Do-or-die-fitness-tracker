// Data focused on reading, writing and preparing data

static abstract class RequestType {
   static final String[] LIST = {
      RequestType.PUSH, 
      RequestType.PULL
   };
   static final String PUSH = "push ";
   static final String PULL = "pull ";
}

static abstract class DataType {
   static final String[] LIST = {
      DataType.PROFILE, 
      DataType.USERCHALLENGES, 
      DataType.ALLCHALLENGES, 
      DataType.NEWCHALLENGE, 
      DataType.SELECTCHALLENGE, 
      DataType.STEP, 
      DataType.WEBPROFILE,
      DataType.NEWPROFILE
   };
   static final String PROFILE = "profile";
   static final String USERCHALLENGES = "user challenges";
   static final String ALLCHALLENGES = "all challenges";
   static final String NEWCHALLENGE = "new challenge";
   static final String SELECTCHALLENGE = "select challenge";
   static final String STEP = "step";
   static final String WEBPROFILE = "web profile";
   static final String NEWPROFILE = "new profile";
}


// Example use of public class for metric as we use multiple (modular design)
public class Metric {
   public String name;
   public float value;
   // The Constructor
   Metric(String _name, float _value) {
      name = _name;
      value = _value;
   }
}

// Simulate SoC b/w API and Database
private class Database {
   JSONObject users = new JSONObject();
   JSONObject sponsors = new JSONObject();
   JSONObject challenges = new JSONObject();
   Database() {
   }
}

// copy any JSON objects on disk into working memory and update timestamps
void refreshData() {
   File dir;
   File[] files;
   dir = new File(dataPath(""));
   files = dir.listFiles();
   JSONObject json;
   for (int i = 0; i <= files.length - 1; i++) {
      String path = files[i].getAbsolutePath();
      if (path.toLowerCase().endsWith("users.json")) {
         json = loadJSONObject(path);
         if (json != null) {
            db.users = json;
         }
      }
      if (path.toLowerCase().endsWith("sponsors.json")) {
         json = loadJSONObject(path);
         if (json != null) {
            db.sponsors = json;
         }
      }
      if (path.toLowerCase().endsWith("challenges.json")) {
         json = loadJSONObject(path);
         if (json != null) {
            db.challenges = json;
         }
      }
   }
}

long getUnixTime() {
   SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
   Date date = new Date();
   String strDate = formatter.format(date); 
   println(strDate);
   long unixTime = date.getTime()/1000; // milliseconds to seconds
   return unixTime;
}

// this is our API class to ensure separation of concerns. User -> API -> DB
public class UserData {
   // API CALL 1
   JSONObject getUserByName(String name) {
      JSONObject ret = new JSONObject();
      JSONArray users = new JSONArray();
      users = db.users.getJSONArray("user");
      if (users != null) {    
         for (int i = 0; i < users.size(); i++) {
            JSONObject user = users.getJSONObject(i);
            if (user != null) {
               if (name.equals(user.getString("user_name"))) {
                  ret = user;
               }
            }
         }
      }
      return ret;
   }
   // API CALL 2
   void saveUsertoDB(JSONObject user) {
      if (user == null) return;
      else saveJSONObject(user, "data/users.json");
   }
   // API CALL 3
   void updateUserStep(String name) {
      JSONObject user = getUserByName(name);
      // key, value
      int incrementstep = user.getInt("total_steps") + 1;
      user.setInt("total_steps", incrementstep);
      int time = user.getInt("remaining_sec");
      user.setInt("remaining_sec", time+2);
      u_api.saveUsertoDB(db.users);
   }
   // API CALL 4
   void pushUserProfile(String name, String topic) {
      JSONObject user = u_api.getUserByName(name);
      JSONObject ret = new JSONObject();
      ret.setString("type", RequestType.PUSH + DataType.PROFILE);
      ret.setString("user_name", name);
      if (user.get("user_name") != null) {      
         ret.setInt("total_steps", user.getInt("total_steps"));
         ret.setInt("remaining_sec", user.getInt("remaining_sec"));
      }
      client.publish(topic, ret.toString());
   }
   // API CALL 5
   void pushUserChallenges(String name, String topic) {
      JSONObject user = u_api.getUserByName(name);
      JSONObject ret = new JSONObject();
      JSONArray challengeid = user.getJSONArray("challenge_id");
      JSONArray challenges = new JSONArray();
      ret.setString("type", RequestType.PUSH + DataType.USERCHALLENGES);
      ret.setJSONArray("challenges", challenges);
      ret.setString("user_name", name);
      if (challengeid != null) {
         for (int i = 0; i < challengeid.size(); i++) {
            challenges.setJSONObject(i, c_api.getChallengeByID(challengeid.get(i).toString()));
         }
      }
      client.publish(topic, ret.toString());
   }
   // API CALL 6
   void addChallengeToUser(String name, String challengeid) {
      JSONObject user = u_api.getUserByName(name);
      if (user != null) {
         if (c_api.getChallengeByID(challengeid) != null) {
            JSONArray challenges = user.getJSONArray("challenge_id");
            challenges.setString(challenges.size()+1, challengeid);
            u_api.saveUsertoDB(db.users);
         }
      }
   }
   // API CALL 7
   void pushWebProfile(String name, String topic) {
      JSONObject user = u_api.getUserByName(name);
      JSONObject ret = new JSONObject();
      JSONArray challenges = new JSONArray();
      ret.setString("type", RequestType.PUSH + DataType.WEBPROFILE);
      ret.setString("user_name", name);
      if (user.get("user_name") != null) {      
         JSONArray challengeid = user.getJSONArray("challenge_id");
         ret.setString("user_type", user.getString("user_type"));
         ret.setInt("total_steps", user.getInt("total_steps"));
         ret.setInt("remaining_sec", user.getInt("remaining_sec"));
         ret.setJSONArray("challenges", challenges);
         if (challengeid != null) {
            for (int i = 0; i < challengeid.size(); i++) {
               challenges.setJSONObject(i, c_api.getChallengeByID(challengeid.get(i).toString()));
            }
         }
      }
      client.publish(topic, ret.toString());
   }
   // API CALL 8
   void updateTimeRemaining() {
      JSONArray users = db.users.getJSONArray("user");
      if (users != null) {
         for (int i = 0; i < users.size(); i++) {
            JSONObject user = users.getJSONObject(i);
            if (user != null) {
               int timeLeft = user.getInt("remaining_sec");
               if (timeLeft != 0) user.setInt("remaining_sec", timeLeft-1);
            }
         }
         u_api.saveUsertoDB(db.users);
      }
   }
   // API CALL 9
   void addNewUserToDB(JSONObject user) {
      JSONArray users = db.users.getJSONArray("user");
      user.remove("type");
      users.setJSONObject(db.users.size()+1, user);
      u_api.saveUsertoDB(db.users);
   }
}

public class ChallengeData {
   // API CALL 1
   JSONObject getChallengeByID(String id) {
      JSONObject ret = new JSONObject();
      JSONArray challenges = new JSONArray();
      challenges = db.challenges.getJSONArray("challenge");
      if (challenges != null) {
         for (int i = 0; i < challenges.size(); i++) {
            JSONObject challenge = challenges.getJSONObject(i);
            if (challenge != null) {
               if (id.contains(challenge.getString("challenge_id"))) ret = challenge;
            }
         }
      }
      return ret;
   }
   // API CALL 2
   void saveChallengetoDB(JSONObject challenge) {
      if (challenge == null) return;
      else saveJSONObject(challenge, "data/challenges.json");
   }
   // API CALL 3
   void pushAllChallenges(String topic) {
      JSONObject ret = new JSONObject();
      ret.setString("type", RequestType.PUSH + DataType.ALLCHALLENGES);
      ret.setJSONArray("challenge", db.challenges.getJSONArray("challenge"));
      client.publish(topic, ret.toString());
   }
   // API CALL 4
   void addNewChallenge(JSONObject challenge) {
      JSONArray challenges = db.challenges.getJSONArray("challenge");
      challenge.remove("type");
      challenges.setJSONObject(db.challenges.size()+1, challenge);
      c_api.saveChallengetoDB(db.challenges);
   }
}
