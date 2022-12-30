
#ifndef IS31FL3731_HEADER_GUARD
#define IS31FL3731_HEADER_GUARD



// IS31FL3731 library header

// include Arduino header
#include <Arduino.h>

// Wire library
#include <Wire.h>
#define wire Wire




// functions required

// control functions

// shutdown()
// get or set shutdown mode.


// page fuctions

// selectpage()
// select animation page to write to

// pixel functions

// setpixel()
// turn an individual pixel on or off.




class IS31FL3731
{
private:
    /// @brief i2c address of chip
    uint8_t _i2c_address;

public:
    /// @brief Constructor for IS31FL3731 LED matrix driver.
    /// @param address I2C address of the chip.
    IS31FL3731( uint8_t address );
    
};








#endif
