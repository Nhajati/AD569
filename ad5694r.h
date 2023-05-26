// #include <Wire.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define DAC_A    (0b0000)
#define DAC_B    (0b0001)
#define DAC_C    (0b0010)
#define DAC_D    (0b0011)

// Table 8 - Address Commands
#define CH_NONE (0b0000)
#define CH_A    (0b0001)
#define CH_B    (0b0010)
#define CH_C    (0b0100)
#define CH_D    (0b1000)
#define CH_ALL  (0b1111)

#define ADDRMSB (0b01100)  //7 BIT ADDRESS FIRST FIVE MSB 00011 << 2

// Table 7 - Command Definition
#define   NoOperation           (0b0000)
#define   WriteInputRegister    (0b0001)
#define   UpdateDacWithInput    (0b0010)
#define   WriteUpdate           (0b0011)
#define   PwrDwn_PwrUP          (0b0100)
#define   HardwareLDACMask      (0b0101)
#define   SoftwareReset         (0b0110)
#define   InternalRefSetupReg   (0b0111)

// Table 10 - Modes of Operation
#define   stateNormal      (0b0000)
#define   stateGND1k       (0b0001)
#define   state100k     (0b0010)
#define   stateNC          (0b0011)

// Table 9 - Device Address Selection
#define I2C_ADDR          (0b0001100)


class AD5696{
 public:
  AD5696();
  void begin();
  void setDAC(uint8_t dac_addr, uint8_t* value); 
  // void readDAC(uint8_t addr, uint8_t channel, uint8_t operation, uint16_t *returnArray);
  void setPowerState(uint8_t A_State, uint8_t B_State, uint8_t C_State, uint8_t D_State);
  // void setLDACMask(uint8_t addr, uint8_t channel); // Table 12 - we don't care about this, since I am using write and update simultaneously
  void internalRefDisabled(bool refDisabled);
  void reset(uint8_t addr);

};