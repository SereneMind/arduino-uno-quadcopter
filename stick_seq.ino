void stick_seq() {
  //--------------------------------------Stick Sequence---------------------------------------------//
  while (start == 0 || start == 1 || start == 2) {
    pwm(0, 0, 0, 0);


    //For starting the motors: throttle low and yaw left (step 1).
    if (receiver_input_channel_3 < 1180 && receiver_input_channel_4 < 1120)start = 1;

    //When yaw stick is back in the center position (step 2).
    if (start == 1 && receiver_input_channel_3 < 1180 && receiver_input_channel_4 > 1450) {
      start = 2;
      //Reset the pid controllers for a bumpless start.
      pid_error_temp_roll = 0;

      pid_i_mem_roll = 0;
      pid_last_roll_d_error = 0;
      pid_output_roll = 0;

      pid_i_mem_pitch = 0;
      pid_last_pitch_d_error = 0;
      pid_output_pitch = 0;

      pid_i_mem_yaw = 0;
      pid_last_yaw_d_error = 0;
      pid_output_yaw = 0;

      //Reset the sensor data for a bumpless start.
      Comp_pitch = 0;
      Comp_roll = 0;

      //Reset the flags for a bumpless start.
      start_descend = LOW;
      i_am_up = LOW;
      count = 0;
    }

    //when throttle reaches the threshold value, motors get started (step 3).
    if (start == 2 && receiver_input_channel_3 > 1200 ) start = 3;

#ifdef stickSequence
    Serial.print(start);
    Serial.print("\t");
    Serial.print(receiver_input_channel_3);
    Serial.print("\t");
    Serial.println(receiver_input_channel_4);
#endif
  }
}
