class View {
  
  private:
    TextBox b1;
    TextBox b2;
    TextBox b3;
    TimeBar bar;
    Bean bean;


  public:

    View() {
      b1.set("Campaigns",0);
      b2.set("Statistics",1);
      b3.set("Interact",2);
    }

    void move() {
      bar.move();
      bean.move();
    }

    void draw() {
      bar.draw();
      b1.draw();
      b2.draw();
      b3.draw();
      bean.draw();
    }
 
} ;

