#include "ad5694r.h"

// I don't think we will need to write to input and then update DAC in separate commands! I'll do them together with 0b0011 command
void setDAC(uint8_t dac_addr, uint8_t* value){
    uint8_t buf[3];
    buf[0] = (WriteUpdate << 4) | dac_addr;
    buf[1] = value[0];
    buf[2] = value[1];
    i2c_write_blocking(i2c1, I2C_ADDR, buf, 3, false); // check msb/lsb
}

void setPowerState(uint8_t A_State, uint8_t B_State, uint8_t C_State, uint8_t D_State){    
    uint8_t buf[3];
    buf[0] = (PwrDwn_PwrUP << 4) | (0b0000);
    buf[1] = 0;
    buf[2] = (D_State << 6) | (C_State << 4) | (B_State << 2) | A_State;
    i2c_write_blocking(i2c1, I2C_ADDR, buf, 3, false);
}

int main(){

    AD5696 ad5694r;
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
    ad5694r.setPowerState(/*DAC A*/ stateNormal, /*DAC B*/ stateNormal, /*DAC C*/ stateNC, /*DAC D*/ stateNC);
    
    // Table 14 & 15 - Disable internal reference, since we are using an external VERF
    

    // Set DAC


    return 0;

}