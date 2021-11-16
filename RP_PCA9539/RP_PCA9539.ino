
#include "src/RP_PCA9539.h"

//device address
const uint8_t PCA9539addr = 0x74;

//object
PCA9539 U4;


void setup() {
  Serial.begin(115200);

  //initialize device and print state
  uint8_t a = U4.init(PCA9539addr);
  Serial.print("PCA-init-code: ");
  Serial.println(a);

  //set buffer for four pins as input, not sent to device yet...
  U4.pinModeBuf(0, INPUT);
  U4.pinModeBuf(1, INPUT);
  U4.pinModeBuf(2, INPUT);
  U4.pinModeBuf(3, INPUT);
  //send the buffer to device
  U4.pinModeUpdate();

  //set four pins as output, every change is sent immediately to device..
  U4.pinMode(8, OUTPUT);
  U4.pinMode(9, OUTPUT);
  U4.pinMode(10, OUTPUT);
  U4.pinMode(11, OUTPUT);
  
  //set pins in buffer high, not sent to device yet...
  U4.digitalWriteBuf(8, HIGH);
  U4.digitalWriteBuf(9, HIGH);
  U4.digitalWriteBuf(10, HIGH);
  U4.digitalWriteBuf(11, HIGH);
  //send the buffer to device
  U4.writeBufUpdate();
  
  delay(2000);

  //set pins in buffer low, not sent to device yet...
  U4.digitalWriteBuf(8, LOW);
  U4.digitalWriteBuf(9, LOW);
  U4.digitalWriteBuf(10, LOW);
  U4.digitalWriteBuf(11, LOW);
  //send the buffer to device
  U4.writeBufUpdate();
  delay(2000);

  //set pins immediately...
  U4.pinMode(8, OUTPUT);
  U4.digitalWrite(8, HIGH);
  U4.digitalWrite(10, HIGH);
  delay(2000);
  U4.digitalWrite(8, LOW);
  U4.digitalWrite(10, LOW);
 
}

void loop() {
  //read all pins from device to input buffer and print it...
  U4.readBufUpdate();
  Serial.print("Read PortA: ");
  Serial.println(U4.readPortA());

  //read input and set output immediately...
  uint8_t b = U4.digitalRead(0);
  U4.digitalWrite(10, b);

  delay(1000); 

}
