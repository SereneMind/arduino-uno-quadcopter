//------------------------------------------------calibration--------------------------------------------
void calibrate() {
  Serial.print("Starting up SuperCopter");           //Print message
  for (int cal_int = 0; cal_int < 500 ; cal_int ++) {   //Take 2000 readings for calibration
    getGyroValues();
    gyro_roll_cal += gyroRawx;                      //Ad roll value to gyro_roll_cal
    gyro_pitch_cal += gyroRawy;                    //Ad pitch value to gyro_pitch_cal
    gyro_yaw_cal += gyroRawz;

    readAccel();
    accelero_roll_cal += xacc;
    accelero_pitch_cal += yacc;
    accelero_yaw_cal += zacc;



    if (cal_int % 100 == 0) Serial.print(".");        //Print a dot every 100 readings
    delay(4);                                        //Wait 4 milliseconds before the next loop
  }

  gyro_roll_cal /= 500;                             //Divide the roll total by 2000
  gyro_pitch_cal /= 500;                            //Divide the pitch total by 2000
  gyro_yaw_cal /= 500;

  accelero_roll_cal /= 500;                             //Divide the roll total by 2000
  accelero_pitch_cal /= 500;                            //Divide the pitch total by 2000
  accelero_yaw_cal /= 500;                              //Divide the yaw total by 2000
  accelero_yaw_cal = accelero_yaw_cal +  128  ;     //128LSB = 1g, as we are using 4g

  Serial.println(" done!");                          //2000 measures are done!
}

int setupL3G4200D(int scale) {
  //From  Jim Lindblom of Sparkfun's code

  // Enable x, y, z and turn off power down:
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:

  if (scale == 250) {
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
  } else if (scale == 500) {
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
  } else {
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

