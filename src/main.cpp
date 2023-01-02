#define IS31FL3731_I2C_ADDRESS 0x75


#include <Arduino.h>

#include <Wire.h>



// include the library code:
#include <LiquidCrystal.h>

// dfrobot sheild pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


// i2c library
#include <Wire.h>
#define wire Wire



// include my IS31FL3731 library
//#include <IS31FL3731.h>

#include <pimoroni_11x7matrix.h>






// define the button pin

#define BUTTONPIN A0

// define the menu options
int8_t menucurrentchoice = 0;

uint8_t menumaxchoices = 6;

String menutext[6] = { "I2C Scan" ,
                       "Test 1" ,
                       "Test 2" ,
                       "Test 3" ,
                       "Test 4" ,
                       ""
                       };




// i2c scanner
void menucommand_00() {

  lcd.clear();

  // turn on i2c as a master
  wire.begin();

  for ( int i = 0 ; i < 127 ; i++ ) {

    // check for a connection
    wire.beginTransmission( i );

    if ( wire.endTransmission() == 0 ) {
      // device is present at this address!
      if ( i < 16 ) { lcd.print("0" ); }
      lcd.print( i , HEX );
    }
    
  }

  // done so hold here
  while (1);
  
}







// Test 1
void menucommand_01() {
  
  // bring up i2c as a master
  wire.begin();

  lcd.clear();
  lcd.setCursor( 0 , 0 );
  lcd.print( "Test 1" );
  
  
  
}



void menucommand_02() {

  // bring up the wire library as a master
  wire.begin();

  // move cursor to home
  lcd.clear();
  lcd.setCursor( 0 , 0 );

  Pimoroni_11x7matrix myledmatrix;

  myledmatrix.begin( IS31FL3731_I2C_ADDRESS );

  myledmatrix.softwareShutdownSet( 0 );
  delay( 10 );
  myledmatrix.softwareShutdownSet( 1 );

  myledmatrix.displayModeSet( 0b00 );

  myledmatrix.frameDisplayPointerSet( 0 );

  myledmatrix.pixelBufferClearAll();
  
  myledmatrix.pixelBufferWriteAllToFrame( 0 );

  uint8_t xpos = 11;
  uint8_t ypos = 7;

  while(1) {

    // turn off the old led.
    myledmatrix.pixelSet( xpos , ypos , 0 );
    myledmatrix.pixelpwmSet( xpos , ypos , 0 );

    // move to a new one.
    xpos++;

    if ( xpos == 11 ) {
      xpos = 0;
      ypos++;
    }

    if ( ypos == 7 ) {
      xpos = 0;
      ypos = 0;
    }

    // turn on the new pixel
    myledmatrix.pixelSet( xpos , ypos , 1 );
    myledmatrix.pixelpwmSet( xpos , ypos , 4 );

    myledmatrix.pixelBufferWriteAllToFrame( 0 );

    //delay( 10 );

  };

  
  
  }



//00h 02h 04h 06h 08h 0Ah 0Ch 0Eh 10h









void menucommand_03() {

    // bring up the wire library as a master
  wire.begin();

  // move cursor to home
  lcd.clear();
  lcd.setCursor( 0 , 0 );

  Pimoroni_11x7matrix myledmatrix;

  myledmatrix.begin( IS31FL3731_I2C_ADDRESS );


  myledmatrix.pixelBufferBlinkStateFill( 0x00 );
  myledmatrix.pixelBufferpwmStateFill( 4 );


  myledmatrix.pixelBufferStateFill( 0x01 );
  myledmatrix.pixelBufferWriteAllToFrame( 0 );
  
  myledmatrix.pixelBufferStateFill( 0x02 );
  myledmatrix.pixelBufferWriteAllToFrame( 1 );
  
  myledmatrix.pixelBufferStateFill( 0x03 );
  myledmatrix.pixelBufferWriteAllToFrame( 2 );
  
  myledmatrix.pixelBufferStateFill( 0x04 );
  myledmatrix.pixelBufferWriteAllToFrame( 3 );
  
  myledmatrix.pixelBufferStateFill( 0x05 );
  myledmatrix.pixelBufferWriteAllToFrame( 4 );
  
  myledmatrix.pixelBufferStateFill( 0x06 );
  myledmatrix.pixelBufferWriteAllToFrame( 5 );
  
  myledmatrix.pixelBufferStateFill( 0x07 );
  myledmatrix.pixelBufferWriteAllToFrame( 6 );
  
  myledmatrix.pixelBufferStateFill( 0x08 );
  myledmatrix.pixelBufferWriteAllToFrame( 7 );



  myledmatrix.blinkEnableSet( 0 );

  // myledmatrix.blinkPeriodTimeSet( 7 );


  myledmatrix.breathControlEnableSet( 1 );

  myledmatrix.breathControlFadeInTimeSet( 3 );

  myledmatrix.breathControlExtinguishTimeSet( 1 );

  myledmatrix.breathControlFadeOutTimeSet( 3 );

  
  myledmatrix.frameDisplayPointerSet( 1 );


  uint8_t framecounter = 0;

  while (1) {
  

  myledmatrix.frameDisplayPointerSet( framecounter );

  delay( 2500 );

  framecounter++;

  if ( framecounter == 8 ) { framecounter = 0; }

  }




};

void menucommand_04() {



    // bring up the wire library as a master
  wire.begin();

  // move cursor to home
  lcd.clear();
  lcd.setCursor( 0 , 0 );

  Pimoroni_11x7matrix myledmatrix;

  myledmatrix.begin( IS31FL3731_I2C_ADDRESS );


  // can I turn the software control off and still access the registers?
  // the data sheet says so?
  myledmatrix.softwareShutdownSet( 0 );

  myledmatrix.pixelBufferBlinkStateFill( 0x00 );
  myledmatrix.pixelBufferpwmStateFill( 4 );


  myledmatrix.pixelBufferStateFill( 0x01 );
  myledmatrix.pixelBufferWriteAllToFrame( 0 );
  
  myledmatrix.pixelBufferStateFill( 0x02 );
  myledmatrix.pixelBufferWriteAllToFrame( 1 );
  
  myledmatrix.pixelBufferStateFill( 0x03 );
  myledmatrix.pixelBufferWriteAllToFrame( 2 );
  
  myledmatrix.pixelBufferStateFill( 0x04 );
  myledmatrix.pixelBufferWriteAllToFrame( 3 );
  
  myledmatrix.pixelBufferStateFill( 0x05 );
  myledmatrix.pixelBufferWriteAllToFrame( 4 );
  
  myledmatrix.pixelBufferStateFill( 0x06 );
  myledmatrix.pixelBufferWriteAllToFrame( 5 );
  
  myledmatrix.pixelBufferStateFill( 0x07 );
  myledmatrix.pixelBufferWriteAllToFrame( 6 );
  
  myledmatrix.pixelBufferStateFill( 0x08 );
  myledmatrix.pixelBufferWriteAllToFrame( 7 );



  myledmatrix.blinkEnableSet( 0 );

  // myledmatrix.blinkPeriodTimeSet( 7 );


  myledmatrix.breathControlEnableSet( 1 );

  myledmatrix.breathControlFadeInTimeSet( 3 );

  myledmatrix.breathControlExtinguishTimeSet( 1 );

  myledmatrix.breathControlFadeOutTimeSet( 3 );

  
  

  // set up an animation on the chip.
  myledmatrix.frameDisplayPointerSet( 0 );


  // starting frame
  myledmatrix.autoplayFrameStartSet( 0 );

  // frames playing selection
  // 7 for 7 frames, to land on 8
  myledmatrix.autoplayNumberOfFramesPlayingSet( 0 );

  // number of loops
  myledmatrix.autoplayNumberOfLoopsSet( 0 );


  // frame display time
  myledmatrix.autoplayFrameDelayTimeSet( 0 );


  // switch to animating mode
  myledmatrix.displayModeSet( 0b01 );



  // now turn the chip on
  myledmatrix.softwareShutdownSet( 1 );

  // now wait.
  //while(1);

};

void menucommand_05() {};


























void domenuaction() {

  lcd.setCursor( 0 , 1 );
  lcd.print( "Executing" );
  delay( 750 );

  switch (menucurrentchoice)
  {
  case 0:
    menucommand_00();
    break;
  
  case 1:
    menucommand_01();
    break;

  case 2:
    menucommand_02();
    break;
  
  case 3:
    menucommand_03();
    break;
  
  case 4:
    menucommand_04();
    break;
  case 5:
    menucommand_05();
    break;
  
  default:
    break;
  }

  return;

}




void displaymenu() {

  lcd.clear();
  lcd.setCursor( 0 , 0 );

  lcd.print( menutext[ menucurrentchoice ] );

}




// button scores
// none   1023
// right  0
// up     131
// down   308
// left   481
// select 720



void checkbutton() {

  int buttonraw = analogRead( BUTTONPIN );

  if ( buttonraw > 1000 ) { /* no button is pressed */ return; }

  if ( buttonraw < 100 ) { /* right button is pressed */ }

  if ( ( buttonraw > 100 ) && ( buttonraw < 200 ) ) { /* up button is pressed */ menucurrentchoice++; }
  if ( ( buttonraw > 250 ) && ( buttonraw < 350 ) ) { /* down button is pressed */ menucurrentchoice--; }
  if ( ( buttonraw > 450 ) && ( buttonraw < 500 ) ) { /* left button is pressed */ }
  if ( ( buttonraw > 700 ) && ( buttonraw < 750 ) ) { /* select button is pressed */ domenuaction(); }
  


  if ( menucurrentchoice == menumaxchoices ) { menucurrentchoice = ( menumaxchoices - 1 ); }
  if ( menucurrentchoice < 0 ) { menucurrentchoice = 0; }

  displaymenu();

}












void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  // set the buttonpin to input
  pinMode( BUTTONPIN , INPUT );

  Serial.begin( 9600 );

  // show the menu screen
  displaymenu();

}






void loop() {

  checkbutton();

  //lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // lcd.print( analogRead( BUTTONPIN ) );

  delay( 500 );

}








































//