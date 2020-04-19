class View {

  private:
    TextBox b1;
    TextBox b2;
    TextBox b3;
    TimeBar bar;
    Bean bean;
    Timer drawTimer = Timer(50, true);


  public:

    View() {
      b1.set("Campaigns", 0);
      b2.set("Statistics", 1);
      b3.set("Interact", 2);
    }

    void move() {
      bar.move();
      bean.move();
    }

    void draw() {
      bar.draw();
      b1.draw();
      b2.draw();
      b3.draw();
      bean.draw();
    }

    void loop() {
      if (drawTimer.isReady()) {
        move();
        draw();
        M5.Lcd.fillRect(240, 0, 80, 10, BACKGROUNDCOLOR);
        M5.Lcd.setCursor(240, 0); M5.Lcd.printf("Steps: %6d", total_steps);
        drawTimer.reset();
      }
      if (M5.BtnA.read()) {
        M5.Lcd.fillScreen(BACKGROUNDCOLOR);
        delay(100);
        campRequested = false;
        currView = camp;
      } else if (M5.BtnB.read()) {
        M5.Lcd.fillScreen(BACKGROUNDCOLOR);
        delay(100);
        statsRequested = false;
        currView = statistics;
      }
    }

} ;
