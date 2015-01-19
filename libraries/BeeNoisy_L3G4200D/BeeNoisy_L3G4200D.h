// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _BeeNoisy_L3G4200D_H_
#define _BeeNoisy_L3G4200D_H_
#include "Arduino.h"
//add your includes for the project BeeNoisy_L3G4200D here
#include <Wire.h>

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project BeeNoisy_L3G4200D here

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

//I2C address of the L3G4200D
#define L3G4200D_Address 105

class BeeNoisy_L3G4200D {
public:
    int begin(int scale);
    void getGyroValues(int *tempX, int *tempY, int *tempZ);
    void getGyroValueOfX(int *tempX);
    void getGyroValueOfY(int *tempY);
    void getGyroValueOfZ(int *tempZ);
private:
    // write a value to I2C address with address and value
    void writeRegister(int deviceAddress, byte address, byte val);
    // Read a value from
    int readRegister(int deviceAddress, byte address);
};

//Do not add code below this line
#endif
/* _BeeNoisy_L3G4200D_H_ */
