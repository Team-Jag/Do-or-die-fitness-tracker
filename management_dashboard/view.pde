// Presentation logic
ListBox l;
Chart overview;
// creates a dropdown list
DropdownList current_users; 
DropdownList upcoming, current, completed;
int is_expanded = 0;

// called each time
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
    surface.setTitle("Do or Die Management Dashboard");
    JSONArray users = db.users.getJSONArray("user");
    JSONObject user = users.getJSONObject(0);
    int steps = user.getInt("total_steps"); 
    // don't think we need the metrics - creates those weird charts at side
    //view.build_metric(users + " total ", user.getInt("total_steps"));
    view.build_list("userrr", user);
    view.build_Chart(users + " chart ", user.getInt("total_steps"), user.getInt("remaining_sec"));
    // when you drop down
    view.build_expanded(user.getString("user_ID"), user);
}
 

// The main class which contains the dynamic build of the dashboard. Advantage being more metrics can be added with ease.
public class Dashboard_view {
    int is_expanded = 0;
    int vert_margin_spacing = 70;
    int horiz_margin_spacing = 70;
    int metric_x_size = 100;
    int metric_spacing = 0;
    int metric_y_size = 20;
    int list_spacing = 0;
    int list_x_size = 100;
    int list_y_size = 200;
    int chart_spacing = 0;
    int chart_size = 150;

    void build_Chart(String chart_name, int val, int val1) {
        Chart chart = cp5.addChart(chart_name) 
            .setPosition(horiz_margin_spacing + chart_spacing, 5.5 * vert_margin_spacing)
            .setSize(chart_size, chart_size)
            .setRange(0, 10)
            .setView(PIE); // see http://www.sojamo.com/libraries/controlP5/reference/controlP5/Chart.html
            // the website has all the diff types of charts so you can play around, he had it as random before
        chart.getColor().setBackground(color(255, 100));
        chart.addDataSet(chart_name);
        chart.setColors(chart_name, color(000), color(0, 255, 0));
        chart.updateData(chart_name, val, val1);
        chart_spacing = chart_spacing + chart_size + (chart_size / 5);
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

    void build_list(String list_name, JSONObject users) {
        ScrollableList list = cp5.addScrollableList(list_name)
            .setPosition((3 * horiz_margin_spacing) + list_spacing, vert_margin_spacing)
            .setSize(list_x_size, list_y_size);
        list.setBackgroundColor(color(190));
        list.setItemHeight(20);
        list.setBarHeight(40);
        list.setColorBackground(color(60));
        list.setColorActive(color(255, 128));
        list_spacing = list_spacing + list_x_size + 10;
        list.clear();
        list.open();
        // keep adding the remaining_sec, mainly just a test for now so update as you want 
          for(int i = 0; i < 10; i ++){
              list.addItem(users.getString("remaining_sec"), i);
         }
     }

// i had to keep messing with the horizontal and vertical spacing below to get it to work 
    void build_expanded(String userid, JSONObject user) {
        if (is_expanded == 1) {
        // basically switch it round
            cp5.get("users").remove();
            cp5.get("challenges").remove();
            is_expanded = 0;
            // haven't used below yet 
          //  button_state = 0; // this ensures that the creation of buttons aren't reported for call backs
        }

        ListBox users = cp5.addListBox("user")
            .setPosition((1 * horiz_margin_spacing), 2 * vert_margin_spacing)
            .setSize(550, 75)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(255, 128))
            .setColorActive(color(0))
            .setColorForeground(color(255, 100, 0));

      ListBox challenges = cp5.addListBox("challenges")
            .setPosition((3 * horiz_margin_spacing), 4 * vert_margin_spacing)
            .setSize(550, 75)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(255, 128))
            .setColorActive(color(0))
            .setColorForeground(color(255, 100, 0));
/*

        users.addItem(user.getInt("total_steps"), 0);
        users.addItem(user.getInt("remaining_sec"), 1); */
        
        // create the buttons
        cp5.addButton("user")
            .setValue(0)
            .setPosition((3 * horiz_margin_spacing), 2 * vert_margin_spacing + 75)
            .setSize(100, 19);

        cp5.addButton("challenges")
            .setValue(0)
            .setPosition((3 * horiz_margin_spacing + 110), 2 * vert_margin_spacing + 75)
            .setSize(100, 19);

        cp5.addButton("total users")
            .setValue(0)
            .setPosition((3 * horiz_margin_spacing + 220), 2 * vert_margin_spacing + 75)
            .setSize(100, 19);

        is_expanded = 1;
    }

    void resetSpacing() {
        chart_spacing = 0;
        list_spacing = 0;
        metric_spacing = 0;
    }
}
