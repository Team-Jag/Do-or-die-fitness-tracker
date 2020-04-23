// flag values
final int STATE_HOME    = 0;
final int STATE_STATS   = 1;
final int STATE_SHOP    = 2;
final int STATE_HOMEHAT = 3;

float x, y;
int steps, coin = 100;
boolean hatbought = false;
PImage home, stats, shop, homehat;
Timer timer;

// set state
int state = STATE_HOME;

void setup() {
  size(380, 350);
  background(0, 0, 0);
  steps = 5000;
  x = width/2;
  y = height/2;
  home = loadImage("HOME.png");
  stats = loadImage("STATS.png");
  shop = loadImage("SHOP.png");
  homehat = loadImage("HOMEHAT.png");

  lbutton = new Button_c(90, 325);
  mbutton = new Button_c(190, 325);
  rbutton = new Button_c(290, 325);
  timer = new Timer(30);
  timer.start();
}

void draw() {
  background(0);
  rectMode(CENTER);
  fill(100); // gray border
  rect(x, y, 330, 250);
  fill(255,255,255);
  rect(x, y, 320, 240); // screen
  textSize(15);
  text("UP arrow = WALK", 20, 20);
  lbutton.draw();
  mbutton.draw();
  rbutton.draw();
  imageMode(CENTER);
  switch(state) {
    case STATE_HOME:
      image(home, x, y);
      if(timer.isQuarter()) {
        fill(255, 0, 0);
      } else if(timer.isHalf()) {
        fill(255, 140, 0);
      } else {
        fill(34, 139, 34);
      }
      text(timer.countdown() + "s left", 55, 80);
      break;
    case STATE_STATS:
      image(stats, x, y);
      fill(255);
      textSize(15);
      text("STEPS TODAY: " + steps + " / 10,000", 55, 125);
      break;
    case STATE_SHOP:
      image(shop, x, y);
      if(hatbought == true) {
        stroke(0, 255, 0);
        fill(0, 255, 0);
        rect(x, y, 150, 30);
        fill(0);
        text("HAT BOUGHT!", x-50, y+5);
      }
      break;
    case STATE_HOMEHAT:
      image(homehat, x, y);
      if(timer.isQuarter()) {
        fill(255, 0, 0);
      } else if(timer.isHalf()) {
        fill(255, 140, 0);
      } else {
        fill(34, 139, 34);
      }
      text(timer.countdown() + "s left", 55, 80);
      break;
  }
    fill(0);
    textSize(20);
    text(coin, 285, 80);
    if(timer.isFinished()) {
      background(0);
      fill(255,0,0);
      textAlign(CENTER);
      textSize(40);
      text("GAME OVER", x, y);
    }
}

void mousePressed() {
  if(state == STATE_HOME) {   
    if(lbutton.checkClick()) state = STATE_STATS;
    if(mbutton.checkClick()) state = STATE_SHOP;
  }
  if(state == STATE_STATS) {
    if(rbutton.checkClick()) state = STATE_HOME;
    if(mbutton.checkClick()) state = STATE_SHOP;
  }
  if(state == STATE_SHOP) {
    if(lbutton.checkClick()) { 
      hatbought = true;
      coin = 0;
    }
    if(rbutton.checkClick() && hatbought == false) state = STATE_HOME;
    else if(rbutton.checkClick() && hatbought == true) state = STATE_HOMEHAT;
  }
}

void keyPressed() {
  if(key == CODED) {
    if(keyCode == UP) {
      timer.totalTime++;
      background(34, 139, 34);
      steps++;
    }
  }
}

    
