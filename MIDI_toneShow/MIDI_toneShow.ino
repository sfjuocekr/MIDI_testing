#include <MIDI.h>
#include <Time.h>
#include <TimeAlarms.h>

#define LED 13
#define PWM 6

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

void setup()
{
  pinMode(LED, OUTPUT);
  blinkLED(1);

  pinMode(PWM, OUTPUT);
  analogWrite(PWM, 0);
  setPwmFrequency(PWM, 8);
  
  MIDI.setHandleNoteOn(onNoteOn);
  MIDI.setHandleNoteOff(onNoteOff);

  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void onNoteOn(byte channel, byte note, byte velocity)
{
  analogWrite(PWM, note);
  blinkLED(channel);
}

void onNoteOff(byte channel, byte note, byte velocity)
{
  analogWrite(PWM, 0);
  blinkLED(channel);
}

void blinkLED(int blinks)
{
  for (int i = 0; i < blinks; i++)
  {
    digitalWrite(LED, HIGH);
    Alarm.delay(50);
    digitalWrite(LED, LOW);
    Alarm.delay(50);
  }
}

void setPwmFrequency(int pin, int divisor)
{
  byte mode;
  if (pin == 5 || pin == 6 || pin == 9 || pin == 10)
  {
    switch (divisor)
    {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }

    if (pin == 5 || pin == 6)
    {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    }
    else
    {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  }
  else if (pin == 3 || pin == 11)
  {
    switch (divisor)
    {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }

    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

void loop()
{
  MIDI.read();
  Alarm.delay(0);
}
