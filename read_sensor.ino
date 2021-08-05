void readAccel() {
  uint8_t howManyBytesToRead = 6;
  readFrom( DATAX0, howManyBytesToRead, _buff); //read the acceleration data from the ADXL345

  // each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
  // thus we are converting both bytes in to one int
  xacc = (((int)_buff[1]) << 8) | _buff[0];
  yacc = (((int)_buff[3]) << 8) | _buff[2];
  zacc = (((int)_buff[5]) << 8) | _buff[4];

}

void getGyroValues() {

  byte xMSB = readRegister(L3G4200D_Address, 0x29);
  byte xLSB = readRegister(L3G4200D_Address, 0x28);
  gyroRawx = ((xMSB << 8) | xLSB);

  byte yMSB = readRegister(L3G4200D_Address, 0x2B);
  byte yLSB = readRegister(L3G4200D_Address, 0x2A);
  gyroRawy = ((yMSB << 8) | yLSB);

  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  gyroRawz = ((zMSB << 8) | zLSB);
}

void getMag()
{
  byte xMSB = readRegister(Mag_address , 0x03);
  byte xLSB = readRegister(Mag_address , 0x04);
  xMagRaw = ((xMSB << 8) | xLSB);

  byte yMSB = readRegister(Mag_address , 0x07);
  byte yLSB = readRegister(Mag_address , 0x08);
  yMagRaw = ((yMSB << 8) | yLSB);

  byte zMSB = readRegister(Mag_address , 0x05);
  byte zLSB = readRegister(Mag_address , 0x06);
  zMagRaw = ((zMSB << 8) | zLSB);
}


void writeTo(byte address, byte val) {
  Wire.beginTransmission(DEVICE); // start transmission to device
  Wire.write(address);             // send register address
  Wire.write(val);                 // send value to write
  Wire.endTransmission();         // end transmission
}

// Reads num bytes starting from address register on device in to _buff array
void readFrom(byte address, int num, byte _buff[]) {
  Wire.beginTransmission(DEVICE); // start transmission to device
  Wire.write(address);             // sends address to read from
  Wire.endTransmission();         // end transmission

  Wire.beginTransmission(DEVICE); // start transmission to device
  Wire.requestFrom(DEVICE, num);    // request 6 bytes from device

  int i = 0;
  while (Wire.available())        // device may send less than requested (abnormal)
  {
    _buff[i] = Wire.read();    // receive a byte
    i++;
  }
  Wire.endTransmission();         // end transmission
}



void writeRegister(int deviceAddress, byte address, byte val) {
  Wire.beginTransmission(deviceAddress); // start transmission to device
  Wire.write(address);       // send register address
  Wire.write(val);         // send value to write
  Wire.endTransmission();     // end transmission
}

int readRegister(int deviceAddress, byte address) {

  int v;
  Wire.beginTransmission(deviceAddress);
  Wire.write(address); // register to read
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress, 1); // read a byte

  while (!Wire.available()) {
    // waiting
  }

  v = Wire.read();
  return v;
}

