class Timer {
  int savedTime;
  int totalTime;
  
  Timer(int tempTotalTime) {
    totalTime = tempTotalTime;
  }
  
  // Starting the timer
  void start() {
    savedTime = millis();
  }
  
  int countdown() {
    int countDown = totalTime - (millis() - savedTime)/1000;
    return countDown;
  }
  
  boolean isHalf() {
    int passedTime = (millis() - savedTime)/1000;
    if(passedTime > totalTime/2) {
      return true;
    } else {
      return false;
    }
  }
  
  boolean isQuarter() {
    int passedTime = (millis() - savedTime)/1000;
    if(passedTime > totalTime*0.75) {
      return true;
    } else {
      return false;
    }
  }
    
  boolean isFinished() {
    int passedTime = (millis() - savedTime)/1000;
    if(passedTime > totalTime) {
      return true;
    } else {
      return false;
    }
  }
}
