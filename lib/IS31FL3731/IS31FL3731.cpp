
// IS31FL3731 library code
#include <IS31FL3731.h>


/// @brief Constructor for IS31FL3731 LED matrix driver.
/// @param address I2C address of the chip.
IS31FL3731::IS31FL3731( uint8_t address ) {

    _i2c_address = ( address & 0b01111111 );

}










