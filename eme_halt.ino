//-------------------------------emergengy halt------------------------------------------

void eme_halt() {
  float throt;
  throt = receiver_input_channel_3;
  while (throt < 1060) {
    pwm(0, 0, 0, 0);
    PORTB = 0x00;
    delay(500);
    PORTB = 0x10;
    delay(500);
    throt = receiver_input_channel_3;
  }
  PORTB = 0x00;
}

