void rearmESC()
{
  Serial.print("ReARMing ESC");
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      PORTB = 0x00;
      delay(100);
      PORTB = 0x10;
      delay(100);
    }
    delay(1000);
  }
  unsigned long time_pwm = millis();
  while (millis() - time_pwm <= 10000) pwm(2000, 2000, 2000, 2000);

  delay(1000);

  time_pwm = millis();
  while (millis() - time_pwm <= 5000) pwm(1000, 1000, 1000, 1000);

  for (int i = 0; i < 5; i++) {
    PORTB = 0x00;
    delay(1000);
    PORTB = 0x10;
    delay(1000);
  }
  while (1);
}
