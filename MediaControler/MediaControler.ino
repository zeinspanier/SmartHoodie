#include <BleKeyboard.h>

BleKeyboard bleKeyboard; //Bluetooth keyboard

#define BTN1 39
#define BTN2 36
#define BTN3 34

// How many cycles to allow for double-press
#define BTN_CYCLES 20


// Button functions
enum expression {
  playPause,
  skipTrack,
  previousTrack,
  volumeUp,
  volumeDown
};

// Struct for button data
struct Button {
  int pin;
  int prev;
  const char* label;
  int is_clicked;
  long last_cycle;
  expression exp;
  expression d_exp;
};

Button buttons[3];
long cycles;
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  
  // Initialize data
  buttons[0].pin = BTN1;
  buttons[0].label = "First BTN";
  buttons[0].exp = previousTrack;
  buttons[0].d_exp = volumeDown;
  
  buttons[1].pin = BTN2;
  buttons[1].label = "Second BTN";
  buttons[1].exp = playPause;
  buttons[1].d_exp = playPause;
  
  buttons[2].pin = BTN3;
  buttons[2].label = "Third BTN";
  buttons[2].exp = skipTrack;
  buttons[2].d_exp = volumeUp;
  
  // Setup cycle counter
  cycles = 0;
  
  // Setup pins
  for(int i = 0; i < 3; i++){
    Button btn = buttons[i];
    pinMode(btn.pin, INPUT);
    int p = digitalRead(btn.pin);
    btn.prev = p;
    btn.last_cycle = -10-BTN_CYCLES;
    Serial.printf("Set up %s on pin %d\n", btn.label, btn.pin);
  }
  
}

bool conn = false;

void clearPrev(){
  for(int i = 0; i < 3; i++){
    Button btn = buttons[i];
    int p = digitalRead(btn.pin);
    btn.prev = p;
    btn.last_cycle = 0;
    btn.is_clicked = false;
  }
}

/**
   When device is connected search search for input, send input to connected device
*/
void loop() {
  if (bleKeyboard.isConnected()) {
    // Handle switching from off to on
    if (!conn){
      clearPrev();
      conn = true;
      Serial.printf("BT Connected\n");
    }
    // Detect button changes
    for(int i = 0; i < 3; i++){
      Button btn = buttons[i];
      int ch = detectChange(&buttons[i]);
      if (ch == 1){
        Serial.printf("Btn pressed: %s\n", btn.label);
        chooseExp(btn.exp);
      } else if (ch == 2){
        Serial.printf("Btn double-pressed: %s\n", btn.label);
        chooseExp(btn.d_exp);
      }
    }

    // Increment cycle_count
    cycles++;
    delay(100); // Prevent double input
  }
  else{
    conn = false;
    Serial.println("Not connected to BT");
    delay(5000);
  }
}

//// Detect clicks
int detectChange(Button *btn){
  int b = digitalRead(btn->pin);
  
  int ret = 0;
  // Check if button has changed
  if (b != btn->prev){
    Serial.printf("[%s]Prev: %d , cur: %d - ", btn->label, btn->prev, b);
    // Check threshold to avoid accidental presses
    if (cycles - (btn->last_cycle) > BTN_CYCLES){
      Serial.println("Within cycle");
      // Button press
      btn->last_cycle = cycles;
      btn->prev = b;
      return 1;   
    }
    else
      Serial.println("Outside cycle");
    // Update bookkeeping
    btn->prev = b;
    btn->last_cycle = cycles;
  }
  // No button press
  return ret;
}


//int detectChange(Button *btn){
//  int b = digitalRead(btn->pin);
//  if (cycles - btn_last_cycle < BTN_CYCLES && b != )
//  
//  
//  
//  
//  // Check if button has changed
//  if (b != btn->prev){
//    // Check threshold to avoid accidental presses
//    if (cycles - btn->last_cycle > BTN_CYCLES){
//      Serial.println("Within cycle");
//      // Button press
//      return 1;   
//    }
//    else
//      Serial.println("Outside cycle");
//    // Update bookkeeping
//    btn->prev = b;
//    btn->last_cycle = cycles;
//  }
//  // No button press
//  return 0;
//}



/**
   Choose the right expression to write
*/
void chooseExp(expression ex) {
  switch (ex) {
    case playPause:
      Serial.println("Pressed playPause");
      playPause_c();
      break;
    case skipTrack:
      Serial.println("Pressed skipTrack");
      nextTrack_c();
      break;
    case previousTrack:
      Serial.println("Pressed previousTrack");
      previousTrack_c();
      break;
    case volumeUp:
      Serial.println("Pressed volumeUp");
      volumeUp_c();
      break;
    case volumeDown:
      Serial.println("Pressed volumeDown");
      volumeUp_c();
      break;
    default:
      break;
  }
}


void previousTrack_c() {
  bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
}
void nextTrack_c() {
  bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
}
void playPause_c() {
  bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
}
void mute_c() {
  bleKeyboard.write(KEY_MEDIA_MUTE);
}
void volumeUp_c() {
  bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
}
void volumeDown_c() {
  bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
}
void stopMedia_c() {
  bleKeyboard.write(KEY_MEDIA_STOP);
}
void answerCall_c() {
  bleKeyboard.write(KEY_UP_ARROW);
}
void declineCall_c() {
  bleKeyboard.write(KEY_DOWN_ARROW);
}
