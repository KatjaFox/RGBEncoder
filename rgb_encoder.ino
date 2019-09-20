#include <stdio.h> // For printf, scanf
#include <string.h> // For strcpy

const int ledRedPin = 13; 
const int ledGreenPin = 5; 
const int ledBluePin = 6; 
char incomingBytes[12];      // a variable to read incoming serial data into

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
}

void splitString(char messageParts[][4],  char message[], char separator)
{
    int partIndex = 0;
    int start = 0;
    char part[4];

    for(int i = 0; i < strlen(message); i++)
    {        
        if(message[i] != separator)
        {
            part[start] = message[i];
            start++;
        }
        
        if(message[i] == separator)
        {
            strlcpy(messageParts[partIndex], part, sizeof(messageParts[partIndex]));
            strlcpy(part, "   ", sizeof(part));
            
            partIndex++;
            start = 0;
        }
        else if(i == (strlen(message) - 1))
        {
            strlcpy(messageParts[partIndex], part, sizeof(messageParts[partIndex]));
        }
    }
}

void loop() {
  if (Serial.available() > 0) {
    strlcpy(incomingBytes, Serial.readString().c_str(), sizeof(incomingBytes));
    Serial.println("read:"); 
    Serial.println(incomingBytes); 

    char separator = ',';

    char messageParts[4][4];

    splitString(messageParts, incomingBytes, separator);

    int r = atoi(messageParts[0]);
    int g = atoi(messageParts[1]);
    int b = atoi(messageParts[2]);
        
    Serial.println(r);    
    Serial.println(g);
    Serial.println(b);
    
    analogWrite(ledRedPin, r);
    analogWrite(ledGreenPin, g);
    analogWrite(ledBluePin, b);
  }
}
