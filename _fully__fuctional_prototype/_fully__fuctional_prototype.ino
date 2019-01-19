#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#define BUZZER 8 //buzzer pin 

#define REDPIN 4
#define GREENPIN 2
#define REDBUTTON 12
#define GREENBUTTON 13


void setup() {
  Serial.begin(9600); // Initiate a serial communication 
  
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(REDBUTTON, INPUT);
  pinMode(GREENBUTTON, INPUT);
  
  pinMode(BUZZER, OUTPUT); 
  noTone(BUZZER);
  resetleds();
} 

void loop() {
  resetleds();
  if (digitalRead(REDBUTTON) == HIGH) {
    passagemInvalida();
  }
  else if (digitalRead(GREENBUTTON) == HIGH){
    passagemValida();
  }
  else{
    resetleds();
  }

}

void testarleds(){
    analogWrite(GREENPIN, 255);
    delay(500);
    resetleds();
    analogWrite(REDPIN, 255);
    delay(500);
    resetleds();
  }

void resetleds(){
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
}


void passagemValida(){
    Serial.println("Authorized access");  

    analogWrite(GREENPIN, 255);
    analogWrite(REDPIN, 0);
    delay(500); 

    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
}

void passagemInvalida(){
    Serial.println(" Access denied"); 
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 255);
    
    tone(BUZZER, 30); 
    delay(800); 
    noTone(BUZZER);
    
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
}
