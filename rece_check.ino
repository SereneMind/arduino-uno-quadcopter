void rece_check() {
  while (1) {
    float duration1 = pulseIn(8, HIGH);
    float duration2 = pulseIn(9, HIGH);
    float duration3 = pulseIn(10, HIGH);
    float duration4 = pulseIn(11, HIGH);


    Serial.print("\tduration1 ");
    Serial.print(duration1);
    Serial.print("\tduration2 ");
    Serial.print(duration2);
    Serial.print("\tduration3 ");
    Serial.print(duration3);
    Serial.print("\tduration4 ");
    Serial.println(duration4);
  }

}

