class ChallengesView {

  private:
    challenge challenges[10];
    TextBox b1;
    TextBox b2;
    TextBox b3;
    Bar progressBar = Bar(0, 70, 310, 15);
    Timer drawTimer = Timer(50, true);
    int size = 0;
    int index = 0;
    boolean ready = false;


  public:
    ChallengesView() {
      b1.set("Home", 0);
      b2.set("Prev", 1);
      b3.set("Next", 2);
    }

    void loop() {
      b1.draw();
      b2.draw();
      b3.draw();
      if (ready) {
        M5.Lcd.setCursor(0, 10); M5.Lcd.setTextSize(2); M5.Lcd.print(challenges[index].name); M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(0 , 50); M5.Lcd.print("Goal: "); M5.Lcd.print(challenges[index].stepGoal);
        if (drawTimer.isReady()) {
        progressBar.move((total_steps * 100) / challenges[index].stepGoal); progressBar.draw();
        drawTimer.reset();
        }
        M5.Lcd.setCursor(0, 90); M5.Lcd.print("Challenge Description: "); M5.Lcd.print(challenges[index].description);
        M5.Lcd.setCursor(0, 200); M5.Lcd.print("Reward: "); M5.Lcd.print(challenges[index].reward);
        int t = challenges[index].endTime;
        M5.Lcd.setCursor(150, 200); M5.Lcd.print("Ends on: "); M5.Lcd.printf("%02d/%02d/%04d %02d:%02d:%02d",day(t),month(t),year(t),hour(t),minute(t),second(t));
        if (M5.BtnA.read()) {
          M5.Lcd.fillScreen(BACKGROUNDCOLOR);
          delay(100);
          currView = home;
          return;
        }
        if (M5.BtnB.read()) {
          M5.Lcd.fillScreen(BACKGROUNDCOLOR);
          delay(100);
          index -= 1;
          if (index < 0) {
            index = size - 1;
          }
        } else if (M5.BtnC.read()) {
          M5.Lcd.fillScreen(BACKGROUNDCOLOR);
          delay(100);
          index += 1;
          if (index > size - 1) {
            index = 0;
          }
        }
      } else {
        M5.Lcd.setCursor(10, 100); M5.Lcd.setTextSize(2); M5.Lcd.print("Loading Challenges . . ."); M5.Lcd.setTextSize(1);
      }

    }


    void clearChallenges() {
      index = 0;
      size = 0;
    }

    void addChallenge(String namein, String descriptionin, int endTimein, int stepGoalin, int rewardin) {
      challenges[index].name = namein;
      challenges[index].description = descriptionin;
      challenges[index].endTime = endTimein;
      challenges[index].stepGoal = stepGoalin;
      challenges[index].reward = rewardin;
      index++;
      size++;
    }

    void setReady(boolean b) {
      ready = b;
      if (ready) {
        M5.Lcd.fillScreen(BACKGROUNDCOLOR);
        index = 0;
      }
    }

};
