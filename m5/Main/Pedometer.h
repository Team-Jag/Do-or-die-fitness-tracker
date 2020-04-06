/* MPU9250 Basic Example Code
 by: Kris Winer
 date: April 1, 2014
 license: Beerware - Use this code however you'd like. If you
 find it useful you can buy me a beer some time.
 Modified by Brent Wilkins July 19, 2016
 */

#include "utility/MPU9250.h"
#include "utility/quaternionFilters.h"

class Pedometer {

  private:
    MPU9250 IMU;
    int curr_z;
    int curr_x;
    int curr_y;
    int sum;
    float moving_average = 0; //sum of all elements divided by ELEMENTS
    bool step_flag = false;
    boolean stepTaken;

    void readGyro() {
     IMU.readAccelData(IMU.accelCount);  // Read the x/y/z adc values
     IMU.getAres();
  
      // Now we'll calculate the accleration value into actual g's
      // This depends on scale being set
      IMU.ax = (float)IMU.accelCount[0]*IMU.aRes; // - accelBias[0];
      IMU.ay = (float)IMU.accelCount[1]*IMU.aRes; // - accelBias[1];
      IMU.az = (float)IMU.accelCount[2]*IMU.aRes; // - accelBias[2];
  
      IMU.readGyroData(IMU.gyroCount);  // Read the x/y/z adc values
      IMU.getGres();
  
      // Calculate the gyro value into actual degrees per second this depends on scale being set
      IMU.gx = (float)IMU.gyroCount[0]*IMU.gRes;
      IMU.gy = (float)IMU.gyroCount[1]*IMU.gRes;
      IMU.gz = (float)IMU.gyroCount[2]*IMU.gRes;
  
      IMU.readMagData(IMU.magCount);  // Read the x/y/z adc values
      IMU.getMres();
      // User environmental x-axis correction in milliGauss, should be automatically calculated
      IMU.magbias[0] = +470.;
      // User environmental x-axis correction in milliGauss TODO axis??
      IMU.magbias[1] = +120.;
      // User environmental x-axis correction in milliGauss
      IMU.magbias[2] = +125.;
  
      // Calculate the magnetometer values in milliGauss
      // Include factory calibration per data sheet and user environmental corrections
      // Get actual magnetometer value, this depends on scale being set
      IMU.mx = (float)IMU.magCount[0]*IMU.mRes*IMU.magCalibration[0] - IMU.magbias[0];
      IMU.my = (float)IMU.magCount[1]*IMU.mRes*IMU.magCalibration[1] - IMU.magbias[1];
      IMU.mz = (float)IMU.magCount[2]*IMU.mRes*IMU.magCalibration[2] - IMU.magbias[2];  
  }

    void updateSteps() {
        
        curr_x=IMU.gx;
        curr_y=IMU.gy;
        curr_z=IMU.gz;
  
        if (curr_x < 0) { curr_x *= -1; }
        if (curr_y < 0) { curr_y *= -1; }
        if (curr_z < 0) { curr_z *= -1; }
        
        sum = curr_x+curr_y+curr_z;
  
        //if we are not currently in a "step", but goes outside threshold
        if ((sum >= 350 || sum < -350) && step_flag == false) {
          step_flag = true;
          stepTaken = true;
        }
  
        if ((sum < 350 && sum > -350) && step_flag == true) {
          step_flag = false;  
        }
  }

  
  public :
    Pedometer() {}

    boolean loop() {
      // If intPin goes high, all data registers have new data
      // On interrupt, check if data ready interrupt
      if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {  
        readGyro();
      } // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
    
      IMU.updateTime(); // Must be called before updating quaternions!
    
      //info about sensor itself and x/y rotation alignment
      //MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
      MahonyQuaternionUpdate(IMU.ax, IMU.ay, IMU.az, IMU.gx*DEG_TO_RAD, IMU.gy*DEG_TO_RAD, IMU.gz*DEG_TO_RAD, IMU.my, IMU.mx, IMU.mz, IMU.deltat);
    
      // Serial print and/or display at 0.5 s rate independent of data rates
      IMU.delt_t = millis() - IMU.count;
      stepTaken = false;
      // update LCD once per half-second independent of read rate
        if (IMU.delt_t > 100) {
          updateSteps();
          IMU.count = millis();
          IMU.sumCount = 0;
          IMU.sum = 0;
        } // if (IMU.delt_t > 100)
      return stepTaken;
    }
        
    void setup() {
      
      IMU.MPU9250SelfTest(IMU.SelfTest); // Start by performing self test and reporting values
      IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias); // Calibrate gyro and accelerometers, load biases in bias registers
      IMU.initMPU9250();
      //byte d = IMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);

  }
  
};
