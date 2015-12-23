#include <MIDI.h>
#include <Time.h>
#include <TimeAlarms.h>

#define LED 13

// RX = 19, TX = 18
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDIA);

// RX = 17, TX = 16
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDIB);

// RX = 15, TX = 14
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDIC);

void setup()
{
  pinMode(LED, OUTPUT);
  
  Serial.begin(250000);
  
  MIDIA.begin(1);
  MIDIB.begin(2);
  
  MIDIC.begin(MIDI_CHANNEL_OMNI);

  MIDIA.setHandleNoteOn(HandleNoteOn);
  MIDIA.setHandleNoteOff(HandleNoteOff);
  MIDIA.setHandleClock(HandleClock);
  
  MIDIB.setHandleNoteOn(HandleNoteOn);
  MIDIB.setHandleNoteOff(HandleNoteOff);
  MIDIB.setHandleClock(HandleClock);
  
  Alarm.timerRepeat(10, sendNoteOn);
  
  Serial.println("setup()");
}

void sendNoteOn()
{
  Serial.println("ON");
  
  MIDIC.sendNoteOn(42, 127, 1);
  
  Alarm.timerOnce(2, sendNoteOff);
}

void sendNoteOff()
{
  Serial.println("OFF");
  
  MIDIC.sendNoteOff(42, 0, 1);
}

/*
  void HandleNoteOn (byte channel, byte note, byte velocity)
  void HandleNoteOff (byte channel, byte note, byte velocity)
  void HandleAfterTouchPoly (byte channel, byte note, byte pressure)
  void HandleControlChange (byte channel, byte number, byte value)
  void HandleProgramChange (byte channel, byte number)
  void HandleAfterTouchChannel (byte channel, byte pressure)
  void HandlePitchBend (byte channel, int bend)
  void HandleSystemExclusive (byte *array, byte size)
  void HandleTimeCodeQuarterFrame (byte data)
  void HandleSongPosition (unsigned int beats)
  void HandleSongSelect (byte songnumber)
  void HandleTuneRequest (void)
  void HandleClock (void)
  void HandleStart (void)
  void HandleContinue (void)
  void HandleStop (void)
  void HandleActiveSensing (void)
  void HandleSystemReset (void)
*/

void loop()
{
  MIDIA.read();
  MIDIB.read();
  //MIDIC.read();

  Alarm.delay(0);
}

void HandleNoteOn (byte channel, byte note, byte velocity)
{
  Serial.println("HandleNoteOn");
  
  Serial.println(channel);
  Serial.println(note);
  Serial.println(velocity);
}

void HandleNoteOff (byte channel, byte note, byte velocity)
{
  Serial.println("HandleNoteOff");
  
  Serial.println(channel);
  Serial.println(note);
  Serial.println(velocity);
}

void HandleClock ()
{
  Serial.println("HandleClock");
}
