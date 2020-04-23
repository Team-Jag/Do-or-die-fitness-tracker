// Presentation logic
ListBox l;
Chart overview;
DropdownList open_orders, processing_orders, in_transit_orders, delivered_orders;
int is_expanded = 0;


void refreshDashboardData() {
    // We just rebuild the view rather than updating existing
    for (String status: Status.LIST) {
        cp5.remove(status + " total ");
        cp5.remove(status);
        cp5.remove(status + " chart ");
    }
    view.resetSpacing();
    updateDashboardData();
}

void updateDashboardData() {
    refreshData();
    surface.setTitle("Stack Delivery Management Dashboard");
    for (String status: Status.LIST) {
        view.build_metric(status + " total ", (float) api.getOrdersByStatus(status).length);
        view.build_list(status, api.getOrdersByStatus(status));
        view.build_Chart(status + " chart ", api.getOrdersByStatus(Status.OPEN).length, api.getOrdersByStatus(Status.CLOSED).length, api.getOrdersByStatus(Status.PROCESSING).length, api.getOrdersByStatus(Status.DELIVERED).length);
    }
}

// The main class which contains the dynamic build of the dashboard. Advantage being more metrics can be added with ease.
public class Dashboard_view {
// Some nasty functions here which need refactoring TODO
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
    int chart_size = 140;

    void build_Chart(String chart_name, int val, int val1, int val2, int val3) {
        Chart chart = cp5.addChart(chart_name)
            .setPosition(horiz_margin_spacing + chart_spacing, 5.5 * vert_margin_spacing)
            .setSize(chart_size, chart_size)
            .setRange(0, 10)
            .setView(int(random(6)) + 1); // see http://www.sojamo.com/libraries/controlP5/reference/controlP5/Chart.html
        chart.getColor().setBackground(color(255, 100));
        chart.addDataSet(chart_name);
        chart.setColors(chart_name, color(255), color(0, 255, 0));
        chart.updateData(chart_name, val, val1, val2, val3);
        chart_spacing = chart_spacing + chart_size + (chart_size / 5);
    }

    void build_metric(String name, Float value) {
        cp5.addNumberbox(name)
            .setValue(value)
            .setPosition(horiz_margin_spacing, vert_margin_spacing + metric_spacing)
            .setSize(metric_x_size, metric_y_size);
        metric_spacing = metric_spacing + (2 * metric_y_size);
    }

    void build_list(String list_name, JSONObject[] orders) {

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
        for (JSONObject order: orders) {
            int i = 0;
            if (order != null) {
                list.addItem(order.getString("user_id"), i);
                i = i + 1;
            }
        }
    }

    void build_expanded_order(String orderid) {

        if (is_expanded == 1) {
            cp5.get("Expanded order").remove();
            cp5.get("ready").remove();
            cp5.get("accept").remove();
            cp5.get("cancel").remove();
            is_expanded = 0;
            button_state = 0; // this ensures that the creation of buttons aren't reported for call backs
        }

        ListBox order = cp5.addListBox("user")
            .setPosition((3 * horiz_margin_spacing), 4 * vert_margin_spacing)
            .setSize(550, 75)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(255, 128))
            .setColorActive(color(0))
            .setColorForeground(color(255, 100, 0));

        order.addItem(api.getOrderByID(orderid).getString("current"), 0);

      ListBox order = cp5.addListBox("challenges")
            .setPosition((4 * horiz_margin_spacing), 5 * vert_margin_spacing)
            .setSize(550, 75)
            .setItemHeight(15)
            .setBarHeight(15)
            .setColorBackground(color(255, 128))
            .setColorActive(color(0))
            .setColorForeground(color(255, 100, 0));

        order.addItem(api.getOrderByID(orderid).getString("upcoming"), 0);
        order.addItem(api.getOrderByID(orderid).getString("current"), 1);
        order.addItem(api.getOrderByID(orderid).getString("completed"), 2);
        
        // create the buttons
        cp5.addButton("user")
            .setValue(0)
            .setPosition((3 * horiz_margin_spacing), 4 * vert_margin_spacing + 75)
            .setSize(100, 19);

        cp5.addButton("challenges")
            .setValue(0)
            .setPosition((3 * horiz_margin_spacing + 110), 4 * vert_margin_spacing + 75)
            .setSize(100, 19);

        cp5.addButton("total users")
            .setValue(0)
            .setPosition((3 * horiz_margin_spacing + 220), 4 * vert_margin_spacing + 75)
            .setSize(100, 19);

        is_expanded = 1;
    }

    void resetSpacing() {
        chart_spacing = 0;
        list_spacing = 0;
        metric_spacing = 0;
    }
}
