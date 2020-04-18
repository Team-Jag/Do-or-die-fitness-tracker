class Bean {
  
  private:
  
    int eyeWidth = 30;
    int r = 60;
    int x = 160; //Using m5.lcd.width()/2 doesn't work.
    int y = 140;
    int step = 5;
    int jump = 1;
    
    void drawEye(int x, int y, int r) {
      M5.Lcd.fillCircle(x, y, r, 0xFFFF);
      M5.Lcd.fillCircle(x,y+(r/2),r/2,0x0000);
    }


  public:

  void delet() {
    M5.Lcd.fillCircle(x, y, r, BACKGROUNDCOLOR);
  }

    void move() {
      y+=jump*(10-8*((140-y)/40));
      if(y>=140) {
        jump = -1;
      }
      if(y<=100) {
        jump = 1;
      }
      x+=step;
      if (x >= 320) {
        step = -5;
      }
      if (x <= 0) {
        step = +5;
      }
    }

    void draw() {
      M5.Lcd.fillCircle(x, y, r, 0xFC9F);
      drawEye(x-eyeWidth,y-10,20);
      drawEye(x+eyeWidth,y-10,20);
    }
    
    
};
