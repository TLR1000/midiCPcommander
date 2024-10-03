Basic Operation
1. Power Up and Welcome Screen
When powered, the OLED displays a "MIDI Setup" welcome message. Afterward, the display will show the current Channel, Program, and Bank.
2. Program Selection:
Press the Program Select Button to increment the program number from 0 to 127. When it reaches 127, it wraps around to 0 and the bank increments.
The OLED will display the current Program Number and Bank Number.
3. Channel Selection:
Press the Channel Select Button to increment the MIDI Channel from 1 to 16.
The OLED will show the selected channel.
4. Send Program Change:
Once the desired Program and Channel are set, press the Send Button. This sends a MIDI Program Change message to the connected MIDI device.
The OLED will display "MIDI Sent!" for 1 second and then revert back to the current settings display.
5. Reset:
Press the Reset Button to reset the Program to 0, the MIDI Channel to 1, and the Bank to 0.
The OLED will display "Reset Values" for 1 second before returning to the settings display.
Bank Select Operation
Bank Switching: When the Program Number rolls over from 127 to 0, the bank number is incremented, and a Bank Select message (MSB + LSB) is sent.
MSB (CC#0): Sent to select the general bank.
LSB (CC#32): Sent for fine bank selection (if supported by your MIDI device).
Note: If your device only supports MSB bank switching, the sketch is already configured to work in that mode. It sends both MSB and LSB by default, but you can modify the code to send only MSB if necessary.
