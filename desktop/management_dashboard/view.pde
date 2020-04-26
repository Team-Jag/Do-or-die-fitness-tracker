// Presentation logic
ListBox l;
Chart overview;

// creates a dropdown list
DropdownList current_users; 
DropdownList upcoming, current, completed;
int is_expanded = 0;

//color scheme to keep everything consistent
static abstract class ColorScheme {
   static final int[] LIST = {
      ColorScheme.MAIN, 
      ColorScheme.HIGHLIGHTS,
      ColorScheme.BACKGROUND,
      ColorScheme.CHARTS1
   };
   static final int MAIN = #2CA8FF;
   static final int HIGHLIGHTS = #fa7a50;
   static final int BACKGROUND = #22247f;
   static final int CHARTS1 = #57dcd9;
}

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

void updateDashboardData() {
    //build basic static elements
    ControlFont cf2 = new ControlFont(createFont("Helvetica",10));
    refreshData();
    surface.setTitle("Do or Die Admin Dashboard");
    view.buildTitle("Do or Die", 250, 0);
    
    //retrieve files through db API
    JSONArray users = db.users.getJSONArray("user");
    JSONArray challenge = db.challenges.getJSONArray("challenge"); 
    JSONArray sponsor = db.sponsors.getJSONArray("sponsor"); 
    
    
    view.buildSearch(10, 0); //search for specific player
    int[] usersOverTime = {1,5,12,35,56,79,100,220,340,325}; //dummy data to simulate growing playerbase
    int[] usersAlive = {users.size() - view.countLivePlayers(users), users.size()}; //need to figure out proportions
    int[] metrics = {sponsor.size(), challenge.size(), users.size()}; //dynamic data creation into array each time dashboard is refreshed
    
    view.buildChart(Chart.LINE, "USERS OVER TIME", usersOverTime, 250, 140,200, 100, 500);
    view.buildChart(Chart.PIE, "Users Alive", usersAlive, 250, 470, 0, 0, 500);
    view.buildChartLabel("USERS ALIVE", 250, 670);
    view.buildChart(Chart.BAR, "METRICS", metrics, 450, 470, 0, 0, 10);
    view.buildChartLabel("SPONSORS         CHALLENGES       USERS", 450, 670);
    
    view.createButton("current users", str(users.size()), 250, 100);
    view.createButton("active challenges", str(challenge.size()), 380, 100);
    view.createButton("total sponsers", str(sponsor.size()), 510, 100);
    
    view.build_list("USERS", users); //builds list with all the other stuff
    view.build_expanded(users, challenge, sponsor); 
}
 

// The main class which contains the dynamic build of the dashboard. Advantage being more metrics can be added with ease.
public class Dashboard_view {
    int colorMain = ColorScheme.MAIN;
    int colorHighlights = ColorScheme.HIGHLIGHTS;
    int colorBackground = ColorScheme.BACKGROUND;
    int colorCharts = ColorScheme.CHARTS1;
  
    int is_expanded = 0; //What to do with this?
    
    int vert_margin_spacing = 10;
    int horiz_margin_spacing = 10;
    
   
    int list_spacing = 0;
    int list_x_size = 250;
    int list_y_size = 350;
    
    int chart_spacing = 100;
    int chart_size = 180; //default size value, smallest charts can be
    
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

    //LIVE PLAYER COUNT
    int countLivePlayers(JSONArray users) {
       int live = 0, i;
       JSONObject curr_user;
       
       for (i = 0; i < users.size(); i++) {
            curr_user = users.getJSONObject(i);
            if (curr_user.getInt("remaining_sec") > 0) {
                live++;
            }
       }
       return live;
    }
    
    //CHART FUNCTIONS 
    
    //generic chart build function for an array of integer data
    void buildChart(int chartType, String chartName, int[] chartData, int chartX, int chartY, int sizeX, int sizeY, int scaling) {      
      Chart chart = cp5.addChart(chartName)
          .setPosition(chartX, chartY)
          .setSize(chart_size+sizeX, chart_size+sizeY)
          .setRange(0, scaling) //chart max value to show, used for scaling
          .setColorCaptionLabel(color(255))
          .setView(chartType);
      
        chart.getColor().setBackground(color(colorBackground)); //colour scheme, need to enum
        
        chart.addDataSet(chartName);
        chart.setColors(chartName, color(255),color(colorMain),color(colorCharts)); 
        addChartData(chart, chartName, chartData); //adds data from data array
        
        
    }
    
    void addChartData(Chart chart, String chartName, int[] data) {
      int i;
      
      for (i = 0; i < data.length; i++) {
        chart.addData(chartName, data[i]);
      }
      
    }

    //workaround for chart label problem
    void buildChartLabel(String text, int labelX, int labelY) {
        Textlabel caption;
      
       caption = cp5.addTextlabel(text)
           .setText(text)
           .setPosition(labelX, labelY)
           .setColorValue(255);
    
    }

    //BUILD ELEMENT FUNCTIONS
    
    void buildTitle(String text, int titleX, int titleY) { //build big main title
        PFont pfont = createFont("Impact",20); 
        ControlFont font = new ControlFont(pfont,85);
        
        Button title = cp5.addButton(text)
            .setValue(0)
            .setPosition(titleX, titleY)
            .setColorBackground(color(colorMain))
            .setColorActive(color(0))
            .setColorForeground(colorHighlights)
            .setSize(380, 90);
            
        title.getCaptionLabel().setFont(font);
    }
    
    //for search button, events has listener
     void buildSearch(int searchX, int searchY) {
      cp5.addTextfield("")
     .setPosition(searchX,searchY)
     .setSize(100,20)
     .setFocus(true)
     .setColor(color(R,G,B))
     ;
     
      cp5.addButton("search")
        .setValue(0)
        .setPosition(searchX+110, searchY)
        .setColorBackground(color(colorMain))
        .setColorActive(color(0))
        .setColorForeground(color(colorHighlights))
        .setSize(50, 20);
    }
    
    //generic button with text
    void createButton(String name, String value, int x, int y) {
        cp5.addButton(name+": "+value) //+total_sponsers 
            .setValue(0)
            .setPosition(x, y)
            .setColorBackground(color(colorMain))
            .setColorActive(color(0))
            .setColorForeground(color(colorHighlights))
            .setSize(120, 25);
    }

    //main list for scrolling for users
    void build_list(String list_name, JSONArray users) { //this creates the main list, takes from the json user object
        ScrollableList list = cp5.addScrollableList(list_name)
            .setPosition((2 * main_list_hoz) + list_spacing+30, main_list_vert)
            .setSize(list_x_size, list_y_size);
            
        list.setBackgroundColor(color(0));
        list.setItemHeight(30);
        list.setBarHeight(40);
        list.setColorBackground(color(colorMain));
        list.setColorForeground(color(colorHighlights));
        list.setColorActive(color(0));
        list_spacing = list_spacing + list_x_size + 15;
        list.clear();
        list.open();
        
        JSONObject curr_user;
        JSONArray user_challenges;
        
         for(int i = 0; i < users.size(); i ++){ //confused about this
              curr_user = users.getJSONObject(i);
              user_challenges = curr_user.getJSONArray("challenge_id");
              
              list.addItem("name: "+curr_user.getString("user_name"), i);
              list.addItem("  challenges: "+str(user_challenges.size()), i);
              list.addItem("  steps: "+str(curr_user.getInt("total_steps")), i);
              list.addItem("  time: "+curr_user.getInt("remaining_sec"), i);
         }
     }

    void build_expanded(JSONArray usersArr, JSONArray challengesArr, JSONArray sponsorsArr) {
        
      
        if (is_expanded == 1) {
            cp5.get("users").remove();
            cp5.get("challenges").remove();
            cp5.get("sponsors").remove();
            is_expanded = 1;
        }

      ListBox challenges = cp5.addListBox("challenge view")
            .setPosition((3 * challenge_view_hoz), 2 * challenge_view_vert)
            .setSize(200, 75)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(colorMain))
            .setColorActive(color(colorHighlights))
            .setColorForeground(color(colorHighlights));

      ListBox users = cp5.addListBox("user view")
            .setPosition((3 * user_view_hoz), 5 * user_view_vert)
            .setSize(200, 75)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(colorMain))
            .setColorActive(color(0))
            .setColorForeground(color(colorHighlights));
            
      ListBox sponsors = cp5.addListBox("sponsor view")
            .setPosition((3 * challenge_view_hoz), 13 * challenge_view_vert)
            .setSize(200, 75)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(colorMain))
            .setColorActive(color(0))
            .setColorForeground(color(colorHighlights));
  
        users.addItem("daily", 0);
        users.addItem("weekly", 1); 
        users.addItem("monthly", 0);
        users.addItem("all time", 1); 
       
        challenges.addItem("daily", 0);
        challenges.addItem("weekly", 1); 
        challenges.addItem("monthly", 0);
        challenges.addItem("all time", 1); 
        
        sponsors.addItem("daily", 0);
        sponsors.addItem("weekly", 1); 
        sponsors.addItem("monthly", 0);
        sponsors.addItem("all time", 1); 
      
        is_expanded = 0;
    }
    
    

    void resetSpacing() {
        chart_spacing = 0;
        list_spacing = 0;
    }
}
