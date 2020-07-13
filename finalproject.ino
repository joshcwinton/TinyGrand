#include <Tone.h>             // Tone library for playing notes
#include <SPI.h>              // Serial Peripheral Interface - needed for I2C
#include <Wire.h>             // I2C - Used to communicate with OLED display
#include <Adafruit_GFX.h>     // Used to send graphics to display
#include <Adafruit_SSD1306.h> // Display-specific library
#include <Adafruit_TPA2016.h> // Amp-specific library


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin, shared with Arduino reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Declaration for TPA2016 amp
Adafruit_TPA2016 audioamp = Adafruit_TPA2016();

// Initialize a tone
Tone tone1;

// Set input pins (digital 0-13)
const int buttonPinC =  0;
const int buttonPinCS = 1;
const int buttonPinD =  2;
const int buttonPinDS = 3;
const int buttonPinE =  4;
const int buttonPinF =  5;
const int buttonPinFS = 6;
const int buttonPinG =  7;
const int buttonPinGS = 8;
const int buttonPinA =  9;
const int buttonPinAS = 10;
const int buttonPinB =  11;
const int recordPin =   12;

// Initialize button states to be unpressed
int buttonStateC =      0;
int buttonStateCS =     0;
int buttonStateD =      0;
int buttonStateDS =     0;
int buttonStateE =      0;
int buttonStateF =      0;
int buttonStateFS =     0;
int buttonStateG =      0;
int buttonStateGS =     0;
int buttonStateA =      0;
int buttonStateAS =     0;
int buttonStateB =      0;
int recordState =       0;

// 0 is live, 1 is record, 2 is play
int MODE = 0;

// Keep track of current note while recording
int currentRecordNote = 0;

// Maximum number of notes stored for playback
const int NUM_NOTES = 100;

// Array for  storing recorded melodies
int melody[NUM_NOTES];

// Routine for clearing melody storage, empty notes are encoded as "-1"
void clearMelody(){
  for(int i = 0; i < NUM_NOTES; i++){
    melody[i] = -1;
  }
}

void setup() {
  Serial.begin(9600);

  // Use analog pin 0 for output to amp
  tone1.begin(A0);

  // Set display to horizontal rotation
  display.setRotation(2);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.setTextSize(2);      // Font size
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner

  // Set all buttons to pullup input mode
  pinMode(buttonPinC, INPUT_PULLUP);
  pinMode(buttonPinCS, INPUT_PULLUP);
  pinMode(buttonPinD, INPUT_PULLUP);
  pinMode(buttonPinDS, INPUT_PULLUP);
  pinMode(buttonPinE, INPUT_PULLUP);
  pinMode(buttonPinF, INPUT_PULLUP);
  pinMode(buttonPinFS, INPUT_PULLUP);
  pinMode(buttonPinG, INPUT_PULLUP);
  pinMode(buttonPinGS, INPUT_PULLUP);
  pinMode(buttonPinA, INPUT_PULLUP);
  pinMode(buttonPinAS, INPUT_PULLUP);
  pinMode(buttonPinB , INPUT_PULLUP);
  pinMode(recordPin, INPUT_PULLUP);

  // Initialize melody array
  clearMelody();

  // Show initial display buffer contents on the screen
  display.clearDisplay();
  display.display();
  display.println(F("TinyGrand"));
  display.display();
  display.setTextSize(3.5);      // Font size
  delay(2000); // Pause for 2 seconds
}

// Routine for reading all buttons
void readPins(){
  buttonStateC  = digitalRead(buttonPinC);
  buttonStateCS = digitalRead(buttonPinCS);
  buttonStateD  = digitalRead(buttonPinD);
  buttonStateDS = digitalRead(buttonPinDS);
  buttonStateE  = digitalRead(buttonPinE);
  buttonStateF  = digitalRead(buttonPinF);
  buttonStateFS = digitalRead(buttonPinFS);
  buttonStateG  = digitalRead(buttonPinG);
  buttonStateGS = digitalRead(buttonPinGS);
  buttonStateA  = digitalRead(buttonPinA);
  buttonStateAS = digitalRead(buttonPinAS);
  buttonStateB  = digitalRead(buttonPinB);
  recordState   = digitalRead(recordPin);
}

// Routine that controls LIVE mode
void live(){
  //  Indicate mode change on display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("LIVE"));
  display.display();

  delay(500);

  display.clearDisplay();
  display.display();

  // Loop runs while device is in LIVE mode
  while(true){
    // switch to RECORD if button has been pushed
    if(MODE == 1){
      record();
    }

    display.clearDisplay();
    display.setCursor(0, 0);
    readPins();

    /* Check if the pushbutton is pressed. If it is, the buttonState is LOW:
       play note and display it */
    if (buttonStateC == LOW) {
      tone1.play(NOTE_C3);
      display.println(F("C"));
      display.display();
    } else if(buttonStateCS == LOW){
      tone1.play(NOTE_CS3);
      display.println(F("C#"));
      display.display();
    } else if(buttonStateD == LOW){
      tone1.play(NOTE_D3);
      display.println(F("D"));
      display.display();
    } else if(buttonStateDS == LOW){
      tone1.play(NOTE_DS3);
      display.println(F("D#"));
      display.display();
    } else if(buttonStateE == LOW){
      tone1.play(NOTE_E3);
      display.println(F("E"));
      display.display();
    } else if(buttonStateF == LOW){
      tone1.play(NOTE_F3);
      display.println(F("F"));
      display.display();
    } else if(buttonStateFS == LOW){
      tone1.play(NOTE_FS3);
      display.println(F("F#"));
      display.display();
    } else if(buttonStateG == LOW){
      tone1.play(NOTE_G3);
      display.println(F("G"));
      display.display();
    } else if(buttonStateGS == LOW){
      tone1.play(NOTE_GS3);
      display.println(F("G#"));
      display.display();
    } else if(buttonStateA == LOW){
      tone1.play(NOTE_A3);
      display.println(F("A"));
      display.display();
    } else if(buttonStateAS == LOW){
      tone1.play(NOTE_AS3);
      display.println(F("A#"));
      display.display();
    } else if(buttonStateB == LOW){
      tone1.play(NOTE_B3);
      display.println(F("B"));
      display.display();
    } else if(recordState == LOW){
      MODE = 1;
    } else {
      // turn LED off:
      tone1.stop();
      display.println(F("OFF"));
      display.display();
    }
  }
}

void record(){
  clearMelody();
  currentRecordNote = 0;

  // Indicate mode change on display
  display.clearDisplay();
  display.println(F("RECORD"));
  display.display();
  delay(500);

  display.clearDisplay();
  display.display();

  while(true){
    display.clearDisplay();
    display.setCursor(0, 0);
    readPins();

    /* Check if the pushbutton is pressed. If it is, the buttonState is LOW:
       play note and display it */
    if (buttonStateC == LOW) {
      tone1.play(NOTE_C3);
      display.println(F("C"));
      display.display();
      while(true){
        readPins();
        if(buttonStateC == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_C3;
      currentRecordNote++;
    } else if(buttonStateCS == LOW){
      tone1.play(NOTE_CS3);
      display.println(F("C#"));
      display.display();
      while(true){
        readPins();
        if(buttonStateCS == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_CS3;
      currentRecordNote++;
    } else if(buttonStateD == LOW){
      tone1.play(NOTE_D3);
      display.println(F("D"));
      display.display();
      while(true){
        readPins();
        if(buttonStateD == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_D3;
      currentRecordNote++;
    } else if(buttonStateDS == LOW){
      tone1.play(NOTE_DS3);
      display.println(F("D#"));
      display.display();
      while(true){
        readPins();
        if(buttonStateDS == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_DS3;
      currentRecordNote++;
    } else if(buttonStateE == LOW){
      tone1.play(NOTE_E3);
      display.println(F("E"));
      display.display();
      while(true){
        readPins();
        if(buttonStateE == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_E3;
      currentRecordNote++;
    } else if(buttonStateF == LOW){
      tone1.play(NOTE_F3);
      display.println(F("F"));
      display.display();
      while(true){
        readPins();
        if(buttonStateF == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_F3;
      currentRecordNote++;
    } else if(buttonStateFS == LOW){
      tone1.play(NOTE_FS3);
      display.println(F("F#"));
      display.display();
      while(true){
        readPins();
        if(buttonStateFS == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_FS3;
      currentRecordNote++;
    } else if(buttonStateG == LOW){
      tone1.play(NOTE_G3);
      display.println(F("G"));
      display.display();
      while(true){
        readPins();
        if(buttonStateG == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_G3;
      currentRecordNote++;
    } else if(buttonStateGS == LOW){
      tone1.play(NOTE_GS3);
      display.println(F("G#"));
      display.display();
      while(true){
        readPins();
        if(buttonStateGS == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_GS3;
      currentRecordNote++;
    } else if(buttonStateA == LOW){
      tone1.play(NOTE_A3);
      display.println(F("A"));
      display.display();
      while(true){
        readPins();
        if(buttonStateA == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_A3;
      currentRecordNote++;
    } else if(buttonStateAS == LOW){
      tone1.play(NOTE_AS3);
      display.println(F("A#"));
      display.display();
      while(true){
        readPins();
        if(buttonStateAS == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_AS3;
      currentRecordNote++;
    } else if(buttonStateB == LOW){
      tone1.play(NOTE_B3);
      display.println(F("B"));
      display.display();
      while(true){
        readPins();
        if(buttonStateB == HIGH){
          break;
        }
      }
      melody[currentRecordNote] = NOTE_B3;
      currentRecordNote++;
    } else if(recordState == LOW){
      play();
      MODE = 0;
      return;
    } else {
      // turn LED off:
      tone1.stop();
      display.println(F("OFF"));
      display.display();
    }
  }
}

void play(){
  display.clearDisplay();
  display.println(F("PLAY"));
  display.display();

  delay(500);

  if(melody[0] == -1){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("EMPTY"));
    display.display();
    delay(500);
    MODE = 0;
    return;
  }

  for (int thisNote = 0; thisNote < NUM_NOTES; thisNote++) {
    Serial.println(melody[thisNote]);
    if(melody[thisNote] == -1){
      display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("End"));
    display.display();
    delay(1000);
      MODE = 0;
      return;
    }

    tone1.play(melody[thisNote]);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int noteDuration = 1000 / 4; // All 1/4 notes
    int pauseBetweenNotes = noteDuration * 0.5;

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("PLAYING"));
//    display.println(melody[thisNote]);
    display.display();
    
    delay(noteDuration);

    display.clearDisplay();
    display.display();
    
    // stop the tone playing:
    tone1.stop();
    delay(pauseBetweenNotes);
  }
  MODE = 0;
  return;
}

void loop() {
  live();
}
