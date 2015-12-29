#include <Thread.h>
#include <ThreadController.h>

ThreadController derFuhrer = ThreadController();

Thread* gateThread = new Thread();
Thread* analogSweepThread = new Thread();

void setup()
{
  Serial.begin(9600);

  pinMode(02, OUTPUT);
  pinMode(03, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(02, HIGH);
  
  gateThread->setInterval(100);
  gateThread->onRun(gateOn);
    derFuhrer.add(gateThread);
  
  analogSweepThread->setInterval(2);
  analogSweepThread->onRun(analogSweep);
    derFuhrer.add(analogSweepThread);
}

void gateOn()
{
  digitalWrite(02, HIGH);
  digitalWrite(13, HIGH);

  gateThread->onRun(gateOff);
}

void gateOff()
{
  digitalWrite(02, LOW);
  digitalWrite(13, LOW);

  gateThread->onRun(gateOn);
}

int analogValue = 0;
int directionValue = 1;

void analogSweep()
{
  analogWrite(03, analogValue);

  analogValue += directionValue;

  if (analogValue == 256) directionValue = -1;
  if (analogValue == 0) directionValue = 1;
}

void loop()
{
  derFuhrer.run();
}
