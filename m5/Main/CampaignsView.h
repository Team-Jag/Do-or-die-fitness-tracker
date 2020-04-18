<<<<<<< Updated upstream
class CampaignsView {
  
  private:
    Campaign* campaigns;
    int size;


  public:
    CampaignsView(Campaign* campaigns_in, int size_in) {
      campaigns = campaigns_in;
      size = size_in;
    }
    
};
=======
class CampaignsView {
  
  private:
    Campaign* campaigns;
    TextBox b1;
    TextBox b2;
    TextBox b3;
    int size;


  public:
    CampaignsView(Campaign* campaigns_in, int size_in) {
      campaigns = campaigns_in;
      size = size_in;
      b1.set("Home",0);
      b2.set("Prev",1);
      b3.set("Next",2);
    }

    void loop() {
      
    }
    
};
>>>>>>> Stashed changes
