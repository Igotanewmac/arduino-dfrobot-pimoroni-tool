#include <Arduino.h>

// include the library code:
#include <LiquidCrystal.h>

// dfrobot sheild pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


// i2c library
#include <Wire.h>
#define wire Wire



// define the button pin

#define BUTTONPIN A0




int8_t menucurrentchoice = 0;

uint8_t menumaxchoices = 6;

String menutext[6] = { "I2C Scan" ,
                       "" ,
                       "" ,
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







// dump eeproms
void menucommand_01() {
  
  // bring up i2c as a master
  wire.begin();

  lcd.clear();
  lcd.setCursor( 0 , 0 );
  lcd.print( "Dumping EEPROMS" );
  
  // for each bank
  for ( int i = 0 ; i < 8 ; i++ ) {

    // read out 32k
    
    Serial.print( "Bank: " );
    Serial.print( i );
    Serial.println( " : " );

    //dump_eeprom_serial( 0x50 + i );

    Serial.println();

  }
  
}



void menucommand_02() {};

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
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print( analogRead( BUTTONPIN ) );

  delay( 750 );

}








































//