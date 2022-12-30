#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();


// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};


// include the library code:
#include <LiquidCrystal.h>

// dfrobot sheild pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


// i2c library
#include <Wire.h>
#define wire Wire



// include my IS31FL3731 library
#include <IS31FL3731.h>

#define IS31FL3731_I2C_ADDRESS 0x75

IS31FL3731 myledmatrix = IS31FL3731( IS31FL3731_I2C_ADDRESS );





// define the button pin

#define BUTTONPIN A0

// define the menu options
int8_t menucurrentchoice = 0;

uint8_t menumaxchoices = 6;

String menutext[6] = { "I2C Scan" ,
                       "Test 1" ,
                       "Test 2" ,
                       "" ,
                       "" ,
                       ""
                       };


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
  
  // bring up i2c as master
  wire.begin();

   if (! ledmatrix.begin()) {
    lcd.print(" not found");
    while (1);
  }
  lcd.print(" OK");

  while (1) {
  for (uint8_t incr = 0; incr < 24; incr++)
    for (uint8_t x = 0; x < 16; x++)
      for (uint8_t y = 0; y < 9; y++)
        ledmatrix.drawPixel(x, y, sweep[(x+y+incr)%24]);
  //delay(20);
  }
  
}



void menucommand_02() {

  // bring up the wire library as a master
  wire.begin();

  // move cursor to home
  lcd.clear();
  lcd.setCursor( 0 , 0 );



  // software shutdown mode
  /*
  lcd.print( "SS: " );
  lcd.print( myledmatrix.shutdownget() );
  lcd.print( ":" );
  myledmatrix.shutdownset( 1 );
  lcd.print( myledmatrix.shutdownget() );
  while (1);
  */

  // turn off software shutdown mode
  myledmatrix.shutdownset( 0 );
  //myledmatrix.write( 0x0B , 0x0A , 00 );
  delay(10);
  myledmatrix.shutdownset( 1 );
  //myledmatrix.write( 0x0B , 0x0A , 0x01 );





  // Picture Display Mode
  /*
  lcd.print( "PD: " );
  lcd.print( myledmatrix.modeget() );
  lcd.print( ":" );
  myledmatrix.modeset( 0 );
  lcd.print( myledmatrix.modeget() );
  while (1);
  */

  // Set to picture display mode
  myledmatrix.modeset( 0 );
  //myledmatrix.write( 0x0B , 0x00 , 0x00 );



  // Frame Select
  /*
  lcd.print( "FS: " );
  lcd.print( myledmatrix.frameget() );
  lcd.print( ":" );
  myledmatrix.frameset( 0 );
  lcd.print( myledmatrix.frameget() );
  while (1);
  */

  // Select frame 0
  myledmatrix.frameset( 0 );
  //myledmatrix.write( 0x0B , 0x01 , 0x00 );



  // apparently now I can set some led's on???


  // turn everything off in a sensible fashion
  for ( uint8_t i = 0 ; i < 0x12 ; i++ ) {
    myledmatrix.write( 0x00 , i , 0xFF );
  }

  // and to the blink controls
  for ( uint8_t i = 12 ; i < 0x24 ; i++ ) {
    myledmatrix.write( 0x00 , i , 0xFF );
  }

  // and for the pwm controls
  for ( uint8_t i = 24 ; i < 0xB4 ; i++ ) {
    myledmatrix.write( 0x00 , i , 0x04 );
  }
  
  // now hold here
  while(1);
  
  
  }



//00h 02h 04h 06h 08h 0Ah 0Ch 0Eh 10h









void menucommand_03() {};

void menucommand_04() {};

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