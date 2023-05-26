#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include "printer.h"

//const int enabPin[] = {21, 22, 23, 24}; // {5, 6, 13, 19} for BCM
const int enabPin[] = {21,24} //{5,19}for BCM
const int inxPin[] = {29, 3, 4, 5}; // {21, 22, 23, 24} for BCM
const int rightAheadPin = inxPin[2], rightBackPin = inxPin[3];
const int leftAheadPin = inxPin[0], leftBackPin = inxPin[1];
void setup() 
{
    logger(LOG_INFO, "Reseting ENA ENB Pin");
    for (int i = 0; i < 2; ++i) 
	{
        pinMode(enabPin[i], OUTPUT);
        digitalWrite(enabPin[i], HIGH);
    }
    for (int i = 0; i < 2; ++i) 
	{
        pinMode(inxPin[i], OUTPUT);
        digitalWrite(inxPin[i], LOW);
    }
    logger(LOG_INFO, "Reset Completed");
}

void front() 
{
    setup();
    digitalWrite(rightAheadPin, HIGH);
    digitalWrite(leftAheadPin, HIGH);
    logger(LOG_INFO, "Mode Switched to \"front\"");
}

void leftFront() 
{
    setup();
    digitalWrite(rightAheadPin, HIGH);
    logger(LOG_INFO, "Mode Switched to \"left front\"");
}

void rightFront() 
{
    setup();
    digitalWrite(leftAheadPin, HIGH);
    logger(LOG_INFO, "Mode Switched to \"right front\"");
}

void rear() 
{
    setup();
    digitalWrite(rightBackPin, HIGH);
    digitalWrite(leftBackPin, HIGH);
    logger(LOG_INFO, "Mode Switched to \"rear\"");
}

void leftRear() 
{
    setup();
    digitalWrite(rightBackPin, HIGH);
    logger(LOG_INFO, "Mode Switched to \"left rear\"");
}

void rightRear()
 {
    setup();
    digitalWrite(leftBackPin, HIGH);
    logger(LOG_INFO, "Mode Switched to \"right rear\"");
}

int main(int argc, char* argv[]) 
{
    wiringPiSetup();
    if (strcmp(argv[1], "front") == 0) 
	{
        front();
    } else if (strcmp(argv[1], "leftFront") == 0) 
	{
        leftFront();
    } else if (strcmp(argv[1], "rightFront") == 0) 
	{
        rightFront();
    } else if (strcmp(argv[1], "rear") == 0) 
	{
        rear();
    } else if (strcmp(argv[1], "leftRear") == 0) 
	{
        leftRear();
    } else if (strcmp(argv[1], "rightRear") == 0) 
	{
        rightRear();
    } else if (strcmp(argv[1], "stop") == 0) 
	{
        setup();
    }
}
