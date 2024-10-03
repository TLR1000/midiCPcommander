Basic Operation
1. Power Up and Welcome Screen
Wanneer ingeschakeld, toont de tft display een welkomstbericht "MIDI Setup". Daarna zal het display het huidige Kanaal, Programma en Bank weergeven.
2. Program Selection:
Druk op de Program knop om het programmummer te verhogen van 0 tot 127. Wanneer het 127 bereikt, springt het terug naar 0 en wordt de bank verhoogd. De tft display zal het huidige Programmummer en Banknummer tonen.
3. Channel Selection:
Druk op de Channel knop om het MIDI-kanaal te verhogen van 1 tot 16. De tft display zal het geselecteerde kanaal weergeven.
4. Send Program Change:
Once the desired Program and Channel are set, press the Send Button. This sends a MIDI Program Change message to the connected MIDI device.
The tft display will display "MIDI Sent!" for 1 second and then revert back to the current settings display.
Zodra het gewenste Programma en Kanaal zijn ingesteld, druk op de Send knop. Dit stuurt een MIDI Program Change-bericht naar het aangesloten MIDI-apparaat. De tft display zal "MIDI Sent !" tonen gedurende 1 seconde en keert daarna terug naar de huidige instellingenweergave.
6. Reset:
Druk op de Resetknop om het Programma terug te zetten naar 0, het MIDI-kanaal naar 1 en de Bank naar 0. De tft display zal "Waarden gereset" weergeven gedurende 1 seconde voordat hij terugkeert naar de instellingenweergave.

Bank Select Operation
Wanneer het Programmummer overloopt van 127 naar 0, wordt het banknummer verhoogd en wordt een Bank Select-bericht (MSB + LSB) verzonden.
MSB (CC#0): om de algemene bank te selecteren.
LSB (CC#32): voor fine bank selection (indien ondersteund door uw MIDI-apparaat).
Opmerking: Als het midi apparaat alleen MSB-bankwissel ondersteunt, is de sketch al geconfigureerd om in die modus te werken. Standaard verzendt hij zowel MSB als LSB.
