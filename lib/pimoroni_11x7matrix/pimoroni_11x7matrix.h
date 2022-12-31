

#ifndef PIMORONI_11X7MATRIX_HEADER_GUARD
#define PIMORONI_11X7MATRIX_HEADER_GUARD


// header for 11x7 matrix board by pimoroni

// pull in the arduino headers
#include <Arduino.h>



class Pimoroni_11x7matrix {


    private:

    uint8_t _ledstate[11];
    uint8_t _ledblinkstate[11];
    uint8_t _ledpwmstate[11][7];

    uint8_t _i2c_address;

    public:

    /// @brief Constructor for Pimoroni 11x7 Matrix Driver
    Pimoroni_11x7matrix();


    /// @brief Set the i2c address and perform any setup required.
    /// @param new_i2c_address The i2c address of the chip.
    void begin( uint8_t new_i2c_address );





    /// @brief Clears the buffer to all off.
    void clear();

    
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

