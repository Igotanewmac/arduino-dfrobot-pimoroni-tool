

#ifndef PIMORONI_11X7MATRIX_HEADER_GUARD
#define PIMORONI_11X7MATRIX_HEADER_GUARD


// header for 11x7 matrix board by pimoroni

// pull in the arduino headers
#include <Arduino.h>

// pull in chip driver
#include "IS31FL3731.h"


class Pimoroni_11x7matrix {


    private:

    uint8_t ledstate[11];
    uint8_t ledblinkstate[11];
    uint8_t ledpwmstate[77];


    public:

    /// @brief Constructor for Pimoroni 11x7 Matrix Driver
    /// @param _i2c_address The i2c address of the chip.
    Pimoroni_11x7matrix( uint8_t _i2c_address );

    



};






























#endif

