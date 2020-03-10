// Data focused on reading, writing and preparing data

// Example use of abstract class for typedef
/*static abstract class Status {
    static final String[] LIST = {
        Status.OPEN,
        Status.CLOSED,
        Status.PROCESSING,
        Status.INTRANSIT,
        Status.DELIVERED
    };
    static final String OPEN = "open";
    static final String CLOSED = "closed";
    static final String PROCESSING = "processing";
    static final String INTRANSIT = "intransit";
    static final String DELIVERED = "delivered";
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
}*/
// Simulate SoC b/w API and Database
private class Database {
    int max_users = 100;
    JSONObject users = new JSONObject();
    Database() {}
    int max_users() {
        return max_users;
    }
}

// copy any JSON objects on disk into working memory 

void refreshData() {
    File dir;
    File[] files;
    dir = new File(dataPath(""));
    files = dir.listFiles();
    JSONObject json;
    for (int i = 0; i <= files.length - 1; i++) {
        String path = files[i].getAbsolutePath();
        if (path.toLowerCase().endsWith(".json")) {
            json = loadJSONObject(path);
            if (json != null) {
                db.users = json;
            }
        }
    }
}
// this is our API class to ensure separation of concerns. User -> API -> DB
public class UserData {
    // API CALL 1
    JSONObject getUserByID(String id) {
        JSONObject ret = new JSONObject();
        JSONArray users = db.users.getJSONArray("user");
        for (int i = 0; i < users.size(); i++) {
          JSONObject user = users.getJSONObject(i);
            if (user != null) {
                if (id.contains(user.getString("user_id"))) {
                    ret = user;
                }
            }
        }
        return ret;
    }
    // API CALL 2
    void saveUsertoDB(JSONObject user) {
        if (user == null) {
            return;
        } else {
            saveJSONObject(user, "data/users.json");
        }
    }
    // API CALL 3
    void updateUserStep(String id, String newsteps) {
        //JSONObject[] ret = new JSONObject[db.max_users()];

        JSONObject user = getUserByID(id);
        // key, value
        user.setString("total_steps", newsteps);
        //client.publish("food_orders", user.toString()); // change to our topic name?
    }
}
