


// include my header
#include <pimoroni_11x7matrix.h>




/// @brief Constructor for Pimoroni 11x7 Matrix Driver
Pimoroni_11x7matrix::Pimoroni_11x7matrix() {

}






/// @brief Set the i2c address and perform any setup required.
/// @param new_i2c_address The i2c address of the chip.
void Pimoroni_11x7matrix::begin( uint8_t new_i2c_address ) {

}







/// @brief Write the pixel buffer to a frame on the chip.
/// @param framenumber The number of the frame to write to. 0-7.
void Pimoroni_11x7matrix::writepixelbuffertoframe( uint8_t framenumber ) {

}








/// @brief Set the chips frame display pointer
/// @param framenumber The number of the frame to display. 0-7.
void Pimoroni_11x7matrix::framedisplaypointerset( uint8_t framenumber ) {

}


/// @brief Fetches the current frame display pointer from the chip.
/// @return The current frame display pointer as a uint8_t. 0-7.
uint8_t Pimoroni_11x7matrix::framedisplaypointerget() {
    return 0;
}











/// @brief Sets the pixel buffers for state, blink and pwm to all zero.
void Pimoroni_11x7matrix::clearallpixelbuffers() {

    // for each column of pixel buffers
    for ( uint8_t x = 0 ; x < 11 ; x++ ) {

        // set the whole row of _ledstate to zero.
        _ledstate[ x ] = 0x00;

        // set the whole row of _ledblinkstate to zero.
        _ledblinkstate[ x ] = 0x00;

        // for each pwm value in the row
        for ( uint8_t y = 0 ; y < 7 ; y++ ) {

            // set it to zero.
            _ledpwmstate[ x ][ y ] = 0x00;

        }

    }

    // all done, return to caller.
    return;

}




/// @brief Sets the pixel buffer for state to all zero.
void Pimoroni_11x7matrix::clearstatepixelbuffer() {

    // for each element in the _ledstate array...
    for ( uint8_t i = 0 ; i < 11 ; i++ ) {

        // set it to zero.
        _ledstate[ i ] = 0x00;

    }

    // all done, return to caller.
    return;

}



/// @brief Sets the pixel buffer for blink state to all zero.
void Pimoroni_11x7matrix::clearblinkpixelbuffer() {

    // for each element in the _ledblinkstate array...
    for ( uint8_t i = 0 ; i < 11 ; i++ ) {

        // set it to zero
        _ledblinkstate[ i ] = 0x00;

    }

    // all done, return to caller.
    return;

}



/// @brief Sets the pixel buffer for pwm value to all zero.
void Pimoroni_11x7matrix::clearpwmpixelbuffer() {

    // for each column in the _ledpwmstate array...
    for ( uint8_t x = 0 ; x < 11 ; x++ ) {

        // for each row in the _ledpwmstate array...
        for ( uint8_t y = 0 ; y < 7 ; y++ ) {

            // set it to zero.
            _ledpwmstate[ x ][ y ] = 0x00;

        }

    }

    // all done, return to caller.
    return;
}




/// @brief Sets a pixel to on or off in the pixel buffer.
/// @param xpos The x position, with zero at the bottom left.
/// @param ypos The y position, with the zero at the bottom left.
/// @param state The state, 1 for on, 0 for off.
void Pimoroni_11x7matrix::pixelset( uint8_t xpos , uint8_t ypos , uint8_t state ) {

    // check if we are turning the bit on, or off.
    if ( state ) {

        // set bit to 1
        _ledstate[ xpos ] |= ( 0b00000001 << ypos );

    }
    else {

        // set bit to 0
        _ledstate[ xpos ] &= ~( 0b00000001 << ypos );
    }

    // all done, return to caller.
    return;
}



/// @brief Gets the value of a pixel from the pixel buffer.
/// @param xpos The x position, with zero at the bottom left.
/// @param ypos The y position, with zero at the bottom left.
/// @return The state of the pixel as a uint8_t.  0 for off, 1 for on.
uint8_t Pimoroni_11x7matrix::pixelget( uint8_t xpos , uint8_t ypos ) {

    // return the bit for this pixel as a uint8_t.
    return (uint8_t)( ( _ledstate[ xpos ] >> ypos ) & 0b00000001 );

}





/// @brief Set the blink flag for a pixel on or off in the pixel buffer.
/// @param xpos The x position, with zero at the bottom left.
/// @param ypos The y position, with zero at the bottom left.
/// @param state The state of the blink flag as a uint8_t.  0 for off, 1 for on.
void Pimoroni_11x7matrix::pixelblinkset( uint8_t xpos , uint8_t ypos , uint8_t state ){

    // check if we are turning the bit on, or off.
    if ( state ) {

        // set bit to 1
        _ledblinkstate[ xpos ] |= ( 0b00000001 << ypos );

    }
    else {

        // set bit to 0
        _ledblinkstate[ xpos ] &= ~( 0b00000001 << ypos );
    }

    // all done, return to caller.
    return;

}

/// @brief Get the state of a pixels blink flag from the pixel buffer.
/// @param xpos The x position, with zero at the bottom left.
/// @param ypos The y position, with zero at the bottom left.
/// @return The state of the pixel as a uint8_t.  0 for off, 1 for on.
uint8_t Pimoroni_11x7matrix::pixelblinkget( uint8_t xpos , uint8_t ypos ) {
    
    // return the bit for this pixel as a uint8_t.
    return (uint8_t)( ( _ledblinkstate[ xpos ] >> ypos ) & 0b00000001 );

}





/// @brief Set the pwm value for a pixel in the pixel buffer
/// @param xpos The x position of the pixel, with zero at the bottom left.
/// @param ypos The y position of the pixel, with zero at the bottom left.
/// @param state The pwm value to set, as a uint8_t.  0 is full off, 255 is full on.
void Pimoroni_11x7matrix::pixelpwmset( uint8_t xpos , uint8_t ypos , uint8_t state ) {

    // set the pixel pwm value in the array
    _ledpwmstate[ xpos ][ ypos ] = state;

    // all done, return to caller.
    return;

}

/// @brief Get the pwm value for a pixel from the pixel buffer.
/// @param xpos The x position of the pixel, with zero at the bottom left.
/// @param ypos The y position of the pixel, with zero at the bottom left.
/// @return The pwm value of the pixel as a uint8_t.  0 is fully off, 255 is fully on.
uint8_t Pimoroni_11x7matrix::pixelpwmget( uint8_t xpos , uint8_t ypos ) {

    // return the byte for this pixel as a uint8_t.
    return _ledpwmstate[ xpos ][ ypos ];

}














