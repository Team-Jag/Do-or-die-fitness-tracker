// Presentation logic
ListBox l;
Chart overview;

// creates a dropdown list
DropdownList current_users; 
DropdownList upcoming, current, completed;
int is_expanded = 0;

// called eachtime
void refreshDashboardData() {
    // We just rebuild the view rather than updating existing
    // will need to update this to remove the user stuff 
    /* for (String status: Status.LIST) {
        cp5.remove(status + " total ");
        cp5.remove(status);
        cp5.remove(status + " chart ");
    } */
    view.resetSpacing();
    updateDashboardData();
}

// basic idea is we'll have a user and challenge view, for the manager (possibly sponsor? see the slack for 
// the drawings of how we want it to look but totally up to you)
void updateDashboardData() {
    refreshData();
    // just the title of the screen
    surface.setTitle("Do or Die Admin Dashboard");
    view.build_title("Do or Die"); //i wanted a title in the middle but not quite working yet
    
    JSONArray users = db.users.getJSONArray("user");
    //JSONArray challenge = db.challenges.getJSONArray("challenge"); //need data api functions
    //JSONArray sponser = db.challenges.getJSONArray("sponser");
    JSONObject user = users.getJSONObject(0);
    int total_users = users.size();
    int total_sponsers = 0;
    int total_challenges = 2;
    int steps = user.getInt("total_steps"); 
    
    // don't think we need the metrics - creates those weird charts at side
    //view.build_metric(users + " total ", user.getInt("total_steps"));
    view.build_list("USERS", users); //builds list with all the other stuff
    view.build_PieChart(users + "users alive", user.getInt("total_steps"), user.getInt("remaining_sec"), 50, 500);
    view.build_LineChart(users + "total users ", total_users, user.getInt("remaining_sec"), 250, 500);
    view.build_LineChart(users + "total sponsers ", total_challenges, user.getInt("remaining_sec"), 450, 500);
    
    
    // when you drop down
    view.build_expanded(user.getString("user_ID"), user); //this is for user list
}
 

// The main class which contains the dynamic build of the dashboard. Advantage being more metrics can be added with ease.
public class Dashboard_view {
    int is_expanded = 0;
    
    int vert_margin_spacing = 10;
    int horiz_margin_spacing = 10;
    
    int metric_x_size = 100;
    int metric_spacing = 0;
    int metric_y_size = 20;
    
    int list_spacing = 0;
    int list_x_size = 100;
    int list_y_size = 200;
    
    int chart_spacing = 100;
    int chart_size = 150;
    
    int chart_vertical = 500;
    int chart_horizontal = 100;
    
    int metrics_vertical = 50;
    int metrics_horizontal = 100;
    
    int user_view_hoz = 0;
    int user_view_vert = 0;
    
    int challenge_view_hoz = 0;
    int challenge_view_vert = 20;
    
    int main_list_hoz = 350;
    int main_list_vert = 10;

    void build_PieChart(String chart_name, int val, int val1, int x, int y) {
        Chart chart = cp5.addChart(chart_name) 
            //.setPosition(horiz_margin_spacing + chart_spacing, 5.5 * vert_margin_spacing)
            .setPosition(x, y)
            .setSize(chart_size, chart_size)
            .setRange(0, 10)
            .setView(PIE); // see http://www.sojamo.com/libraries/controlP5/reference/controlP5/Chart.html
            // the website has all the diff types of charts so you can play around, he had it as random before
        chart.getColor().setBackground(color(255, 1));
        chart.addDataSet(chart_name);
        chart.setColors(chart_name, color(255), color(0, 154, 189));
        chart.updateData(chart_name, val, val1);
        chart_spacing = chart_spacing + chart_size + (chart_size / 5);
    }
    
     void build_LineChart(String chart_name, int val, int val1, int x, int y) {
        Chart chart = cp5.addChart(chart_name) 
            //.setPosition(horiz_margin_spacing + chart_spacing, 5.5 * vert_margin_spacing)
            .setPosition(x, y)
            .setSize(chart_size, chart_size)
            .setRange(0, 10)
            .setView(LINE); // see http://www.sojamo.com/libraries/controlP5/reference/controlP5/Chart.html
            
        chart.getColor().setBackground(color(255, 100));
        chart.addDataSet(chart_name);
        chart.setColors(chart_name, color(000),color(0, 154, 189));
        chart.updateData(chart_name, val, val1);
        chart_spacing = chart_spacing + chart_size + (chart_size / 5);
    }
    
    void build_title(String text) {
      
    }

// curr users - build_metric
/*
    void build_metric(String name, int value) {
        cp5.addNumberbox(name)
            .setValue(value)
            .setPosition(horiz_margin_spacing, vert_margin_spacing + metric_spacing)
            .setSize(metric_x_size, metric_y_size);
        metric_spacing = metric_spacing + (2 * metric_y_size);
    } */

    void build_list(String list_name, JSONArray users) { //this creates the main list, takes from the json user object
        ScrollableList list = cp5.addScrollableList(list_name)
            .setPosition((2 * main_list_hoz) + list_spacing+30, main_list_vert)
            .setSize(list_x_size, list_y_size);
            
        list.setBackgroundColor(color(190));
        list.setItemHeight(20);
        list.setBarHeight(40);
        list.setColorBackground(color(60));
        list.setColorActive(color(255, 128));
        list_spacing = list_spacing + list_x_size + 15;
        list.clear();
        list.open();
        
        //test for one user
        
        JSONObject curr_user;
        // keep adding the remaining_sec, mainly just a test for now so update as you want 
          for(int i = 0; i < users.size(); i ++){ //confused about this
              curr_user = users.getJSONObject(i);
          
              list.addItem("user id: "+curr_user.getString("user_id"), i);
              list.addItem("  name: "+curr_user.getString("user_name"), i);
              list.addItem("  steps: "+str(curr_user.getInt("total_steps")), i);
              list.addItem("  time: "+curr_user.getString("remaining_sec"), i);
         }
     }

// i had to keep messing with the horizontal and vertical spacing below to get it to work 
    void build_expanded(String userid, JSONObject user) {
        if (is_expanded == 1) {
        // basically switch it round
            cp5.get("users").remove();
            cp5.get("challenges").remove();
            is_expanded = 1;
            // haven't used below yet 
          //  button_state = 0; // this ensures that the creation of buttons aren't reported for call backs
        }

      ListBox challenges = cp5.addListBox("challenge view")
            .setPosition((1 * challenge_view_hoz), 2 * challenge_view_vert)
            .setSize(200, 100)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(255, 128))
            .setColorActive(color(0))
            .setColorForeground(color(255, 100, 0));

      ListBox users = cp5.addListBox("user view")
            .setPosition((1 * user_view_hoz), 2 * user_view_vert)
            .setSize(200, 100)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(255, 128))
            .setColorActive(color(0))
            .setColorForeground(color(255, 100, 0));

      
/*
        users.addItem(user.getInt("total_steps"), 0);
        users.addItem(user.getInt("remaining_sec"), 1); */
        
        // create the buttons, these would be inside expanded for some reason?
        cp5.addButton("users: "+2) //+total_users
            .setValue(0)
            .setPosition((3 * metrics_horizontal), 2 * metrics_vertical + 75)
            .setSize(100, 19);

        cp5.addButton("challenges: "+2) //+total challenges
            .setValue(0)
            .setPosition((3 * metrics_horizontal + 110), 2 * metrics_vertical + 75)
            .setSize(100, 19);

        cp5.addButton("sponsers: "+0) //+total_sponsers 
            .setValue(0)
            .setPosition((3 * metrics_horizontal + 220), 2 * metrics_vertical + 75)
            .setSize(100, 19);

        is_expanded = 1;
    }

    void resetSpacing() {
        chart_spacing = 0;
        list_spacing = 0;
        metric_spacing = 0;
    }
}
