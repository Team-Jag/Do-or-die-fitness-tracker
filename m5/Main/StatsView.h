class StatsView {

  private:
    TextBox b2;
    TimeBar weekBar = TimeBar(0, 40, 310, 30);
    TimeBar dayBar = TimeBar(0, 110, 160, 10);
    boolean ready = false;
    int weeklySteps = 0;
    int recordWeeklySteps = 1;
    int recordDailySteps = 1;
    Timer drawTimer = Timer(50, true);

  public:
    StatsView() {
      b2.set("Home", 1);
    }

    void loop() {
      b2.draw();
      if (ready) {
        if (drawTimer.isReady()) {
          M5.Lcd.setCursor(0, 10); M5.Lcd.print("Here are your stats:");
          M5.Lcd.fillRect(0, 30, 100, 10, BACKGROUNDCOLOR);
          M5.Lcd.setCursor(0, 30); M5.Lcd.printf("Weekly Steps: %d", weeklySteps);
          weekBar.move((weeklySteps * 100) / recordWeeklySteps); weekBar.draw(); // 
          M5.Lcd.fillRect(0, 100, 100, 10, BACKGROUNDCOLOR);
          M5.Lcd.setCursor(0, 100); M5.Lcd.printf("Daily Steps: %d", total_steps);
          dayBar.move((total_steps * 100) / recordDailySteps); dayBar.draw(); //
          drawTimer.reset();
        }
        if (M5.BtnB.read()) {
          M5.Lcd.fillScreen(BACKGROUNDCOLOR);
          delay(100);
          currView = home;
          return;
        }
      } else {
        M5.Lcd.setCursor(10, 100); M5.Lcd.setTextSize(2); M5.Lcd.print("Loading Stats . . ."); M5.Lcd.setTextSize(1);
      }

    }

    void setupStats(int weeklyStepsin, int recordWeeklyStepsin, int recordDailyStepsin) {
      weeklySteps = weeklyStepsin;
      recordWeeklySteps = recordWeeklyStepsin;
      recordDailySteps = recordDailyStepsin;
    }

    void setReady(boolean b) {
      ready = b;
      if (ready) {
        M5.Lcd.fillScreen(BACKGROUNDCOLOR);
      }
    }

};
