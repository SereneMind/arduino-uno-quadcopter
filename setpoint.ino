void setpoint() {

  int divider = 20;
  //The PID set point in degrees per second is determined by the roll receiver input.
  //In the case of deviding by 3 the max roll rate is aprox 164 degrees per second ( (500-15)/3 = 164d/s ).
  pid_roll_setpoint = 0;
  //We need a little dead band of 16us for better results.
  if (receiver_input_channel_1 > 1515)pid_roll_setpoint = (receiver_input_channel_1 - 1515) / divider;
  //remember below setpoint will be set in negative values.....
  else if (receiver_input_channel_1 < 1485)pid_roll_setpoint = (receiver_input_channel_1 - 1485) / divider;



  //The PID set point in degrees per second is determined by the pitch receiver input.
  //In the case of deviding by 3 the max pitch rate is aprox 164 degrees per second ( (500-8)/3 = 164d/s ).
  pid_pitch_setpoint = 0;
  //We need a little dead band of 16us for better results.
  if (receiver_input_channel_2 > 1515)pid_pitch_setpoint = (receiver_input_channel_2 - 1515) / divider;
  else if (receiver_input_channel_2 < 1485)pid_pitch_setpoint = (receiver_input_channel_2 - 1485) / divider;


  /*
    //The PID set point in degrees per second is determined by the yaw receiver input.
    //In the case of deviding by 3 the max yaw rate is aprox 164 degrees per second ( (500-8)/3 = 164d/s ).
    pid_yaw_setpoint = 0;
    //We need a little dead band of 16us for better results.
    if(receiver_input_channel_3 > 1050){ //Do not yaw when turning off the motors.
    if(receiver_input_channel_4 > 1515)pid_yaw_setpoint = (receiver_input_channel_4 - 1515)/divider;
    else if(receiver_input_channel_4 < 1485)pid_yaw_setpoint = (receiver_input_channel_4 - 1485)/divider;
    }
  */
}
