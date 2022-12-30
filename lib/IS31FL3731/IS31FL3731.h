
#ifndef IS31FL3731_HEADER_GUARD
#define IS31FL3731_HEADER_GUARD



// IS31FL3731 library header

// include Arduino header
#include <Arduino.h>

// Wire library
#include <Wire.h>
#define wire Wire








// a whole bunch of definitions

// the animation page the refers to the control register
#define IS31FL3731_PAGE_CONTROL 0x0B

#define IS31FL3731_ADDRESS_CONFIG_REGISTER 0x00
#define IS31FL3731_ADDRESS_SOFTWARESHUTDOWN 0x0A







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

    /// @brief Write a byte to the chip
    /// @param page The page to write to, 0x0-7 animation, 0xB control.
    /// @param address The address within the page to write to.
    /// @param data The data to write
    void write( uint8_t page , uint8_t address , uint8_t data );

    /// @brief Read a byte from the chip
    /// @param page The page to read from.  0x0-7 animation, 0xB control.
    uint8_t read( uint8_t page , uint8_t address );

public:
    /// @brief Constructor for IS31FL3731 LED matrix driver.
    /// @param address I2C address of the chip.
    IS31FL3731( uint8_t address );

    /// @brief Sets the software shutdown state to 0 ( shutdown ) or 1 ( normal operation ). 
    /// @param state 0 or 1. 0 is shutdown, 1 is normal operation.
    void shutdownset( uint8_t state );

    /// @brief Retreives the current software shutdown state.
    uint8_t shutdownget();


    /// @brief Set the mode in the configuration register.
    /// @param mode 0b00 = picture mode, 0b01 = auto frame play, 0b1x = audio frame play.
    void modeset( uint8_t mode );
    
    /// @brief Gets the current mode from the chip.
    uint8_t modeget();

};








#endif
