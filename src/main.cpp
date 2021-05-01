#include <Arduino.h>

/*
  4-bit LCD pin:
  (Just write, so pin RW grounded)
*/
const int _data_pins[4]   =   { 0,   4,   5,   16 };  //  { db4, db5, db6, db7 }
const int rs              =   12;                     //  Low: to send command | High: to send chars    
const int en              =   14;                     //  Pulse to send bits

void pulseEn(void);
void write4bits(uint8_t value);
void sendBitsOf(uint8_t value, uint8_t _mode);


void setup() {
  Serial.begin(9600); // Initializing Serial to monitorate some codes.


  delay(5);
  Serial.println ("...");
  Serial.println (0x4C, BIN);
  Serial.println (((0x4C)>>0) & 0x01);
  Serial.println (((0x4C)>>1) & 0x01);
  Serial.println (((0x4C)>>2) & 0x01);
  Serial.println (((0x4C)>>3) & 0x01);

  Serial.println (((0x4C)>>4) & 0x01);
  Serial.println (((0x4C)>>5) & 0x01);
  Serial.println (((0x4C)>>6) & 0x01);
  Serial.println (((0x4C)>>7) & 0x01);

  
  // Initializing Pins Mode
  pinMode(_data_pins[0], OUTPUT);
  pinMode(_data_pins[1], OUTPUT);
  pinMode(_data_pins[2], OUTPUT);
  pinMode(_data_pins[3], OUTPUT);

  pinMode(rs, OUTPUT);
  pinMode(en, OUTPUT);
  
  digitalWrite(rs,    LOW); // Command mode
  delayMicroseconds(100);   // Wait 40ms to energy the 16x2 (datasheet)
  for (int i = 0; i < 3; i++) {
    writeBits(0x03);          // Setting 4-bits mode, three times (datasheet).
    delayMicroseconds(4500);  // Waiting 4500 µs → 4.5 ms
  }

  delayMicroseconds(150);
  
  // Set to 4-bit interface
  writeBits(0x02);

  // Clear Display
  digitalWrite(rs,    LOW); // Function mode (low)
  digitalWrite(_data_pins[0], 0);
  digitalWrite(_data_pins[1], 0);
  digitalWrite(_data_pins[2], 0);
  digitalWrite(_data_pins[3], 0);
  pulseEn();
   
  digitalWrite(rs,    LOW); // Function mode (low)
  digitalWrite(_data_pins[0], 1);
  digitalWrite(_data_pins[1], 0);
  digitalWrite(_data_pins[2], 0);
  digitalWrite(_data_pins[3], 0);
  pulseEn();

  delay(1000); // 5 seconds to clear
   
  // Writing "L" on display with LOW/HIGH

  digitalWrite(rs,    HIGH); // Write mode
  digitalWrite(_data_pins[0], LOW);
  digitalWrite(_data_pins[1], LOW);
  digitalWrite(_data_pins[2], HIGH);
  digitalWrite(_data_pins[3], LOW);
  pulseEn();
   
  digitalWrite(rs,    HIGH); // Write mode
  digitalWrite(_data_pins[0], LOW);
  digitalWrite(_data_pins[1], LOW);
  digitalWrite(_data_pins[2], HIGH);
  digitalWrite(_data_pins[3], HIGH);
  pulseEn();

  // Writing on display "H" with Hex

  digitalWrite(rs,    HIGH); // Write mode
  digitalWrite(_data_pins[0], (((0x48)>>4) & 0x01));
  digitalWrite(_data_pins[1], (((0x48)>>5) & 0x01));
  digitalWrite(_data_pins[2], (((0x48)>>6) & 0x01));
  digitalWrite(_data_pins[3], (((0x48)>>7) & 0x01));
  pulseEn();
   
  digitalWrite(rs,    HIGH); // Write mode
  digitalWrite(_data_pins[0], (((0x48)>>0) & 0x01));
  digitalWrite(_data_pins[1], (((0x48)>>1) & 0x01));
  digitalWrite(_data_pins[2], (((0x48)>>2) & 0x01));
  digitalWrite(_data_pins[3], (((0x48)>>3) & 0x01));
  pulseEn();

}


void loop() {

  
}

void pulseEn() {
  digitalWrite(en,    LOW);
  delayMicroseconds(5);
  digitalWrite(en,   HIGH);
  delayMicroseconds(5);
  digitalWrite(en,    LOW);
  delayMicroseconds(100);
}

void writeBits(uint8_t value) {
  // Wrinting the instructions with 4 bits:
  for (int i = 0; i < 4; i++) {
    digitalWrite(_data_pins[i], (value>>i) & 0x01); // Get value and turn an binary value
  }
  
  pulseEn();
}