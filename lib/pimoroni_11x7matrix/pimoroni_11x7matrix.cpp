


// include my header
#include <pimoroni_11x7matrix.h>




/// @brief Constructor for Pimoroni 11x7 Matrix Driver
Pimoroni_11x7matrix::Pimoroni_11x7matrix() {

}






/// @brief Set the i2c address and perform any setup required.
/// @param new_i2c_address The i2c address of the chip.
void Pimoroni_11x7matrix::begin( uint8_t new_i2c_address ) {

    // make sure the wire library is started.
    wire.begin();

    // store my i2c address for later.
    _i2c_address = new_i2c_address;

    // all done, return to caller.
    return;

}




/// @brief Write a single byte of data to the chip.
/// @param framenumber The number of the frame to write to. 0x00-0x07 Animation. 0x0B Control.
/// @param address The address within the frame to write to.
/// @param data The data byte to write to the chip.
void Pimoroni_11x7matrix::_chipwritebyte( uint8_t framenumber , uint8_t address , uint8_t data ) {


    // say hello to the chip
    wire.beginTransmission( _i2c_address );

    // send the frame number
    wire.write( 0xFD );
    wire.write( framenumber );

    // say goodbye to the chip.
    wire.endTransmission();

    // say hello to the chip again...
    wire.beginTransmission( _i2c_address );

    // send the address
    wire.write( address );

    // send the data
    wire.write( data );

    // say goodbye
    wire.endTransmission();

    // all done, return to caller
    return;
    
}


/// @brief Read a single byte of data from the chip.
/// @param framenumber The number of the frame to read from. 0x00-0x07 Animation. 0x0B Control.
/// @param address The address within the frame to read from.
/// @return The data byte rturned from the chip as a uint8_t.
uint8_t Pimoroni_11x7matrix::_chipreadbyte( uint8_t framenumber , uint8_t address ) {

    // say hello to the chip
    wire.beginTransmission( _i2c_address );

    // send the frame number
    wire.write( 0xFD );
    wire.write( framenumber );

    // say goodbye to the chip.
    wire.endTransmission();

    // say hello to the chip again...
    wire.beginTransmission( _i2c_address );
    
    // send the address
    wire.write( address );

    // say goodye to the chip
    wire.endTransmission();

    // request one byte back from the chip
    wire.requestFrom( _i2c_address , (uint8_t)(0x01) );

    // wait until that byte is available.
    while( !wire.available() ) { delay(1); };

    // receive one byte back from the chip and return it as a uint8_t.
    return (uint8_t)( wire.read() );

}








/// @brief Sets the software shutdown flag on the chip.
/// @param state The state to set as a uint8_t. 0 = shutdown, 1 = normal operation.
void Pimoroni_11x7matrix::softwareshutdownset( uint8_t state ) {

    _chipwritebyte( IS31FL3731_PAGE_CONTROL , IS31FL3731_ADDRESS_SOFTWARESHUTDOWN , state );

}

/// @brief Gets the software shutdown flag from the chip.
/// @return the flag as a uint8_t. 0 = shutdown, 1 = normal operation.
uint8_t Pimoroni_11x7matrix::softwareshutdownget() {

    return _chipreadbyte( IS31FL3731_PAGE_CONTROL , IS31FL3731_ADDRESS_SOFTWARESHUTDOWN );

}


/// @brief Sets the display mode on the chip.
/// @param mode The mode number to set. 0b00 = picture mode, 0b01 = auto frame play, 0b1x = audio frame play.
void Pimoroni_11x7matrix::displaymodeset( uint8_t mode ) {


    // read out the current byte
    uint8_t tempbyte = _chipreadbyte( IS31FL3731_PAGE_CONTROL , IS31FL3731_ADDRESS_CONFIG_REGISTER );

    // add in my data
    tempbyte &= 0b11100111;
    tempbyte |= ( mode << 3 );

    _chipwritebyte( IS31FL3731_PAGE_CONTROL , IS31FL3731_ADDRESS_CONFIG_REGISTER , tempbyte );

    // all done, return to caller.
    return;

}







/// @brief Gets the display mode from the chip.
/// @return The current display mode number as a uint8_t. 0b00 = picture mode, 0b01 = auto frame play, 0b1x = audio frame play.
uint8_t Pimoroni_11x7matrix::displaymodeget() {

    uint8_t tempbyte = _chipreadbyte( IS31FL3731_PAGE_CONTROL , IS31FL3731_ADDRESS_CONFIG_REGISTER );

    // get our data out
    tempbyte &= 0b00011000;
    
    return (uint8_t)( tempbyte >> 3 );

}



















/// @brief Write the pixel buffer to a frame on the chip.
/// @param framenumber The number of the frame to write to. 0-7.
void Pimoroni_11x7matrix::writepixelbuffertoframe( uint8_t framenumber ) {



    // write the buffer line by line to map easily

    _chipwritebyte( 0x00 , 0x00 , _ledstate[ 0  ] );
    _chipwritebyte( 0x00 , 0x01 , _ledstate[ 1  ] );
    _chipwritebyte( 0x00 , 0x02 , _ledstate[ 2  ] );
    _chipwritebyte( 0x00 , 0x03 , _ledstate[ 3  ] );
    _chipwritebyte( 0x00 , 0x04 , _ledstate[ 4  ] );
    _chipwritebyte( 0x00 , 0x05 , _ledstate[ 5  ] );
    _chipwritebyte( 0x00 , 0x06 , _ledstate[ 6  ] );
    _chipwritebyte( 0x00 , 0x07 , _ledstate[ 7  ] );
    _chipwritebyte( 0x00 , 0x08 , _ledstate[ 8  ] );
    _chipwritebyte( 0x00 , 0x09 , _ledstate[ 9  ] );
    _chipwritebyte( 0x00 , 0x0A , _ledstate[ 10 ] );
    

    // write the blink state buffer line by line to map easily

    _chipwritebyte( 0x00 , 0x12 , _ledblinkstate[ 0  ] );
    _chipwritebyte( 0x00 , 0x13 , _ledblinkstate[ 1  ] );
    _chipwritebyte( 0x00 , 0x14 , _ledblinkstate[ 2  ] );
    _chipwritebyte( 0x00 , 0x15 , _ledblinkstate[ 3  ] );
    _chipwritebyte( 0x00 , 0x16 , _ledblinkstate[ 4  ] );
    _chipwritebyte( 0x00 , 0x17 , _ledblinkstate[ 5  ] );
    _chipwritebyte( 0x00 , 0x18 , _ledblinkstate[ 6  ] );
    _chipwritebyte( 0x00 , 0x19 , _ledblinkstate[ 7  ] );
    _chipwritebyte( 0x00 , 0x1A , _ledblinkstate[ 8  ] );
    _chipwritebyte( 0x00 , 0x1B , _ledblinkstate[ 9  ] );
    _chipwritebyte( 0x00 , 0x1C , _ledblinkstate[ 10 ] );
    


    // write out the pwm state buffer line by line to map easily

    uint8_t startaddress = 0x24;

    for ( uint8_t x = 0 ; x < 11 ; x++ ) {

        for ( uint8_t y = 0 ; y < 7 ; y++ ) {

            _chipwritebyte( 0x00 , startaddress + y , _ledpwmstate[ x ][ y ] );

            
        }

        startaddress += 8;

    }



    // now all done, return to caller.
    return;


}


















/// @brief Set the chips frame display pointer
/// @param framenumber The number of the frame to display. 0-7.
void Pimoroni_11x7matrix::framedisplaypointerset( uint8_t framenumber ) {
    _chipwritebyte( IS31FL3731_PAGE_CONTROL , IS31FL3731_ADDRESS_PICTURE_DISPLAY_REG , framenumber );
}


/// @brief Fetches the current frame display pointer from the chip.
/// @return The current frame display pointer as a uint8_t. 0-7.
uint8_t Pimoroni_11x7matrix::framedisplaypointerget() {
    return _chipreadbyte( IS31FL3731_PAGE_CONTROL , IS31FL3731_ADDRESS_PICTURE_DISPLAY_REG );
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














