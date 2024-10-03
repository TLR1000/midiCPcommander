The sketch, as it is currently written, supports the following modes with regards to Bank Select:

1. MSB (Most Significant Byte) Bank Select Support:
The sketch sends Control Change (CC#0) messages, which are used to select the MSB for bank switching.
MSB-only devices are supported by the sketch. When the program number reaches 127 and rolls over to 0, a new Bank Select MSB message is sent, and the bank number is incremented.
2. LSB (Least Significant Byte) Bank Select Support (Optional):
The current sketch sends both MSB (CC#0) and LSB (CC#32) messages, allowing support for devices that require both for bank switching.
This dual-message support means the sketch can handle devices that use both MSB and LSB for selecting banks, giving access to a wide range of sounds beyond 128 programs.
3. Program Change:
The sketch works alongside Program Change messages to allow selecting programs within the current bank.
After switching banks using Bank Select, the program number is sent to select a specific sound/patch within that bank.
Summary of Modes:
MSB-only mode: If your device supports only MSB Bank Select (using CC#0), the sketch will work in this mode.
MSB + LSB mode: If your device requires both MSB and LSB (CC#32), the sketch currently sends both messages, making it compatible with this mode as well.
