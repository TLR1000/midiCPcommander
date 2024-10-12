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
#define DEFAULT_MIDI_CHANNEL 11   // Default MIDI channel

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Parameters
#define DISPLAY_OFFSET 1  // Offset for display to match device numbering (e.g., display 1-128 instead of 0-127)
#define TOTAL_BANKS 4     // Total number of banks available on the device

// Variables
Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);  // Rotary encoder instance
int programNumber = DEFAULT_PROGRAM_NUMBER;
int bankNumber = 0;  // Bank selection variable
int midiChannel = DEFAULT_MIDI_CHANNEL;
long lastEncoderPosition = 0;
bool isChannelSelect = true;  // Toggle between channel and program selection

// MIDI Setup
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);  // Use hardware Serial for MIDI

void setup() {
  pinMode(PROGRAM_CHANGE_BUTTON_PIN, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
  pinMode(ENCODER_SWITCH_PIN, INPUT_PULLUP);  // Set switch pin as input with pull-up resistor

  // Initialize OLED for 128x64 screen
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
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

  Serial.begin(31250);  // Initialize MIDI at 31250 baud using the TX pin
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  handleEncoderSwitch();
  adjustChannelOrProgram();
  handleProgramChangeButton();
}

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
      if (programNumber < 0) {
        programNumber = 127;
        bankNumber = (bankNumber == 0) ? TOTAL_BANKS - 1 : bankNumber - 1;
      } else if (programNumber > 127) {
        programNumber = 0;
        bankNumber = (bankNumber + 1) % TOTAL_BANKS;
      }
    }
    lastEncoderPosition = newEncoderPosition;
    updateDisplay();
  }
}

// Function to update OLED with current program and channel
void updateDisplay() {
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);  // Set the custom font

  // Draw indicator separately at column 0
  if (isChannelSelect) {
    display.fillTriangle(0, 10, 10, 14, 0, 19, WHITE);  // Triangle for channel select, higher position
  } else {
    display.fillTriangle(0, 28, 10, 32, 0, 37, WHITE);  // Triangle for program select, lower position
  }

  // Draw channel text starting from a fixed column
  display.setCursor(15, 20);
  display.print("Channel ");
  display.println(midiChannel);

  // Draw program text starting from a fixed column
  display.setCursor(15, 38);
  display.print("Program ");
  display.println(programNumber + DISPLAY_OFFSET);

  // Draw bank text starting from a fixed column
  display.setCursor(15, 58);
  display.print("Bank ");
  display.println(bankNumber + 1);

  display.display();
}

// Function to handle program change button press
void handleProgramChangeButton() {
  if (digitalRead(PROGRAM_CHANGE_BUTTON_PIN) == LOW) {
    displayMessage("Sending MIDI...");
    MIDI.sendControlChange(0, bankNumber, midiChannel);  // Send bank select message (Control Change)
    MIDI.sendProgramChange(programNumber, midiChannel);
    delay(200);  // Debounce delay
    updateDisplay();  // Return to the normal display
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
