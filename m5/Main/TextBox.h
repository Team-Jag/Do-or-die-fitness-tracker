class TextBox {

  private:
    String text;
    int HEIGHT = 30;
    int WIDTH = 320 / 3;
    int x = 0;
    int y = 240 - HEIGHT;


  public:

    TextBox() {
    }

    void set(String text_in, int num) {
      text = text_in;
      x = WIDTH * num + 10;
    }

    void draw() {
      M5.Lcd.fillRect(x, y, WIDTH - 20, HEIGHT, BLUE);
      m5.Lcd.setTextColor(WHITE);
      m5.Lcd.setCursor(x + 15, y + 10); M5.Lcd.print(text);
      m5.Lcd.setTextColor(TEXTCOLOR);
    }


};
