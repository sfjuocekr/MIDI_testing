#include <MIDI.h>
#include <Time.h>
#include <TimeAlarms.h>

#define LED 13

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup()
{
  pinMode(LED, OUTPUT);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);

  Alarm.timerRepeat(2, sendNoteOn);

  digitalWrite(LED, LOW);
}

void sendNoteOn()
{
  digitalWrite(LED, HIGH);
  
  MIDI.sendNoteOn(60, 127, 1);
  
  Alarm.timerOnce(1, sendNoteOff);
}

void sendNoteOff()
{
  digitalWrite(LED, LOW);
  
  MIDI.sendNoteOff(60, 0, 1);
}

void loop()
{
  MIDI.read();
  Alarm.delay(0);
}
