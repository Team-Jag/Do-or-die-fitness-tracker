class Bean {

  private:

    int eyeWidth = 30;
    int r = 60;
    int m5Width = 320;
    int m5Height = 280;
    int x = 160; //Using m5.lcd.width()/2 doesn't work.
    int y = 140; //Using m5.lcd.height()/2 doesn't work.
    int yFloor = 140;
    int yMax = 100;
    short step = 1;
    short jump = 1;
    int xold, yold;
    boolean jumping = false;
    Timer jumpTimer = Timer(1000, true);


    void drawEye(int xin, int yin, int r) {
      if (y < yFloor-(yFloor-yMax)/2) {
        M5.Lcd.drawLine(xin - r / 2, yin, xin, yin - r / 2, BLACK);
        M5.Lcd.drawLine(xin, yin - r / 2, xin + r / 2, yin, BLACK);
      } else {
        M5.Lcd.fillCircle(xin, yin, r, WHITE);
        M5.Lcd.fillCircle(xin, yin + (r / 2), r / 2, BLACK);
      }
    }

    void drawMouth() {
      int i = 10 * ((y - yMax) / (yFloor-yMax)); //How squished the mouth is
      M5.Lcd.fillEllipse(x, y + r/2, 15 + i, 15 - i, BLACK);
    }


  public:

    Bean() {

    }

    void move() {
      yMax = 100 + (20*(maxlife-lifeleft)/maxlife); //Formula to change maximum value of y based on life left, max = 100, min = 120
      if (jumping == false && jumpTimer.isReady()) {
        jumping = true;
      }

      if (jumping) {
        xold = x; //Store old coordinates so we cand delete old frame
        yold = y;

        y += jump * (10 -  (8 *(yFloor - y) / (yFloor - yMax))); //This formula is so that maxspeed = 10, minspeed = 2
        if (y >= yFloor) {
          jump = -1;
        }
        if (y <= yMax) {
          jump = 1;
        }
        x += (step*4*lifeleft)/maxlife + step; //Formula for speed in x based on life left, min = 2, max = 5
        if (x >= m5Width - r) { //Right edge
          step = -1;
        }
        if (x <= r) { //Left edge
          step = +1;
        }

      } //jumping

      if (y >= yFloor && jumping == true) {
        jumping = false;
        jumpTimer.setNewPeriod((5000*(maxlife-lifeleft))/maxlife); //jumping frequency, max = 0ms delay, min = 5000 ms delay
        jumpTimer.reset();
      }
      Serial.println(y);
    }

    void draw() {
      M5.Lcd.fillCircle(xold, yold, r, BACKGROUNDCOLOR);
      M5.Lcd.fillCircle(x, y, r, 0xFC9F);
      drawEye(x - eyeWidth, y - 10, 20);
      drawEye(x + eyeWidth, y - 10, 20);
      drawMouth();
    }

    void drawdead() {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(120, 0); M5.Lcd.setTextSize(2); M5.Lcd.setTextColor(RED); M5.Lcd.print("Dead :(");
      M5.Lcd.fillCircle(160, 120, 60, 0xFC9F);
      drawDeadEye(160 - eyeWidth, 120 - 10, 20);
      drawDeadEye(160 + eyeWidth, 120 - 10, 20);
      drawMouth();
    }

    void drawDeadEye(int xin, int yin, int r) {
      M5.Lcd.drawLine(xin - r / 2, yin + r / 2, xin + r / 2, yin - r / 2, BLACK);
      M5.Lcd.drawLine(xin - r / 2, yin - r / 2, xin + r / 2, yin + r / 2, BLACK);
    }

};
