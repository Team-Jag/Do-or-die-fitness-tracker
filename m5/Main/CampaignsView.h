class CampaignsView {
  
  private:
    campaign **campaigns;
    TextBox b1;
    TextBox b2;
    TextBox b3;
    campaign *currCamp;
    int size;
    int index;


  public:
      CampaignsView(campaign **campaigns_in, int size_in) {
      campaigns = campaigns_in;
      size = size_in;
      b1.set("Home",0);
      b2.set("Prev",1);
      b3.set("Next",2);
      if(size_in==0) {
        currCamp = (campaign *)malloc(sizeof(campaign));
        currCamp->name="No Campaigns!";
        currCamp->description="You have no campaigns!";
      } else {
          index = 0;
          currCamp=campaigns[0];
      }
    }

    void loop() {
      b1.draw();
      b2.draw();
      b3.draw();
      M5.Lcd.setCursor(0, 10); M5.Lcd.println("Campaign Name:"); M5.Lcd.print(currCamp->name);
      M5.Lcd.setCursor(0, 30); M5.Lcd.println("Campaign Description:"); M5.Lcd.print(currCamp->description);
      if(M5.BtnA.read()) {
          currView = home;
          return;
      }
      if(size>0) {
        if(M5.BtnB.read()) {
          M5.Lcd.fillScreen(BACKGROUNDCOLOR);
          index = (index-1)%size;
          currCamp = campaigns[index];
      } else if(M5.BtnC.read()) {
          M5.Lcd.fillScreen(BACKGROUNDCOLOR);
          index = (index+1)%size;
          currCamp = campaigns[index];
      }

      }
    }
    
};
