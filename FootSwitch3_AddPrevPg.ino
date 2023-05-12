#include <BleKeyboard.h>

// need to set in BandHelper Remote Control Settings
// RIGHT_ARROW next song
// LEFT_ARROW prev song 
// DOWN_ARROW scroll down 


// shorter 15 character name seems to work better w. iPad
BleKeyboard bleKeyboard("ESP32-Chris", "Me", 100);

#define BUTTON_PIN 4
int timer = 0;
bool stepOne = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  static int debug = 0, counter = 0;
  char button = digitalRead(BUTTON_PIN) == LOW;

 if (!button && stepOne){
  timer ++;
//  Serial.println(timer);
//  delay(50);
 }

    if (bleKeyboard.isConnected() && button){
       counter++;
      // Serial.println(counter);

    if (counter > 15){
        delay (20);
        bleKeyboard.write(KEY_DOWN_ARROW);
        timer = 0;
      }
 
  }
if (!button && counter > 1 && counter < 15){
 // Serial.println(counter);
    delay(50);
  if (stepOne && timer < 11 && timer > 0){
      bleKeyboard.write(KEY_LEFT_ARROW);
      delay(50);
      timer = 0;
      counter = 0;
      stepOne = false;
   //   Serial.println("prev song");
   //    delay(50);
    }
    else {
      stepOne = true;
   //   Serial.println("stepOne");
   //    delay(50);
      counter = 0;
     }
}
   if (stepOne && !button && timer > 10) {
        bleKeyboard.write(KEY_RIGHT_ARROW);
      delay(50);
      timer = 0;
      counter = 0;
    //  Serial.println("Next song");
   //    delay(50);
       stepOne = false;
   }

   //   *****not done........//
  bleKeyboard.releaseAll();
//  counter = 0;
  // bleKeyboard.releaseAll();

if (!button && counter > 14){
//  Serial.println(counter);
//  delay (50);
  bleKeyboard.releaseAll();
  counter = 0; 
}

//  if(++debug % 20 == 0) Serial.println("sec");
  delay(50);
}
