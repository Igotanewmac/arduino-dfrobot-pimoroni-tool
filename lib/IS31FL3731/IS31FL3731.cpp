
// IS31FL3731 library code
#include <IS31FL3731.h>


/// @brief Constructor for IS31FL3731 LED matrix driver.
/// @param address I2C address of the chip.
IS31FL3731::IS31FL3731( uint8_t address ) {

    _i2c_address = ( address & 0b01111111 );

}



/// @brief Write a byte to the chip
/// @param page The page to write to, 0x0-7 animation, 0xB control.
/// @param address The address within the page to write to.
/// @param data The data to write
void IS31FL3731::write( uint8_t page , uint8_t address , uint8_t data ) {

    // say hello to the chip
    wire.beginTransmission( _i2c_address );

    // send the page
    wire.write( page );

    // send the address
    wire.write( address );

    // send the data
    wire.write( data );

    // say goodbye
    wire.endTransmission();

    // all done, return to caller
    return;

}






/// @brief Read a byte from the chip
/// @param page The page to read from.  0x0-7 animation, 0xB control.
uint8_t IS31FL3731::read( uint8_t page , uint8_t address ) { 
    
    // say hello to the chip
    wire.beginTransmission( _i2c_address );

    // send the page
    wire.write( page );

    // send the address
    wire.write( address );

    // say goodye to the chip
    wire.endTransmission();

    // request one byte back from the chip
    wire.requestFrom( _i2c_address , (uint8_t)(1) );

    // receive one byte back from the chip
    return wire.read();

    // return said byte.
    //return 0;
    
}













