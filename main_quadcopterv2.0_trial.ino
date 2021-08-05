
#include <Wire.h>
#include "all_variables.h"
#include "all_debug.h"



void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)

#ifdef useSerial4DEBUG
  Serial.begin(115200);  // start serial for output. Make sure you set your Serial Monitor to the same!
#endif

  /*-------------------interupt config--------------------*/
  PCICR |= (1 << PCIE0);                                       //Set PCIE0 to enable PCMSK0 scan.
  PCMSK0 |= (1 << PCINT0);                                     //Set PCINT0 (digital input 8) to trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT1);                                     //Set PCINT1 (digital input 9)to trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT2);                                     //Set PCINT2 (digital input 10)to trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT3);                                     //Set PCINT2 (digital input 11)to trigger an interrupt on state change.

  //Interrupt for Ultrasonic Sensor
  PCICR |= (1 << PCIE2);                                       //Set PCIE2 to enable PCMSK2 scan.
  PCMSK2 |= (1 << PCINT18);                                    //Set PCINT18 (digital input 2) to trigger an interrupt on state change.


  /*---------------------fast wire -----------------------*/
  TWSR = 0;//
  TWBR = 12;//
  TWCR = 1 << TWEN;//

  /*-----------------Port D n B as output-----------------*/
  DDRD |= B11111000;                                           //Configure digital port 3, 4, 5, 6 and 7 as output.Pin 3 is for ultrasonic
  DDRB |= B00110000;                                           //Configure digital port 12 and 13 as output.
  //Serial.flush();

  /*------------------Config Sensor ACC-------------------*/

  writeTo(DATA_FORMAT, 0x01);
  //Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register.
  writeTo(POWER_CTL, 0x00);
  writeTo(POWER_CTL, 0x16);
  writeTo(POWER_CTL, 0x08);

  /*------------------Config Sensor GYRO-------------------*/
  //Serial.println("Starting up SuperCopter");
  setupL3G4200D(500); // Configure L3G4200  - 250, 500 or 2000 deg/sec

  /*-------------------Config Sensor MAG-------------------*/
  //Mode register(Continuous Mode),1.3Ga;
  writeRegister(Mag_address, 0x02, 0x00);
  //status register,(LOCK mode) updates the reg only when whole data has been read
  writeRegister(Mag_address, 0x09, 0x02);

  /*----------------------calibration----------------------*/

  calibrate();
  // compass_offset_calibration();//offset calibration for Magnetometer

  battery_voltage =   (analogRead(0) + 65) * 1.2317; // checking battery voltage
}



void loop()
{
  //rearmESC();   // for rearming the ESC
  //rece_check(); // debugging transmitter
  //PORTB = 0X10;
  //batt_check();

  start_time = micros();
  timeStep = (start_time - loop_time) / 1000000.00;
  loop_time = start_time;

  //stick_seq();

  get_sens();

  setpoint();
  if (start == 3) {
    throttle = receiver_input_channel_3;
    //throttle_check();
    pidCalc();
  }
  esc_update();
  serialPrint();

  //Stopping the motors: throttle low.
  if (start == 3 && receiver_input_channel_3 < 1180 )start = 0;

  count++;
  //PORTB = 0X00;

}

