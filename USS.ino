void uss() {

  PORTD |= 0b00000000;
  delayMicroseconds(2);
  PORTD |= 0b00001000;
  delayMicroseconds(5);
  PORTD &= 0b11110111;

  //pinMode(2, INPUT);
  //float duration = pulseIn(2, HIGH);// put up an interrupt instead of pulseIN

  altitude = duration / 29 / 2;

#ifdef ultrasonic
  Serial.print(altitude);
  Serial.println(" cm");
#endif

}
