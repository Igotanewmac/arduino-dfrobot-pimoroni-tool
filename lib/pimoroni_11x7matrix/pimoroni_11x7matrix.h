

#ifndef PIMORONI_11X7MATRIX_HEADER_GUARD
#define PIMORONI_11X7MATRIX_HEADER_GUARD


// header for 11x7 matrix board by pimoroni

// pull in the arduino headers
#include <Arduino.h>

// pull in the wire library
#ifndef wire
#include <Wire.h>
#define wire Wire
#endif




// a whole bunch of definitions

// the animation page that refers to the control register
#define IS31FL3731_PAGE_CONTROL 0x0B

// the control register addresses
#define IS31FL3731_ADDRESS_CONFIG_REG 0x00
#define IS31FL3731_ADDRESS_PICTURE_DISPLAY_REG 0x01
#define IS31FL3731_ADDRESS_AUTOPLAY_CONTROL_ONE_REG 0x02
#define IS31FL3731_ADDRESS_AUTOPLAY_CONTROL_TWO_REG 0x03
#define IS31FL3731_ADDRESS_DISPLAY_OPTION_REG 0x05
#define IS31FL3731_ADDRESS_AUDIO_SYNCH_REG 0x05
#define IS31FL3731_ADDRESS_FRAME_STATE_REG 0x07
#define IS31FL3731_ADDRESS_BREATH_CONTROL_ONE_REG 0x08
#define IS31FL3731_ADDRESS_BREATH_CONTROL_TWO_REG 0x09
#define IS31FL3731_ADDRESS_SOFTWARESHUTDOWN_REG 0x0A
#define IS31FL3731_ADDRESS_AGC_CONTROL_REG 0x0B
#define IS31FL3731_ADDRESS_AUDIO_ADC_RATE_REG 0x0C







class Pimoroni_11x7matrix {


    private:

    /// @brief The pixel buffer for the on/pff state.
    uint8_t _ledstate[11];

    /// @brief The pixel buffer for the blink on/off state.
    uint8_t _ledblinkstate[11];

    /// @brief The pixel buffer for the pwm values.
    uint8_t _ledpwmstate[11][7];

    /// @brief The i2c address of the chip.
    uint8_t _i2c_address;


    /// @brief Write a single byte of data to the chip.
    /// @param framenumber The number of the frame to write to. 0x00-0x07 Animation. 0x0B Control.
    /// @param address The address within the frame to write to.
    /// @param data The data byte to write to the chip.
    void _chipwritebyte( uint8_t framenumber , uint8_t address , uint8_t data );

    /// @brief Read a single byte of data from the chip.
    /// @param framenumber The number of the frame to read from. 0x00-0x07 Animation. 0x0B Control.
    /// @param address The address within the frame to read from.
    /// @return The data byte rturned from the chip as a uint8_t.
    uint8_t _chipreadbyte( uint8_t framenumber , uint8_t address );
    
    
    
    public:

    /// @brief Constructor for Pimoroni 11x7 Matrix Driver
    Pimoroni_11x7matrix();


    /// @brief Set the i2c address and perform any setup required.
    /// @param new_i2c_address The i2c address of the chip.
    void begin( uint8_t new_i2c_address );




    /// @brief Sets the software shutdown flag on the chip.
    /// @param state The state to set as a uint8_t. 0 = shutdown, 1 = normal operation.
    void softwareshutdownset( uint8_t state );

    /// @brief Gets the software shutdown flag from the chip.
    /// @return the flag as a uint8_t. 0 = shutdown, 1 = normal operation.
    uint8_t softwareshutdownget();


    /// @brief Sets the display mode on the chip.
    /// @param mode The mode number to set. 0b00 = picture mode, 0b01 = auto frame play, 0b1x = audio frame play.
    void displaymodeset( uint8_t mode );

    /// @brief Gets the display mode from the chip.
    /// @return The current display mode number as a uint8_t. 0b00 = picture mode, 0b01 = auto frame play, 0b1x = audio frame play.
    uint8_t displaymodeget();






    /// @brief Set the chips frame display pointer
    /// @param framenumber The number of the frame to display. 0-7.
    void framedisplaypointerset( uint8_t framenumber );


    /// @brief Fetches the current frame display pointer from the chip.
    /// @return The current frame display pointer as a uint8_t. 0-7.
    uint8_t framedisplaypointerget();








    /// @brief Write the pixel buffer to a frame on the chip.
    /// @param framenumber The number of the frame to write to. 0-7.
    void writepixelbuffertoframe( uint8_t framenumber );







    /// @brief Sets the pixel buffers for state, blink and pwm to all zero.
    void clearallpixelbuffers();


    /// @brief Sets the pixel buffer for state to all zero.
    void clearstatepixelbuffer();

    /// @brief Sets the pixel buffer for blink state to all zero.
    void clearblinkpixelbuffer();

    /// @brief Sets the pixel buffer for pwm value to all zero.
    void clearpwmpixelbuffer();




    /// @brief Sets a pixel to on or off in the pixel buffer.
    /// @param xpos The x position, with zero at the bottom left.
    /// @param ypos The y position, with the zero at the bottom left.
    /// @param state The state, 1 for on, 0 for off.
    void pixelset( uint8_t xpos , uint8_t ypos , uint8_t state );

    /// @brief Gets the value of a pixel from the pixel buffer.
    /// @param xpos The x position, with zero at the bottom left.
    /// @param ypos The y position, with zero at the bottom left.
    /// @return The state of the pixel as a uint8_t.  0 for off, 1 for on.
    uint8_t pixelget( uint8_t xpos , uint8_t ypos );





    /// @brief Set the blink flag for a pixel on or off in the pixel buffer.
    /// @param xpos The x position, with zero at the bottom left.
    /// @param ypos The y position, with zero at the bottom left.
    /// @param state The state of the blink flag as a uint8_t.  0 for off, 1 for on.
    void pixelblinkset( uint8_t xpos , uint8_t ypos , uint8_t state );

    /// @brief Get the state of a pixels blink flag from the pixel buffer.
    /// @param xpos The x position, with zero at the bottom left.
    /// @param ypos The y position, with zero at the bottom left.
    /// @return The state of the pixel as a uint8_t.  0 for off, 1 for on.
    uint8_t pixelblinkget( uint8_t xpos , uint8_t ypos );





    /// @brief Set the pwm value for a pixel in the pixel buffer
    /// @param xpos The x position of the pixel, with zero at the bottom left.
    /// @param ypos The y position of the pixel, with zero at the bottom left.
    /// @param state The pwm value to set, as a uint8_t.  0 is full off, 255 is full on.
    void pixelpwmset( uint8_t xpos , uint8_t ypos , uint8_t state );

    /// @brief Get the pwm value for a pixel from the pixel buffer.
    /// @param xpos The x position of the pixel, with zero at the bottom left.
    /// @param ypos The y position of the pixel, with zero at the bottom left.
    /// @return The pwm value of the pixel as a uint8_t.  0 is fully off, 255 is fully on.
    uint8_t pixelpwmget( uint8_t xpos , uint8_t ypos );












};






























#endif

