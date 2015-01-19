// Do not remove the include below
#include "BeeNoisy_L3G4200D.h"

int BeeNoisy_L3G4200D::begin(int scale) {
    //From  Jim Lindblom of Sparkfun's code
    // Enable x, y, z and turn off power down:
    writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);
    // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
    writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);
    // Configure CTRL_REG3 to generate data ready interrupt on INT2
    // No interrupts used on INT1, if you'd like to configure INT1
    // or INT2 otherwise, consult the datasheet:
    writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);
    // CTRL_REG4 controls the full-scale range, among other things:
    if (scale == 250) {
        writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
    } else if (scale == 500) {
        writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
    } else {
        writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
    }
    // CTRL_REG5 controls high-pass filtering of outputs, use it
    // if you'd like:
    writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
    return 0;
}

// read values of gyro from register
void BeeNoisy_L3G4200D::getGyroValues(int *tempX, int *tempY, int *tempZ) {
    getGyroValueOfX(tempX);
    getGyroValueOfY(tempY);
    getGyroValueOfZ(tempZ);
}

// read x value of gyro from register
void BeeNoisy_L3G4200D::getGyroValueOfX(int *tempX) {
    byte xMSB = readRegister(L3G4200D_Address, 0x29);
    byte xLSB = readRegister(L3G4200D_Address, 0x28);
    *tempX = ((xMSB << 8) | xLSB);
}

// read y value of gyro from register
void BeeNoisy_L3G4200D::getGyroValueOfY(int *tempY) {
    byte yMSB = readRegister(L3G4200D_Address, 0x2B);
    byte yLSB = readRegister(L3G4200D_Address, 0x2A);
    *tempY = ((yMSB << 8) | yLSB);
}

// read z value of gyro from register
void BeeNoisy_L3G4200D::getGyroValueOfZ(int *tempZ) {
    byte zMSB = readRegister(L3G4200D_Address, 0x2D);
    byte zLSB = readRegister(L3G4200D_Address, 0x2C);
    *tempZ = ((zMSB << 8) | zLSB);
}

void BeeNoisy_L3G4200D::writeRegister(int deviceAddress, byte address, byte val) {
    // start transmission to device
    Wire.beginTransmission(deviceAddress);
    // send register address
    Wire.write(address);
    // send value to write
    Wire.write(val);
    // end transmission
    Wire.endTransmission();
}

int BeeNoisy_L3G4200D::readRegister(int deviceAddress, byte address) {
    int v;
    Wire.beginTransmission(deviceAddress);
    // register to read
    Wire.write(address);
    Wire.endTransmission();
    // read a byte
    Wire.requestFrom(deviceAddress, 1);
    while (!Wire.available())
        // waiting
        ;
    v = Wire.read();
    return v;
}
