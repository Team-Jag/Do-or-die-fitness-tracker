class CampaignsView {

  private:
    campaign campaigns[10];
    TextBox b1;
    TextBox b2;
    TextBox b3;
    int size = 0;
    int index = 0;
    boolean ready = false;


  public:
    CampaignsView() {
      b1.set("Home", 0);
      b2.set("Prev", 1);
      b3.set("Next", 2);
    }

    void loop() {
      b1.draw();
      b2.draw();
      b3.draw();
      if (ready) {
        M5.Lcd.setCursor(0, 10); M5.Lcd.println("Campaign Name:"); M5.Lcd.print(campaigns[index].name);
        M5.Lcd.setCursor(0, 30); M5.Lcd.println("Campaign Description:"); M5.Lcd.print(campaigns[index].description);
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
          if(index < 0) {
            index = size-1;
          }
        } else if (M5.BtnC.read()) {
          M5.Lcd.fillScreen(BACKGROUNDCOLOR);
          delay(100);
          index += 1;
          if(index > size-1) {
            index = 0;
          }
        }
      } else {
        M5.Lcd.setCursor(0, 10); M5.Lcd.println("Loading Campaigns . . .");
      }

    }

    void addCampaign(String namein, String descriptionin) {
      campaigns[index].name = namein;
      campaigns[index].description = descriptionin;
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
