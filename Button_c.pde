Button_c lbutton;
Button_c mbutton;
Button_c rbutton;

class Button_c {
  int x;
  int y;
  int w = 80;
  int h = 35;
  
  Button_c(int set_x, int set_y) {
    x = set_x;
    y = set_y;
  }
  
  void draw() {
    stroke(0, 0, 0);
    strokeWeight(3);
    fill(255, 255, 255);
    
    rect(x, y, w, h, 15);
  }

  boolean checkClick() {
    if(mouseX>=x-w && mouseX<=x+w && mouseY>=y-h && mouseY<=y+h) {
      fill(255,255,255);
      return true;
    } else { 
      return false;
    }
  }
}
