void compass_offset_calibration() {
  writeRegister(Mag_address, 0x00, 0b01110001);

  /*
    A A                        DO2 DO1 DO0      Sample Rate [Hz]      MS1 MS0    Measurment Mode
    0 0 = No Average            0   0   0   =   0.75                   0   0   = Normal
    0 1 = 2 Sample average      0   0   1   =   1.5                    0   1   = Positive Bias
    1 0 = 4 Sample Average      0   1   0   =   3                      1   0   = Negative Bais
    1 1 = 8 Sample Average      0   1   1   =   7.5                    1   1   = -
                                1   0   0   =   15 (Default)
                                1   0   1   =   30
                                1   1   0   =   75
                                1   1   1   =   -
  */
  getMag();// Disregarding the first data

  // Reading the Positive baised Data
  while (xMagRaw < 200 | yMagRaw < 200 | zMagRaw < 200) getMag(); // Making sure the data is with Positive baised

  compass_x_scalled = xMagRaw * compass_gain_fact;
  compass_y_scalled = yMagRaw * compass_gain_fact;
  compass_z_scalled = zMagRaw * compass_gain_fact;


  // Offset = 1160 - Data_positive
  compass_x_gainError = (float)compass_XY_excitation / compass_x_scalled;
  compass_y_gainError = (float)compass_XY_excitation / compass_y_scalled;
  compass_z_gainError = (float)compass_Z_excitation / compass_z_scalled;

  writeRegister(Mag_address, 0x00, 0b01110010);
  getMag();// Disregarding the first data
  // Reading the Negative baised Data
  while (xMagRaw > -200 | yMagRaw > -200 | zMagRaw > -200) getMag(); // Making sure the data is with negative baised

  compass_x_scalled = xMagRaw * compass_gain_fact;
  compass_y_scalled = yMagRaw * compass_gain_fact;
  compass_z_scalled = zMagRaw * compass_gain_fact;


  // Taking the average of the offsets
  compass_x_gainError = (float)((compass_XY_excitation / abs(compass_x_scalled)) + compass_x_gainError) / 2;
  compass_y_gainError = (float)((compass_XY_excitation / abs(compass_y_scalled)) + compass_y_gainError) / 2;
  compass_z_gainError = (float)((compass_Z_excitation / abs(compass_z_scalled)) + compass_z_gainError) / 2;
  Serial.print("x_gain_offset = ");
  Serial.println(compass_x_gainError);
  Serial.print("y_gain_offset = ");
  Serial.println(compass_y_gainError);
  Serial.print("z_gain_offset = ");
  Serial.println(compass_z_gainError);


  writeRegister(Mag_address, 0x00, 0b01110000);

  Serial.println("Calibrating the Magnetometer ....... Offset");
  Serial.println("Please rotate the magnetometer 2 or 3 times in complete circules with in one minute ............. ");

  for (int i = 0; i < 10; i++) { // Disregarding first few data
    getMag();// Disregarding the first data
  }
  float x_max = -4000, y_max = -4000, z_max = -4000;
  float x_min = 4000, y_min = 4000, z_min = 4000;

  /*
      Debug code ------------------------------
  */

  Serial.println("Starting Debug data in ");
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("0");
  Serial.println();
  for (byte i = 0; i < 10; i++) {
    Serial.print("*");
  }
  Serial.println("*");
  Serial.println("Debug -- (Offset Calibration)");
  for (byte i = 0; i < 10; i++) {
    Serial.print("*");
  }
  Serial.println("*");

  // End Debug code

  unsigned long t = millis();
  while (millis() - t <= 30000) {
    getMag();

    compass_x_scalled = (float)xMagRaw * compass_gain_fact * compass_x_gainError;
    compass_y_scalled = (float)yMagRaw * compass_gain_fact * compass_y_gainError;
    compass_z_scalled = (float)zMagRaw * compass_gain_fact * compass_z_gainError;

    Serial.print(compass_x_scalled);
    Serial.print("\t");
    Serial.print(compass_y_scalled);
    Serial.print("\t");
    Serial.println(compass_z_scalled);

    x_max = max(x_max, compass_x_scalled);
    y_max = max(y_max, compass_y_scalled);
    z_max = max(z_max, compass_z_scalled);


    x_min = min(x_min, compass_x_scalled);
    y_min = min(y_min, compass_y_scalled);
    z_min = min(z_min, compass_z_scalled);
  }

  compass_x_offset = ((x_max - x_min) / 2) - x_max;
  compass_y_offset = ((y_max - y_min) / 2) - y_max;
  compass_z_offset = ((z_max - z_min) / 2) - z_max;

  Serial.print("Offset x  = ");
  Serial.print(compass_x_offset);
  Serial.println(" mG");
  Serial.print("Offset y  = ");
  Serial.print(compass_y_offset);
  Serial.println(" mG");
  Serial.print("Offset z  = ");
  Serial.print(compass_z_offset);
  Serial.println(" mG");

}

