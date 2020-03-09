// User interaction logic calling data (model) and views
/*
String expanded_order; //ID of order in focus
String MQTT_topic = "food_orders"; // vhange!!!!
int button_state = 0;

void clientConnected() {
    println("client connected to broker");
    client.subscribe(MQTT_topic);
}

void connectionLost() {
    println("connection lost");
}

void messageReceived(String topic, byte[] payload) {
    JSONObject json = parseJSONObject(new String(payload));
    if (json == null) {
        println("Order could not be parsed");
    } else {
        api.saveOrdertoDB(json);
        refreshData();
    }
    refreshDashboardData();
}

void controlEvent(ControlEvent theEvent) {
    // expand order if clicked via API call
    if (theEvent.getController().getValueLabel().getText().contains("O") == true) {
        // call the api and get the JSON packet
        expanded_order = api.getOrdersByStatus(theEvent.getController().getName())[(int) theEvent.getController().getValue()].getString("order_id");
        view.build_expanded_order(expanded_order);
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
