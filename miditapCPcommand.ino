#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <MIDI.h>

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// MIDI Setup
MIDI_CREATE_DEFAULT_INSTANCE();

// Button Pins (using GPIO numbers directly)
const int buttonProgramPin = 14;  // Program select button (GPIO 14 - D5)
const int buttonChannelPin = 13;  // Channel select button (GPIO 13 - D7)
const int buttonSendPin = 12;     // Send message button (GPIO 12 - D6)
const int buttonResetPin = 16;    // Send message button (GPIO 12 - D6)

// MIDI Variables
int midiChannel = 1;    // Default channel is 1 (range 1-16)
int programNumber = 0;  // Default program number is 0 (range 0-127)

// Button state variables
int lastProgramButtonState = HIGH;
int lastChannelButtonState = HIGH;
int lastSendButtonState = HIGH;
int lastResetButtonState = HIGH;

void setup() {
  // Initialize MIDI
  MIDI.begin(MIDI_CHANNEL_OFF);

  // Initialize buttons
  pinMode(buttonProgramPin, INPUT_PULLUP);
  pinMode(buttonChannelPin, INPUT_PULLUP);
  pinMode(buttonSendPin, INPUT_PULLUP);
  pinMode(buttonResetPin, INPUT);

  // Initialize OLED for 128x64 screen
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;)
      ;  // Loop forever if OLED fails to initialize
  }

  // Display welcome message
  display.clearDisplay();
  display.setTextSize(2);  // Large text size for visibility
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("MIDI Setup");
  display.display();
  delay(1000);

  updateDisplay();  // Initial display update for program and channel
}

void loop() {
  // Handle program selection button
  int currentProgramButtonState = digitalRead(buttonProgramPin);
  if (currentProgramButtonState == LOW && lastProgramButtonState == HIGH) {
    programNumber = (programNumber + 1) % 128;  // Increment program number, wrap around at 127
    updateDisplay();  // Update OLED with new program number
    delay(200);  // Debounce
  }
  lastProgramButtonState = currentProgramButtonState;

  // Handle channel selection button
  int currentChannelButtonState = digitalRead(buttonChannelPin);
  if (currentChannelButtonState == LOW && lastChannelButtonState == HIGH) {
    midiChannel = (midiChannel % 16) + 1;  // Increment channel, wrap around at 16
    updateDisplay();  // Update OLED with new channel
    delay(200);  // Debounce
  }
  lastChannelButtonState = currentChannelButtonState;

  // Handle send message button and display feedback message
  int currentSendButtonState = digitalRead(buttonSendPin);
  if (currentSendButtonState == LOW && lastSendButtonState == HIGH) {
    MIDI.sendProgramChange(programNumber, midiChannel);  // Send MIDI Program Change message

    // Show "MIDI Sent!" message on OLED
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.println("MIDI Sent!");
    display.display();

    delay(1000);  // Wait for 1 second before returning to the program/channel display

    updateDisplay();  // Return to displaying the program number and channel
  }
  lastSendButtonState = currentSendButtonState;

  // Handle reset message button and display feedback message
  int currentResetButtonState = digitalRead(buttonResetPin);
  if (currentResetButtonState == LOW && lastResetButtonState == HIGH) {
    // perform reset logic. 
    programNumber = 0;
    midiChannel = 1;

    // Show message on OLED
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.println("Reset!");
    display.display();

    delay(1000);  // Wait for 1 second before returning to the program/channel display

    updateDisplay();  // Return to displaying the program number and channel
  }
  lastResetButtonState = currentResetButtonState;

}

// Function to update OLED with current program and channel
void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(2);  // Set text size for clear display
  display.setCursor(0, 0);
  display.print("Program:");
  display.println(programNumber);
  display.setCursor(0, 32);
  display.print("Channel:");
  display.println(midiChannel);
  display.display();
}
