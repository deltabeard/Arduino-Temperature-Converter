/*
  2014 Mahyar Koshkouei
  
  Temperature Converter
*/

#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Below are the usual pins for connecting to a Nokia 5110 LCD
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 7, 12, 10);
// My Nokia 5110 LCD requires different pins than the usual because it's a wierd one.

// Below are variable for use with a Funduino Joystick Shield V1.A, although most of the buttons aren't needed for this game.
byte up_button = 2;
byte down_button = 4;
byte left_button = 5;
byte right_button = 3;
byte start_button = 6;
byte select_button = 7;
byte analog_button = 8;
byte x_axis = A0;
byte y_axis = A1;
byte buttons[] = {up_button, down_button, left_button, right_button, start_button, select_button, analog_button};


float input = 25;  // Used to get input from user
float outputToFar = 0;  // Used to store calculation
float outputToCel = 0;

void setup() {
  //Initialise the Joystick shield
  for (int i; i < 7; i++)
  {
   pinMode(buttons[i], INPUT);
   digitalWrite(buttons[i], HIGH);
  }
  
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);
  delay(500);
  display.clearDisplay();   // clears the screen and buffer
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
}

void loop() {
  display.clearDisplay();
  display.println("Enter value:");
  display.println(input);
  display.display();
  if (digitalRead(up_button) == LOW) {
    input++;
  } else if (digitalRead(right_button) == LOW) {
    input = input + 0.01;
  } else if (digitalRead(down_button) == LOW) {
    input--;
  } else if (digitalRead(left_button) == LOW) {
    input = input - 0.01;
  } else if (digitalRead(start_button) == LOW) {
    convert();
  }
  delay(50);
}

void convert(){
  display.clearDisplay();
  outputToFar = (input * 1.8) + 32;
  outputToCel = (input - 32) / 1.8;
  display.print("Input: ");
  display.println(input);
  display.println("Farenheit:");
  display.println(outputToFar);
  display.println("Celsius:");
  display.println(outputToCel);
  display.display();
  while (digitalRead(start_button) == LOW) {
    // Do nothing
  }
}
