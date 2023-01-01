

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











    /// @brief Write the pixel buffer to a frame on the chip.
    /// @param framenumber The number of the frame to write to. 0-7.
    void pixelbufferwritealltoframe( uint8_t framenumber );



    void pixelbufferstatewritetoframe( uint8_t framenubmer );

    void pixelbufferblinkstatewritetoframe( uint8_t framenumber );

    void pixelbufferpwmstatewritetoframe( uint8_t framenumber );




    /// @brief Sets the pixel buffers for state, blink and pwm to all zero.
    void pixelbufferclearall();


    /// @brief Sets the pixel buffer for state to all zero.
    void pixelbufferstateclear();

    /// @brief Sets the pixel buffer for blink state to all zero.
    void pixelbufferblinkstateclear();

    /// @brief Sets the pixel buffer for pwm value to all zero.
    void pixelbufferpwmstateclear();



    /// @brief Set all pixels state to the given value.
    /// @param data 0 = off, 1 = on.
    void pixelbufferstatefill( uint8_t data );

    /// @brief Set all pixels blink state to the given value
    /// @param data 0 = off, 1 = on.
    void pixelbufferblinkstatefill( uint8_t data );

    /// @brief Set all pixels pwm value to the given value.
    /// @param data 0-255. 0 is fully off, 255 is fully on.
    void pixelbufferpwmstatefill( uint8_t data );









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









    // register config functions

    // 0x00 configuration register

    /// @brief Sets the display mode on the chip.
    /// @param mode The mode number to set. 0b00 = picture mode, 0b01 = auto frame play, 0b1x = audio frame play.
    void displaymodeset( uint8_t mode );

    /// @brief Gets the display mode from the chip.
    /// @return The current display mode number as a uint8_t. 0b00 = picture mode, 0b01 = auto frame play, 0b1x = audio frame play.
    uint8_t displaymodeget();

    /// @brief Sets the start frame for autoplay
    /// @param startframe The number of the frame to syart autoplay on. 0-7.
    void autoplayframestartset( uint8_t startframe );

    /// @brief Gets the start frame for autoplay
    /// @return The number of the frame to start autoplay on as a uint8_t. 0-7.
    uint8_t autoplayframestartget();





    // 0x01 Picture Display Register

    /// @brief Set the chips frame display pointer
    /// @param framenumber The number of the frame to display. 0-7.
    void framedisplaypointerset( uint8_t framenumber );


    /// @brief Fetches the current frame display pointer from the chip.
    /// @return The current frame display pointer as a uint8_t. 0-7.
    uint8_t framedisplaypointerget();




    // 0x02 Autoplay Control Register 1

    /// @brief Sets the number of loops to play in Auto frame Play mode.
    /// @param numberofloops The number of loops to play. 0 = infinite, 1-7 plays that many loops.
    void autoplaynumberofloopsset( uint8_t numberofloops );

    /// @brief Gets the number of loops to play in Auto Frame Play mode.
    /// @return The number of loops to play.  0 = infinite, 1-7 plays that many loops.
    uint8_t autoplaynumberofloopsget();


    /// @brief Sets the number of frames to play in Auto Frame Play mode.
    /// @param  numberofframes The number of frames to play. 0 = all frames, 1-7 = that many frames.
    void autoplaynumberofframesplayingset( uint8_t numberofframes );

    /// @brief Gets the number of frames to play in an Auto Frame Play mode.
    /// @return The number of frames to play as a uint8_t. 0 = all framed, 1-7 = that many frames.
    uint8_t autoplaynumberofframesplayingget();



    // 0x03 Autoplay Control Register 2

    /// @brief Sets the frame delay time for Auto Frame Play mode.
    /// @param framedelaytime The time each frame should be shown.
    void autoplayframedelaytimeset( uint8_t framedelaytime );

    /// @brief Gets the frame delay time for Auto Frame Play mode.
    /// @return The frame delay time as a uint8_t.
    uint8_t autoplayframedelaytimeget();




    // 0x05 Display Option Register

    /// @brief Sets the intensity control bit.
    /// @param intensitystate 0 = set the intensity of each frame independently.  1 = use frame 0 for all settings.
    void intensitycontrolset( uint8_t intensitystate );

    /// @brief Gets the intensity control bit.
    /// @return The intensity control bit, as a uint8_1. 0 = set the intensity of each frame independently.  1 = use frame 0 for all settings.
    uint8_t intensitycontrolget();

    /// @brief Enable blinking!
    /// @param blinkstate The blink state. 0 for disabled, 1 for enabled.
    void blinkenableset( uint8_t blinkstate );

    /// @brief Get the current blink state.
    /// @return The current blink enable state as a uint8_t. 0 for disabled, 1 for enabled.
    uint8_t blinkenableget();

    /// @brief Sets the blink period time.
    /// @param  blinkperiodtime The amount of time to spend on each blink. 0-7 = bpt * 0.27s
    void blinkperiodtimeset( uint8_t blinkperiodtime );

    /// @brief Gets the blink period time
    /// @return The blink period time multiplier, as a uint8_t.  0-7 = bpt * 0.27s
    uint8_t blinkperiodtimeget();



    // 0x06 Audio Synchronisation Register.

    /// @brief Set the Audio Synchronisaton state.
    /// @param state The desired state as a uint8_t. 0 = disable, 1 = enable.
    void audiosynchenableset( uint8_t state );

    /// @brief Get the Audio Synchronisation state.
    /// @return The desired state as a uint8_t.  0 = disabled, 1 = enabled.
    uint8_t audiosynchenableget();



    // 0x07 Frame Display State Register. ( read only )

    /// @brief Returns true when the Auto Frame Play process has finished.  Automatically cleared on read.
    /// @return 0 if not finished.  1 when finished.  Automatically cleared on read.
    uint8_t framedisplayinterruptget();

    /// @brief Gets the number of the frame currently displayed in Auto Frame Play mode.
    /// @return The frame number. 0-7.
    uint8_t currentframedisplayget();





    // 0x08 Breath Control Register 1

    /// @brief Sets the fade out time for breath control
    /// @param fadeouttime 0-7. interval 26ms.
    void breathcontrolfadeouttimeset( uint8_t fadetime );

    /// @brief Gets the fade out time for breath control.
    /// @return 0-7. interval 26ms.
    uint8_t breathcontrolfadeouttimeget();


    /// @brief Sets the fade in time for breath control.
    /// @param fadeintime 0-7. interval 26ms.
    void breathcontrolfadeintimeset( uint8_t fadetime );

    /// @brief Gets the fade in time for breath control.
    /// @return 0-7. interval 26ms.
    uint8_t breathcontrolfadeintimeget();


    // 0x09 Breath Control Register 2

    /// @brief Sets the enable flaf for the Breath Control system.
    /// @param state 0 = disable , 1 = enable.
    void breathcontrolenableset( uint8_t state );

    /// @brief Gets the enable flag for the Breath Control system.
    /// @return 0 = disable , 1 = enable.
    uint8_t breathcontrolenableget();


    /// @brief Sets the extinguish time for the Breath Control system.
    /// @param fadetime 0-7. interval 3.5ms.
    void breathcontrolextinguishtimeset( uint8_t fadetime );

    /// @brief Gets the extinguish time from the Breath Control system.
    /// @return 0-7. interval 3.5ms
    uint8_t breathcontrolextinguishtimeget();







    // 0x0A Shurdown Register.

    /// @brief Sets the software shutdown flag on the chip.
    /// @param state The state to set as a uint8_t. 0 = shutdown, 1 = normal operation.
    void softwareshutdownset( uint8_t state );

    /// @brief Gets the software shutdown flag from the chip.
    /// @return the flag as a uint8_t. 0 = shutdown, 1 = normal operation.
    uint8_t softwareshutdownget();



    // 0x0B AGC Control Register.

    /// @brief Set the AGC mode.
    /// @param state 0 = slow mode, 1 = fast mode.
    void audioagcmodeset( uint8_t state );

    /// @brief Get the AGC mode.
    /// @return 0 = slow mode, 1 = fast mode.
    uint8_t audioagcmodeget();

    /// @brief Set the enable flag for AGC.
    /// @param state 0 = disable, 1 = enable.
    void audioagcenableset( uint8_t state );

    /// @brief Get the enable flag for AGC.
    /// @return 0 = disable, 1 = enable.
    uint8_t audioagcenableget();

    /// @brief Sets the gain for the AGC
    /// @param gain 0-7, interval 3dB
    void audioagcgainset( uint8_t gain );

    /// @brief Gets the gain for AGC.
    /// @return 0-7, interval 3dB.
    uint8_t audioagcgainget();





    // 0x019 Audio ADC Rate Register

    /// @brief Sets the ADC sample rate.
    /// @param samplerate 0-255, interval 46us
    void audioadcsamplerateset( uint8_t samplerate );

    /// @brief Gets the ADC sample rate.
    /// @return 0-255, interval 46us
    uint8_t audioadcsamplerateget();








};






























#endif

