#include <MIDI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSans9pt7b.h>  // Include a custom font
#include <Encoder.h>

// Constants
#define PROGRAM_CHANGE_BUTTON_PIN 16  // Pin for sending MIDI program change command
#define MIDI_TX_PIN D7            // TX pin used for MIDI communication
#define ENCODER_PIN_A 14          // Pin A (CLK) for rotary encoder
#define ENCODER_PIN_B 12          // Pin B (DT) for rotary encoder
#define ENCODER_SWITCH_PIN 13     // Pin for rotary encoder switch (SW)
#define DEFAULT_PROGRAM_NUMBER 0  // Default program number
#define DEFAULT_MIDI_CHANNEL 1    // Default MIDI channel

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Variables
Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);  // Rotary encoder instance
int programNumber = DEFAULT_PROGRAM_NUMBER;
int midiChannel = DEFAULT_MIDI_CHANNEL;
long lastEncoderPosition = 0;
bool isChannelSelect = true;  // Toggle between channel and program selection

// MIDI Setup
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);  // Use hardware Serial for MIDI

// Handle encoder switch press to toggle between channel and program selection
void handleEncoderSwitch() {
  static unsigned long lastPressTime = 0;
  unsigned long currentTime = millis();
  if (digitalRead(ENCODER_SWITCH_PIN) == LOW && (currentTime - lastPressTime) > 200) {  // Debounce delay
    isChannelSelect = !isChannelSelect;                                                 // Toggle selection mode
    updateDisplay();                                                                    // Update display to show active selection mode
    lastPressTime = currentTime;
  }
}

// Adjust channel or program based on encoder movement
void adjustChannelOrProgram() {
  long newEncoderPosition = encoder.read();
  if (newEncoderPosition != lastEncoderPosition) {
    long change = (lastEncoderPosition - newEncoderPosition);
    if (isChannelSelect) {
      midiChannel += change;
      if (midiChannel < 1) midiChannel = 1;
      if (midiChannel > 16) midiChannel = 1;
    } else {
      programNumber += change;
      if (programNumber < 0) programNumber = 0;
      if (programNumber > 127) programNumber = 127;
    }
    lastEncoderPosition = newEncoderPosition;
    

    updateDisplay();
  }
}

void setup() {
  pinMode(PROGRAM_CHANGE_BUTTON_PIN, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
  // Initialize OLED for 128x64 screen
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;)
      ;  // Loop forever if OLED fails to initialize
  }

  // Display welcome message
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);  // Set the custom font
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("MIDI Setup");
  display.display();
  delay(1000);

  updateDisplay();  // Initial display update for program and channel

  pinMode(ENCODER_SWITCH_PIN, INPUT_PULLUP);  // Set switch pin as input with pull-up resistor

  Serial.begin(31250);  // Initialize MIDI at 31250 baud using the TX pin
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  handleProgramChangeButton();
  handleEncoderSwitch();
  adjustChannelOrProgram();
}

// Handle button press to send MIDI program change command
void handleProgramChangeButton() {
  static bool buttonPressed = false;
  if (digitalRead(PROGRAM_CHANGE_BUTTON_PIN) == LOW && !buttonPressed) {
    buttonPressed = true;
    displayMessage("Sending MIDI...");
    MIDI.sendProgramChange(programNumber, midiChannel);
    delay(200);  // Debounce delay
    updateDisplay();  // Return to the normal display
  } else if (digitalRead(PROGRAM_CHANGE_BUTTON_PIN) == HIGH) {
    buttonPressed = false;
  }
}
// Function to display a temporary message on OLED
void displayMessage(const char* message) {
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.println(message);
  display.display();
}

// Function to update OLED with current program and channel
void updateDisplay() {
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);  // Set the custom font

  // Draw indicator separately at column 0
  if (isChannelSelect) {
                      //(x0, y0, x1, y1, x2, y2)
    display.fillTriangle(0, 10, 10, 14, 0, 19, WHITE);  // Triangle for channel select, higher position
  } else {
    display.fillTriangle(0, 40, 10, 44, 0, 49, WHITE);  // Triangle for program select, lower position
  }

  // Draw channel text starting from a fixed column
  display.setCursor(15, 20);
  display.print("Channel ");
  display.println(midiChannel);

  // Draw program text starting from a fixed column
  display.setCursor(15, 50);
  display.print("Program ");
  display.println(programNumber);

  display.display();
}
