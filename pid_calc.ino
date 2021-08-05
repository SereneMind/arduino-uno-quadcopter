/*------------------------------------pid Calcualtion---------------------------------------------*/
void pidCalc() {

  //roll calculation;====================================================

  //pid_roll_setpoint = 0;//setpoint has been set in the setpoint function

  pid_error_temp_roll = Comp_roll - pid_roll_setpoint;//setpoint is calculted from the readings of the receiver

  //calculation for integral-----------------------
  pid_i_mem_roll += pid_i_gain_roll * pid_error_temp_roll;

  //////////max roll pwm has been limited to 400 instead of 500
  if (pid_i_mem_roll > pid_max_roll)pid_i_mem_roll = pid_max_roll;
  //if roll pwn comes out to be less than -400 for negative roll,
  ////////then max roll pwm has been limited to -400 instead of -500
  else if (pid_i_mem_roll < pid_max_roll * -1)pid_i_mem_roll = pid_max_roll * -1;

  //Summing all the factors--------------------------
  //PID = Proportional + Integral + derivative;
  //PID = error*p + (previousIntegral + error*i) + d*(cuurentError-previousError);
  //where p,i,d are constants;

  pid_output_roll = pid_p_gain_roll * pid_error_temp_roll +
                    pid_i_mem_roll +                         //Integral calculated above
                    (pid_d_gain_roll * (pid_error_temp_roll - pid_last_roll_d_error));

  //////////limiting the pwm to 400;
  if (pid_output_roll > pid_max_roll)pid_output_roll = pid_max_roll;
  //////////limiting the pwn for negative roll;
  else if (pid_output_roll < pid_max_roll * -1)pid_output_roll = pid_max_roll * -1;


  //Saving the error for future use.
  pid_last_roll_d_error = pid_error_temp_roll;


  //Pitch calculations==========================================================================================

  //pid_pitch_setpoint = 0;//setpoint has been set in the setpoint function

  pid_error_temp_pitch  = Comp_pitch - pid_pitch_setpoint;

  pid_i_mem_pitch += pid_i_gain_pitch * pid_error_temp_pitch;

  if (pid_i_mem_pitch > pid_max_pitch)pid_i_mem_pitch = pid_max_pitch;
  else if (pid_i_mem_pitch < pid_max_pitch * -1)pid_i_mem_pitch = pid_max_pitch * -1;

  pid_output_pitch = pid_p_gain_pitch * pid_error_temp_pitch +
                     pid_i_mem_pitch +
                     (pid_d_gain_pitch * (pid_error_temp_pitch - pid_last_pitch_d_error));

  if (pid_output_pitch > pid_max_pitch)pid_output_pitch = pid_max_pitch;
  else if (pid_output_pitch < pid_max_pitch * -1)pid_output_pitch = pid_max_pitch * -1;
  pid_last_pitch_d_error = pid_error_temp_pitch;



  //Yaw calculations=============================================================================================
  /*
    pid_error_temp_yaw = yaw - pid_yaw_setpoint;
    pid_i_mem_yaw += pid_i_gain_yaw * pid_error_temp_yaw;
    if(pid_i_mem_yaw > pid_max_yaw)pid_i_mem_yaw = pid_max_yaw;
    else if(pid_i_mem_yaw < pid_max_yaw * -1)pid_i_mem_yaw = pid_max_yaw * -1;

    pid_output_yaw = pid_p_gain_yaw * pid_error_temp_yaw + pid_i_mem_yaw + pid_d_gain_yaw * (pid_error_temp_yaw - pid_last_yaw_d_error);
    if(pid_output_yaw > pid_max_yaw)pid_output_yaw = pid_max_yaw;
    else if(pid_output_yaw < pid_max_yaw * -1)pid_output_yaw = pid_max_yaw * -1;

    pid_last_yaw_d_error = pid_error_temp_yaw;

  */
}


