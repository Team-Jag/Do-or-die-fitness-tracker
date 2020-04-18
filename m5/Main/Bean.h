class Bean {
  
  private:
  
    int eyeWidth = 30;
    int r = 60;
    int x = 160; //Using m5.lcd.width()/2 doesn't work.
    int y = 140;
    short step = 5;
    short jump = 1;
    int xold, yold;
    boolean jumping = false;
    Timer jumpTimer = Timer(1000,true);

    
    void drawEye(int xin, int yin, int r) {
      if(y<120){
        M5.Lcd.drawLine(xin-r/2,yin,xin,yin-r/2,BLACK);
        M5.Lcd.drawLine(xin,yin-r/2,xin+r/2,yin,BLACK);
      } else {
        M5.Lcd.fillCircle(xin, yin, r, 0xFFFF);
      M5.Lcd.fillCircle(xin,yin+(r/2),r/2,0x0000);
      } 
    }

    void drawMouth() {
      int i = 10*((y-100)/40);
      M5.Lcd.fillEllipse(x,y+30,15+i,15-i,BLACK);
    }


  public:

    Bean() {
      
    }
    
    void move() {
      if(jumping == false && jumpTimer.isReady()) {
        jumping = true;
      }

        if(jumping) {
        xold = x;
        yold = y;
        
        y+=jump*(10-8*((140-y)/40));
        if(y>=140) {
          jump = -1;
        }
        if(y<=100) {
          jump = 1;
        }
        x+=step;
        if (x >= 320-60) {
          step = -5;
        }
        if (x <= 0+60) {
          step = +5;
        }

      } //jumping

      if(y>=140 && jumping == true) {
        jumping = false;
        jumpTimer.reset();
      }

      Serial.print(y);
      
    }

    void draw() {
      M5.Lcd.fillCircle(xold, yold, r, BACKGROUNDCOLOR);
      M5.Lcd.fillCircle(x, y, r, 0xFC9F);
      drawEye(x-eyeWidth,y-10,20);
      drawEye(x+eyeWidth,y-10,20);
      drawMouth();
    }
    
    
};