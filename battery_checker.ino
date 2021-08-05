void batt_check()
{


  /***********************************battery checker***********************************/
  //Load the battery voltage to the battery_voltage variable.
  //65 is the voltage compensation for the diode.
  //12.6V equals ~5V @ Analog 0.
  //12.6V equals 1023 analogRead(0).
  //1260 / 1023 = 1.2317.
  //The variable battery_voltage holds 1050 if the battery voltage is 10.5V.
  //The battery voltage is needed for compensation.
  //A complementary filter is used to reduce noise.
  //0.09853 = 0.08 * 1.2317.
  /**************************************************************************************/

  battery_voltage = battery_voltage * 0.92 + (analogRead(0) + 65) * 0.09853;

  //Blink the led if battery voltage is to low and turn the esc down

  if (battery_voltage < 1200 && battery_voltage > 950 ) PORTB = 0X00;
  else {
    while (battery_voltage < 950)
    {
      pwm(0, 0, 0, 0);
      PORTB = 0X10;
      delay(100);
      PORTB = 0X00;
      delay(100);
      battery_voltage = battery_voltage * 0.92 + (analogRead(0) + 65) * 0.09853;
    }
  }
}
