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
    ControlFont cf2 = new ControlFont(createFont("Helvetica",10));
    refreshData();
    surface.setTitle("Do or Die Admin Dashboard");
    view.build_title("Do or Die", 250, 0);
    
    JSONArray users = db.users.getJSONArray("user");
    JSONArray challenge = db.challenges.getJSONArray("challenge"); 
    //JSONArray sponser = db.challenges.getJSONArray("sponser"); //need data api functions
    JSONObject user = users.getJSONObject(0);
    int total_users = users.size();
    int total_sponsers = 1;
    int total_challenges = challenge.size();
    int steps = user.getInt("total_steps"); 
    
    // don't think we need the metrics - creates those weird charts at side
    //view.build_metric(users + " total ", user.getInt("total_steps"));
    
    view.build_list("USERS", users); //builds list with all the other stuff
    view.buildSearch(10, 0);
    
    view.build_LineChart("users daily", 0, 4, 7, 250, 140);
    view.build_LineChart("users weekly", 0, 150, 700, 250, 400);
    view.build_BarChart("users, challenges, sponsers", total_challenges, total_users+1, total_sponsers, 680, 450);
    view.build_PieChart("users alive", users.size(), view.countLivePlayers(users), 680, 290); //players alive out of total players
    
    view.createButton("current users", str(total_users), 250, 100);
    view.createButton("active challenges", str(total_challenges), 380, 100);
    view.createButton("total sponsers", str(total_sponsers), 510, 100);
    
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
    int list_x_size = 250;
    int list_y_size = 350;
    
    int chart_spacing = 100;
    int chart_size = 180;
    
    int chart_vertical = 500;
    int chart_horizontal = 100;
    
    int metrics_vertical = 0;
    int metrics_horizontal = 100;
    
    int user_view_hoz = 0;
    int user_view_vert = 30;
    
    int challenge_view_hoz = 0;
    int challenge_view_vert = 20;
    
    int main_list_hoz = 305;
    int main_list_vert = 0;
    
    int R = 96;
    int G = 224;
    int B = 252;

    int countLivePlayers(JSONArray users) {
       int live = 0, i;
       JSONObject curr_user;
       
       for (i = 0; i < users.size(); i++) {
            curr_user = users.getJSONObject(i);
            if (curr_user.getInt("remaining_sec") > 0) {
                live++;
                println(live); //for debug
            }
       }
       return live;
    }

    void buildSearch(int x, int y) {
      cp5.addTextfield("")
     .setPosition(x,y)
     .setSize(100,20)
     .setFocus(true)
     .setColor(color(R,G,B))
     ;
     
      cp5.addButton("search")
        .setValue(0)
        .setPosition(x+110, y)
        .setColorBackground(color(0,135,166))
        .setColorActive(color(0))
        .setColorForeground(color(R,G,B))
        .setSize(50, 20);
    }

    void build_PieChart(String chart_name, int val, int val1, int x, int y) {
        Chart chart = cp5.addChart(chart_name)
            .setPosition(x, y)
            .setSize(chart_size, chart_size)
            .setRange(0, 10)
            .setColorCaptionLabel(color(255)) //for some reason this doesn't work for anything that is not a line graph
            .setView(Chart.PIE); // see http://www.sojamo.com/libraries/controlP5/reference/controlP5/Chart.html
            // the website has all the diff types of charts so you can play around, he had it as random before
            
            
        chart.getColor().setBackground(color(0,0));
        chart.addDataSet(chart_name);
        chart.setColors(chart_name, color(255),color(0, 124, 158));
        chart.updateData(chart_name, val, val1);
        chart_spacing = chart_spacing + chart_size + (chart_size / 5);
        
    }
    
     void build_LineChart(String chart_name, int val, int val1, int val3, int x, int y) {
        Chart chart = cp5.addChart(chart_name)
            .setPosition(x, y)
            .setSize(chart_size+200, chart_size+50)
            .setRange(0, 10)
            .setColorCaptionLabel(color(255))
            .setView(Chart.LINE); // see http://www.sojamo.com/libraries/controlP5/reference/controlP5/Chart.html
            
        chart.getColor().setBackground(color(12,23,45));
        chart.addDataSet(chart_name);
        chart.setColors(chart_name, color(255),color(0, 124, 158));
        chart.updateData(chart_name, val, val1, 5, 2, 5, 1, val3, val3);
        chart_spacing = chart_spacing + chart_size + (chart_size / 5);
    }
    
     void build_BarChart(String chart_name, int val, int val1, int val3, int x, int y) {
        Chart chart = cp5.addChart(chart_name)
            .setColorLabel(255)
            .setPosition(x, y)
            .setSize(chart_size, chart_size-20)
            .setRange(0, 10)
            .setColorCaptionLabel(color(255))
            .setView(Chart.BAR); // see http://www.sojamo.com/libraries/controlP5/reference/controlP5/Chart.html
            
        chart.getColor().setBackground(color(0,0));
        chart.addDataSet(chart_name);
        chart.setColors(chart_name, color(255),color(0, 124, 158));
        chart.updateData(chart_name, val, val1, val3);
        chart_spacing = chart_spacing + chart_size + (chart_size / 5);
    }
    
    void build_title(String text, int x, int y) { //this is a hack to get around text troubles
        //ControlFont cf1 = new ControlFont(createFont("Arial",50));
        
        PFont pfont = createFont("Impact",20); // use true/false for smooth/no-smooth
        ControlFont font = new ControlFont(pfont,85);
        
        Button title = cp5.addButton(text)
            .setValue(0)
            .setPosition(x, y)
            .setColorBackground(color(0,135,166))
            .setColorActive(color(0))
            .setColorForeground(color(R,G,B))
            .setSize(380, 90);
            
        title.getCaptionLabel().setFont(font);
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
            
        list.setBackgroundColor(color(0));
        list.setItemHeight(30);
        list.setBarHeight(40);
        list.setColorBackground(color(0,135,166));
        list.setColorForeground(color(R,G,B));
        list.setColorActive(color(R, G, B));
        list_spacing = list_spacing + list_x_size + 15;
        list.clear();
        list.open();
        
        //test for one user
        
        JSONObject curr_user;
        JSONArray user_challenges;
        
        // keep adding the remaining_sec, mainly just a test for now so update as you want 
          for(int i = 0; i < users.size(); i ++){ //confused about this
              curr_user = users.getJSONObject(i);
              user_challenges = curr_user.getJSONArray("challenge_id");
              
              list.addItem("name: "+curr_user.getString("user_name"), i);
              list.addItem("  challenges: "+str(user_challenges.size()), i);
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
            .setPosition((3 * challenge_view_hoz), 6 * challenge_view_vert)
            .setSize(200, 75)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(0,135,166))
            .setColorActive(color(R,G,B))
            .setColorForeground(color(R, G, B));
            
             

      ListBox users = cp5.addListBox("user view")
            .setPosition((2 * user_view_hoz), 1 * user_view_vert)
            .setSize(200, 75)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(0,135,166))
            .setColorActive(color(R,G,B))
            .setColorForeground(color(R, G, B));

    
      
  
        users.addItem("daily", 0);
        users.addItem("weekly", 1); 
        users.addItem("monthly", 0);
        users.addItem("all time", 1); 
       
        challenges.addItem("daily", 0);
        challenges.addItem("weekly", 1); 
        challenges.addItem("monthly", 0);
        challenges.addItem("all time", 1); 
      
        is_expanded = 0;
    }
    
    void createButton(String name, String value, int x, int y) {
        cp5.addButton(name+": "+value) //+total_sponsers 
            .setValue(0)
            .setPosition(x, y)
            .setColorBackground(color(0,135,166))
            .setColorActive(color(0))
            .setColorForeground(color(R,G,B))
            .setSize(120, 25);
    }

    void resetSpacing() {
        chart_spacing = 0;
        list_spacing = 0;
        metric_spacing = 0;
    }
}
