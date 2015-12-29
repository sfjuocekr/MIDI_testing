#include <NewPing.h>
#include <Thread.h>
#include <ThreadController.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 450

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

ThreadController* derFuhrer = new ThreadController();
ThreadController* sensors = new ThreadController();
ThreadController* feedback = new ThreadController();

Thread* distanceThread = new Thread();
Thread* serialThread = new Thread();

int currentDistance = 0;

void setup()
{
  Serial.begin(9600);
  
  currentDistance = sonar.ping_median() / 2;
  
  distanceThread->setInterval(50);
  distanceThread->onRun(getPing);

  serialThread->setInterval(100);
  serialThread->onRun(writeSerial);

  sensors->add(distanceThread);
  feedback->add(serialThread);

  derFuhrer->add(sensors);
  derFuhrer->add(feedback);
}

void loop()
{
  derFuhrer->run();
}

void getPing()
{
  currentDistance = (currentDistance + sonar.ping_median()) / 3;
}

float C(float _temp)
{
  return 331.3f * sqrt(1 + (_temp / 273.15f));
}

void writeSerial()
{
    Serial.print(C(21.4f) * currentDistance / 10000);
    Serial.println(" cm");
    Serial.print(currentDistance);
    Serial.println(" uS");
    Serial.println();
}

