/*-----------------------------PWM Generation-------------------------------------------------*/
void pwm(int escIN1, int escIN2, int escIN3, int escIN4) {

  esc_1 = escIN1;
  esc_2 = escIN2;
  esc_3 = escIN3;
  esc_4 = escIN4;

  //All the information for controlling the motor's is available.
  //The refresh rate is 250Hz. That means the esc's need there pulse every 4ms.
  while (micros() - esc_timer < 5000);                                     //We wait until 5000us are passed.
  esc_timer = micros();                                                    //Set the timer for the next loop.

  PORTD |= B11110000;                                                       //Set digital outputs 4,5,6 and 7 high.
  timer_channel_1 = esc_1 + esc_timer;                                     //Calculate the time of the faling edge of the esc-1 pulse.
  timer_channel_2 = esc_2 + esc_timer;                                     //Calculate the time of the faling edge of the esc-2 pulse.
  timer_channel_3 = esc_3 + esc_timer;                                     //Calculate the time of the faling edge of the esc-3 pulse.
  timer_channel_4 = esc_4 + esc_timer;                                     //Calculate the time of the faling edge of the esc-4 pulse.

  while (PORTD >= 16) {                                                     //Stay in this loop until output 4,5,6 and 7 are low.
    esc_loop_timer = micros();                                              //Read the current time.
    if (timer_channel_1 <= esc_loop_timer)PORTD &= B11101111;               //Set digital output 4 to low if the time is expired.
    if (timer_channel_2 <= esc_loop_timer)PORTD &= B11011111;               //Set digital output 5 to low if the time is expired.
    if (timer_channel_3 <= esc_loop_timer)PORTD &= B10111111;               //Set digital output 6 to low if the time is expired.
    if (timer_channel_4 <= esc_loop_timer)PORTD &= B01111111;               //Set digital output 7 to low if the time is expired.
  }
}


