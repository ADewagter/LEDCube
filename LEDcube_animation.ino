/*
  Shift Register Example
  Turning on the outputs of a 74HC595 using an array

 Hardware:
 * 74HC595 shift register
 * LEDs attached to each of the outputs of the shift register

 */
//Pin connected to ST_CP of level data
int latchPin = 8;
//Pin connected to SH_CP of level data
int clockPin = 12;
////Pin connected to DS of level data
int dataPin = 11;


//Pin connected to ST_CP of level selector
int latchPin_l = 2;
//Pin connected to SH_CP of level selector
int clockPin_l = 4;
////Pin connected to DS of level selector
int dataPin_l = 3;



//int delay_update = 700; //used to showcase the multiplexing
int frame = 0; // keeps track of the frame the animation is at
int numberofframes = 26; //the number of frames in the animation
int frametime = 200; //the time in milliseconds per frame of the animation

//holders for infromation you're going to pass to shifting function
byte data;
byte dataArray[26][4]; //[frames][levels]
byte levelArray[4];


void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(latchPin_l, OUTPUT);
  Serial.begin(9600);

  //Binary notation as comment

  //first frame of the image
  dataArray[0][0] = 0x01; 
  dataArray[0][1] = 0x00;
  dataArray[0][2] = 0x00; 
  dataArray[0][3] = 0x00; 

  dataArray[1][0] = 0x00; 
  dataArray[1][1] = 0x01; 
  dataArray[1][2] = 0x00; 
  dataArray[1][3] = 0x00; 
  
  dataArray[2][0] = 0x00; 
  dataArray[2][1] = 0x00; 
  dataArray[2][2] = 0x01; 
  dataArray[2][3] = 0x00; 

  dataArray[3][0] = 0x00; 
  dataArray[3][1] = 0x00; 
  dataArray[3][2] = 0x00; 
  dataArray[3][3] = 0x01; 

  dataArray[4][0] = 0x00; 
  dataArray[4][1] = 0x00; 
  dataArray[4][2] = 0x00; 
  dataArray[4][3] = 0x04; 

  dataArray[5][0] = 0x00; 
  dataArray[5][1] = 0x00; 
  dataArray[5][2] = 0x00; 
  dataArray[5][3] = 0x10; 

  dataArray[6][0] = 0x00; 
  dataArray[6][1] = 0x00; 
  dataArray[6][2] = 0x00; 
  dataArray[6][3] = 0x40; 

  dataArray[7][0] = 0x00; 
  dataArray[7][1] = 0x00; 
  dataArray[7][2] = 0x40; 
  dataArray[7][3] = 0x00; 

  dataArray[8][0] = 0x00; 
  dataArray[8][1] = 0x40; 
  dataArray[8][2] = 0x00; 
  dataArray[8][3] = 0x00; 

  dataArray[9][0] = 0x40; 
  dataArray[9][1] = 0x00; 
  dataArray[9][2] = 0x00; 
  dataArray[9][3] = 0x00; 

  dataArray[10][0] = 0x10; 
  dataArray[10][1] = 0x00; 
  dataArray[10][2] = 0x00; 
  dataArray[10][3] = 0x00; 

  dataArray[11][0] = 0x04; 
  dataArray[11][1] = 0x00; 
  dataArray[11][2] = 0x00; 
  dataArray[11][3] = 0x00; 

  dataArray[12][0] = 0x01; 
  dataArray[12][1] = 0x00; 
  dataArray[12][2] = 0x00; 
  dataArray[12][3] = 0x00; 

// part 2 of animation

  dataArray[13][0] = 0x02; 
  dataArray[13][1] = 0x00;
  dataArray[13][2] = 0x00; 
  dataArray[13][3] = 0x00; 

  dataArray[14][0] = 0x00; 
  dataArray[14][1] = 0x02; 
  dataArray[14][2] = 0x00; 
  dataArray[14][3] = 0x00; 
  
  dataArray[15][0] = 0x00; 
  dataArray[15][1] = 0x00; 
  dataArray[15][2] = 0x02; 
  dataArray[15][3] = 0x00; 

  dataArray[16][0] = 0x00; 
  dataArray[16][1] = 0x00; 
  dataArray[16][2] = 0x00; 
  dataArray[16][3] = 0x02; 

  dataArray[17][0] = 0x00; 
  dataArray[17][1] = 0x00; 
  dataArray[17][2] = 0x00; 
  dataArray[17][3] = 0x08; 

  dataArray[18][0] = 0x00; 
  dataArray[18][1] = 0x00; 
  dataArray[18][2] = 0x00; 
  dataArray[18][3] = 0x20; 

  dataArray[19][0] = 0x00; 
  dataArray[19][1] = 0x00; 
  dataArray[19][2] = 0x00; 
  dataArray[19][3] = 0x80; 

  dataArray[20][0] = 0x00; 
  dataArray[20][1] = 0x00; 
  dataArray[20][2] = 0x80; 
  dataArray[20][3] = 0x00; 

  dataArray[21][0] = 0x00; 
  dataArray[21][1] = 0x80; 
  dataArray[21][2] = 0x00; 
  dataArray[21][3] = 0x00; 

  dataArray[22][0] = 0x80; 
  dataArray[22][1] = 0x00; 
  dataArray[22][2] = 0x00; 
  dataArray[22][3] = 0x00; 

  dataArray[23][0] = 0x20; 
  dataArray[23][1] = 0x00; 
  dataArray[23][2] = 0x00; 
  dataArray[23][3] = 0x00; 

  dataArray[24][0] = 0x08; 
  dataArray[24][1] = 0x00; 
  dataArray[24][2] = 0x00; 
  dataArray[24][3] = 0x00; 

  dataArray[25][0] = 0x02; 
  dataArray[25][1] = 0x00; 
  dataArray[25][2] = 0x00; 
  dataArray[25][3] = 0x00;
  
  levelArray[0] = 0x11;
  levelArray[1] = 0x22;
  levelArray[2] = 0x44;
  levelArray[3] = 0x88;
  /*
  dataArray[1][0] = 0xF0; //0b11110000
  dataArray[1][1] = 0xE0; //0b11100000
  dataArray[1][2] = 0xC0; //0b11000000
  dataArray[1][3] = 0x80; //0b10000000

  
  dataArray[0][8] = 0x00; //0b00000000
  dataArray[0][9] = 0xE0; //0b11100000
  
  dataArray[1][0] = 0xFF; //0b11111111
  dataArray[1][1] = 0xFE; //0b11111110
  dataArray[1][2] = 0xFC; //0b11111100
  dataArray[1][3] = 0xF8; //0b11111000
  dataArray[1][4] = 0xF0; //0b11110000
  dataArray[1][5] = 0xE0; //0b11100000
  dataArray[1][6] = 0xC0; //0b11000000
  dataArray[1][7] = 0x80; //0b10000000
  dataArray[1][8] = 0x00; //0b00000000
  dataArray[1][9] = 0xE0; //0b11100000
  */

  //function that blinks all the LEDs
  //gets passed the number of blinks and the pause time
  //blinkAll_2Bytes(2,500);
}

void loop() {
  // each loop performs a single frame
  frame = frame % numberofframes; //loops the animation
  
  unsigned long time = millis(); //Gets the time at the beginning of the frame

  while(millis()-time < frametime){
    for (int j = 0; j < 4; j++) {
      data = dataArray[frame][j];
      digitalWrite(latchPin, 1);
      shiftOut(dataPin, clockPin, data);
      digitalWrite(latchPin, 0);

      digitalWrite(latchPin_l, 1);
      shiftOut(dataPin_l, clockPin_l, levelArray[j]);
      digitalWrite(latchPin_l, 0);
      delay(2);
      // delay(delay_update); // Used to showcase multiplexing
      }
  }
  frame ++; //Go to next frame
  
  }
  
  

  
 /* for (int j = 0; j < sizeof dataArray ; j++) {
    //load the light sequence you want from array
    data = dataArray[j];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, data);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);

    digitalWrite(latchPin_l, 0);

    shiftOut(dataPin_l, clockPin_l, data);

    digitalWrite(latchPin_l, 1);
    
    
    
    delay(200);

    */
  




// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else { 
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}


//blinks the whole register based on the number of times you want to
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}
