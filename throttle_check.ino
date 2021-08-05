void throttle_check() {

  //----------checking whether quad is UP-----------
  if (throttle > 1550) {
    i_am_up = HIGH;  //setting of hovering pwm 1550
    throttle_ctrl = 1550;
  }
  if (throttle < 1250) i_am_up = LOW;// setting of lower limit pwm

  //------------------Main Control------------------
  if (start_descend == LOW)throttle = receiver_input_channel_3;
  if (start_descend == HIGH)throttle = descend_ctrl();

  //check_throttle = throttle - previous_throttle;//for postive or negative transtition
  //avoiding the above program as our response as compared to uController is very-3
  //less that can lead to less efficient result

  //-------------shifting of control of throttle-----------------
  if (receiver_input_channel_3 < 1550 && i_am_up == HIGH)start_descend = HIGH;
  if (receiver_input_channel_3 > 1550)start_descend = LOW;
}

inline int descend_ctrl() {

  if (count % 200 == 0) {
    if (throttle_ctrl > 1490)throttle_ctrl = throttle_ctrl - 1;
    else throttle_ctrl = 1490;
  }
  return throttle_ctrl;
}

/*
  inline int descend_ctrl(int throttle_ctrl) {

  uss();

  return throttle_ctrl;

  }
   countP = count - countP;
  if (countP < 250)throttle_ctrl = 1550;
  else {
*/
