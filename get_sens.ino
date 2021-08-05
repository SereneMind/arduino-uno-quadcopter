void get_sens()
{

  /*----------------------data manupulation from ACC-----------------------------*/
  readAccel(); // read the x/y/z tilt

  //Conversion Into Vectors
  vect_x = ((xacc - accelero_roll_cal) * 0.0078);
  vect_y = ((yacc - accelero_pitch_cal) * 0.0078);
  vect_z = ((zacc - accelero_yaw_cal) * 0.0078);

  accPitch = -(atan2(vect_x, sqrt(vect_y * vect_y + vect_z * vect_z)) * 180.0) / PI;
  accRoll  = -(atan2(vect_y, sqrt(vect_x * vect_x + vect_z * vect_z)) * 180.0) / PI;



  /*----------------------data manupulation from GYRO-----------------------------*/

  getGyroValues();  // This will update x, y, and z with new valuesv

  gyroVectx = (gyroRawx - gyro_roll_cal) * 0.0175;
  gyroVecty = -(gyroRawy - gyro_pitch_cal) * 0.0175;
  gyroVectz = (gyroRawz - gyro_yaw_cal) * 0.0175;


  //Integration of the gyro Values..
  gyroVectx_f += gyroVectx * timeStep ; //roll
  gyroVecty_f += gyroVecty * timeStep;  //pitch
  gyroVectz_f += gyroVectz * timeStep;


  errorPitch = Comp_pitch - lastPitch;
  errorRoll = Comp_roll - lastRoll;

  /*--------------------------data fusion ----------------------------------*/

  //New estimation algorithm according to "Left hand Rule"
  Comp_pitch = Comp_pitch + (gyroVecty - errorPitch) * timeStep;
  Comp_roll = Comp_roll + (gyroVectx - errorRoll) * timeStep;

  lastPitch = accPitch;
  lastRoll = accRoll;

  /*------------------------Yaw from Mag------------------------------------
    getMag();


    compass_x_scalled = xMagRaw * compass_gain_fact * compass_x_gainError + compass_x_offset;
    compass_y_scalled = yMagRaw * compass_gain_fact * compass_y_gainError + compass_y_offset;
    compass_z_scalled = zMagRaw * compass_gain_fact * compass_z_gainError + compass_z_offset;

    //Low pass filter
    alpha_m = 0.70;
    xMagF = alpha_m * compass_x_scalled + (1 - alpha_m) * xMagF;
    yMagF = alpha_m * compass_y_scalled + (1 - alpha_m) * yMagF;
    zMagF = alpha_m * compass_z_scalled + (1 - alpha_m) * zMagF;

    /*---------------------------------------
    xMagVect = xMagF * (0.92 / 1000); //Multiplying it with resolution
    yMagVect = yMagF * (0.92 / 1000); //to get a vector of the value
    zMagVect = zMagF * (0.92 / 1000); //0.9 2 mGa/LSB
    ------------------------------------------

    cos_roll = cos(Comp_roll);
    sin_roll = sin(Comp_roll);
    cos_pitch = cos(Comp_pitch);
    sin_pitch = sin(Comp_pitch);

    MAG_X = xMagF * cos_pitch + yMagF * sin_roll * sin_pitch + zMagF * cos_roll * sin_pitch; // Tilt compensated Magnetic filed X:
    MAG_Y = yMagF * cos_roll - zMagF * sin_roll; // Tilt compensated Magnetic filed Y:
    magHeading = (atan2(MAG_Y, MAG_X) * 180) / PI ; // in degrees



    // *****************************Sample Code Update Yaw ***************************
    currentHeading += gyroData[YAW] * headingScaleFactor * controldT;
    if (currentHeading > 180.0) currentHeading = -360 + currentHeading;
    if (currentHeading < -180.0) currentHeading = 360 - currentHeading;
    #ifdef useMagnetometer
    headingdiff = magnetometerHeading - currentHeading;
    if (headingdiff > 180) headingdiff = headingdiff - 360; // choose CCW because more nearby than CW
    if (headingdiff < -180) headingdiff = 360 + headingdiff; // choose CW because more nearby than CCW
    currentHeading = currentHeading + headingdiff * 0.003; // the correction of the gyro yaw
    #endif

    //******************************Update Yaw******************************
    yaw = hpz;
    //#ifdef useMagnetometer
    headingDiff = magHeading - yaw;
    yaw = yaw + headingDiff*0.0002;
    //#endif

    alpha = 0.60; //.65
    yaw  = alpha * magHeading  + (1.0 - alpha) * (yaw - hpz );
    //**********************************************************************
  */


}
