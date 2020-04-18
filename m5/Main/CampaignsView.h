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
