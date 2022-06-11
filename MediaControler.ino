#include <BleKeyboard.h>

BleKeyboard bleKeyboard; //Bluetooth keyboard

/**
   Turns bluetooth on. Begins search for a device to pair with
*/
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

/**
   When device is connected search search for input, send input to connected device
*/
void loop() {

  if (bleKeyboard.isConnected()) {
    // Psudo code
    // Listen for input from sensor
    // inperpret input
    // choose correct expression

    expression ex // Placeholder for sensor expression
    chooseExp(ex)

    delay(2500); // Prevent double input
  }
}

/**
   Choose the right expression to write
*/
void chooseExp(expression ex) {
  switch (ex) {
    case swipeRight:
      // serial.peek() check data, if phone call
      previousTrack();
      // if(phone call){ answer}
      break;
    case swipeLeft:
      // serial.peek() check data, if phone call
      nextTrack();
      // if(phone call){ decline}
      break;
    case doubleTap:
      playPause();
      break;
    case buttonOne:
      volumeUp();
      break;
    case buttonTwo:
      volumeDonw();
      break;

  }
}


void previousTrack() {
  bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
}
void nextTrack() {
  bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
}
void playPause() {
  bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
}
void mute() {
  bleKeyboard.write(KEY_MEDIA_MUTE);
}
void volumeUp() {
  bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
}
void volumeDown() {
  bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
}
void stopMedia() {
  bleKeyboard.write(KEY_MEDIA_STOP);
}
void answerCall() {
  bleKeyboard.write(KEY_UP_ARROW);
}
voic declineCall() {
  bleKeyboard.write(KEY_DOWN_ARROW);
}
