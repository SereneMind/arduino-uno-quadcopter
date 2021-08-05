void esc_update()
{
  /*
    for x configuration(left hand co-ordinate system)

     ->     <-
      M0   M1
        \ /
        / \
      M3   M2
     ->     <-

  */
  /*
      esc_1 = throttle - pid_output_roll ; //Calculate the pulse for esc 1 (front-left - CW)//Currently +ve y axis is designated as front
      esc_2 = throttle + pid_output_roll ; //Calculate the pulse for esc 2 (front-right - CCW)
      esc_3 = throttle + pid_output_roll ; //Calculate the pulse for esc 3 (rear-right - CW)
      esc_4 = throttle - pid_output_roll ; //Calculate the pulse for esc 4 (rear-left - CCW)

      esc_1 = throttle  + pid_output_pitch; //Calculate the pulse for esc 1 (front-left - CW)//Currently +ve y axis is designated as front
      esc_2 = throttle  + pid_output_pitch; //Calculate the pulse for esc 2 (front-right - CCW)
      esc_3 = throttle  - pid_output_pitch; //Calculate the pulse for esc 3 (rear-right - CW)
      esc_4 = throttle  - pid_output_pitch; //Calculate the pulse for esc 4 (rear-left - CCW)

      esc_1 = throttle - pid_output_roll + pid_output_pitch; //Calculate the pulse for esc 1 (front-left - CW)//Currently +ve y axis is designated as front
      esc_2 = throttle + pid_output_roll + pid_output_pitch; //Calculate the pulse for esc 2 (front-right - CCW)//offset of +50
      esc_3 = throttle + pid_output_roll - pid_output_pitch; //Calculate the pulse for esc 3 (rear-right - CW)
      esc_4 = throttle - pid_output_roll - pid_output_pitch;  //Calculate the pulse for esc 4 (rear-left - CCW)//offset of -10

      esc_1 = throttle; //Calculate the pulse for esc 1 (front-left - CW)//Currently +ve y axis is designated as front
      esc_2 = throttle; //Calculate the pulse for esc 2 (front-right - CCW)
      esc_3 = throttle; //Calculate the pulse for esc 3 (rear-right - CW)
      esc_4 = throttle; //Calculate the pulse for esc 4 (rear-left - CCW)

      //pid_output_roll is added or subtracted according to current co-ordinate system(Left hand rule)
    esc_1 = throttle - pid_output_roll + pid_output_pitch ; //Calculate the pulse for esc 1 (front-left - CW)//Currently +ve y axis is designated as front
    esc_2 = throttle + pid_output_roll + pid_output_pitch ; //Calculate the pulse for esc 2 (front-right - CCW)
    esc_3 = throttle + pid_output_roll - pid_output_pitch ; //Calculate the pulse for esc 3 (rear-right - CW)
    esc_4 = throttle - pid_output_roll - pid_output_pitch ; //Calculate the pulse for esc 4 (rear-left - CCW)



  */
  //pid_output_roll is added or subtracted according to current co-ordinate system(Left hand rule)
  esc_1 = throttle - pid_output_roll + pid_output_pitch ; //Calculate the pulse for esc 1 (front-left - CW)//Currently +ve y axis is designated as front
  esc_2 = throttle + pid_output_roll + pid_output_pitch ; //Calculate the pulse for esc 2 (front-right - CCW)
  esc_3 = throttle + pid_output_roll - pid_output_pitch ; //Calculate the pulse for esc 3 (rear-right - CW)
  esc_4 = throttle - pid_output_roll - pid_output_pitch ; //Calculate the pulse for esc 4 (rear-left - CCW)



  if (esc_1 < 1100) esc_1 = 1100;                                         //Keep the motors running.
  if (esc_2 < 1100) esc_2 = 1100;                                         //Keep the motors running.
  if (esc_3 < 1100) esc_3 = 1100;                                         //Keep the motors running.
  if (esc_4 < 1100) esc_4 = 1100;                                         //Keep the motors running.

  if (esc_1 > 1800)esc_1 = 1800;                                          //Limit the esc-1 pulse to 1900.
  if (esc_2 > 1800)esc_2 = 1800;                                          //Limit the esc-2 pulse to 1900.
  if (esc_3 > 1800)esc_3 = 1800;                                          //Limit the esc-3 pulse to 1900.
  if (esc_4 > 1800)esc_4 = 1800;                                          //Limit the esc-4 pulse to 1900.

  /*
    if (restart_no > 1 && start == 3 && restart_time <  7000000) {
      /*
        unsigned long CurrentTime = millis();
        unsigned long ElapsedTime = CurrentTime - StartTime;

      if()
      restart_time1 = micros();
      restart_time = restart_time1 - restart_time;

      pwm(0, 0, 0, 0);
    }
    else {
      pwm(esc_1, esc_2, esc_3, esc_4);
    }
  */

#ifdef prop_stop
  pwm(0, 0, 0, 0);
#endif

#ifndef prop_stop
  pwm(esc_1, esc_2, esc_3, esc_4);
#endif
}

