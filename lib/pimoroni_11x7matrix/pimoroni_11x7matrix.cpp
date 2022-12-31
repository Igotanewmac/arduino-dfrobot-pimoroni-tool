


// include my header
#include <pimoroni_11x7matrix.h>


Pimoroni_11x7matrix::Pimoroni_11x7matrix() {

}



/// @brief Shorthand setup for seti2caddress, software reset ( off and back on ) and clear all.
/// @param new_i2c_address The i2c address of the chip.
void Pimoroni_11x7matrix::begin( uint8_t new_i2c_address ) {

    _i2c_address = new_i2c_address;

}




/// @brief Clears the buffer to all off.
void Pimoroni_11x7matrix::clear() {

    // for each column
    for ( uint8_t xpos = 0 ; xpos < 12 ; xpos++ ) {

        _ledstate[ xpos ] = 0x00;
        _ledblinkstate[ xpos ] = 0x00;

        for ( uint8_t ypos = 0 ; ypos < 8 ; ypos++ ) {

            _ledpwmstate[ xpos ][ ypos ] = 0x00;

        }

    }

    // all done!
    return;

}








/// @brief Sets a pixel to on or off.
/// @param xpos The x position, with zero at the bottom left.
/// @param ypos The y position, with the zero at the bottom left.
/// @param state The state, 1 for on, 0 for off.
void Pimoroni_11x7matrix::pixelset( uint8_t xpos , uint8_t ypos , uint8_t state ) {

    if ( state ) {
        _ledstate[ xpos ] |= ( 0b00000001 << ypos );
    }
    else {
        _ledstate[ xpos ] &= !( 0b00000001 << ypos );
    }

}














