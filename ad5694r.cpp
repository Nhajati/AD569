#include "ad5694r.h"


void  AD5696::initialize(){
    // DAC reset pin
    gpio_init(RESET_GPIO);
    gpio_set_dir(RESET_GPIO, GPIO_OUT);
    gpio_put(RESET_GPIO, 1); // Active low pin

    // DAC LDAC pin
    gpio_init(LDAC_GPIO);
    gpio_set_dir(LDAC_GPIO, GPIO_OUT); 
    gpio_put(LDAC_GPIO, 0); // Table 13

    // Init i2c1 controller
    i2c_init(i2c1, 1000000);

    // Set up pins 18 and 19
    gpio_set_function(18, GPIO_FUNC_I2C);
    gpio_set_function(19, GPIO_FUNC_I2C);
    gpio_pull_up(18);
    gpio_pull_up(19);

    // If you don't do anything before initializing a display pi pico is too fast and starts sending
    // commands before the screen controller had time to set itself up, so we add an artificial delay for
    // ad5694r to set itself up
    sleep_ms(250);

    // Table 10 - Power-down mode for DAC C and DAC D, since we're only using A and B channels
    setPowerState(/*DAC A*/ stateNormal, /*DAC B*/ stateNormal, /*DAC C*/ stateNC, /*DAC D*/ stateNC);
    
    // Table 14 & 15 - Disable internal reference, since we are using an external VERF
    internalRefDisabled(true);
}

// I don't think we will need to write to input and then update DAC in separate commands! I'll do them together with 0b0011 command
void AD5696::setDAC(uint8_t dac_addr, uint16_t value){
    uint8_t msb = (value >> 8) & 0XFF;
    uint8_t lsb = value & 0xFF;
    uint8_t buf[3];
    buf[0] = (WriteUpdate << 4) | dac_addr;
    buf[1] = msb;
    buf[2] = lsb;
    i2c_write_blocking(i2c1, I2C_ADDR, buf, 3, false); // check msb/lsb
}

void AD5696::setPowerState(uint8_t A_State, uint8_t B_State, uint8_t C_State, uint8_t D_State){    
    uint8_t buf[3];
    buf[0] = (PwrDwn_PwrUP << 4) | (0b0000);
    buf[1] = 0;
    buf[2] = (D_State << 6) | (C_State << 4) | (B_State << 2) | A_State;
    i2c_write_blocking(i2c1, I2C_ADDR, buf, 3, false);
}

void AD5696::internalRefDisabled (bool refDisabled){
    uint8_t buf[3];
    buf[0] = (InternalRefSetupReg << 4) | (0b0000);
    buf[1] = 0;
    buf[2] = refDisabled;
    i2c_write_blocking(i2c1, I2C_ADDR, buf, 3, false);
}

void AD5696::reset(uint pin_gp){
    gpio_put(pin_gp, 0);
    sleep_ms(10); //is this time ok?
    gpio_put(RESET_GPIO, 1);
}

int main(){

    stdio_init_all();

    AD5696 ad5694r;

    ad5694r.initialize();    

    // Set DAC
    // probably should put it inside an interrupt, to have ref and meas at the same instance saved.
    
    // Test values for DAC A and DAC B
    uint16_t dacAValue = 2048;  // Example value for DAC A
    uint16_t dacBValue = 4095;  // Example value for DAC B

    ad5694r.setDAC(CH_A, dacAValue);
    ad5694r.setDAC(CH_B, dacBValue);

    while (1)
    {
    /* code */
    }

    return 0;

}