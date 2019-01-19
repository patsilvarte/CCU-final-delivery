#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

const int trigPin = 8;
const int echoPin = 7;
#define SS_PIN 10 
#define RST_PIN 9 
//#define LED_G 5 //define green LED pin 
//#define LED_R 4 //define red LED 
#define BUZZER 2 //buzzer pin 

#define REDPIN 3
#define GREENPIN 4

long duration;
int distance;
int safetyDistance;
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.  

void setup() {
  Serial.begin(9600); // Initiate a serial communication 
  Serial.println("Put your card to the reader..."); 
  Serial.println();
  
  SPI.begin(); // Initiate SPI bus 
  mfrc522.PCD_Init(); // Initiate MFRC522 


  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(BUZZER, OUTPUT); 
  noTone(BUZZER);
  Serial.println("Put your card to the reader..."); 
  Serial.println();
  resetleds();
} 

void loop() { // Look for new cards

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  safetyDistance = distance;
  
  //Serial.print("Distance: ");
  //Serial.println(distance);
  if (safetyDistance <= 35){
    delay(300);
    verificaCartao(); 
  }
  else{
    resetleds();
  }
  
}

void resetleds(){
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
}

void verificaCartao(){    
    //not sure about this
    if ( ! mfrc522.PICC_IsNewCardPresent()) { passagemInvalida(); return; } // Select one of the cards 
    if ( ! mfrc522.PICC_ReadCardSerial()) { Serial.println("No serial");return; } //Show UID on serial monitor 
    
    Serial.print("UID tag :"); 
    String content= ""; 
    byte letter; 
    for (byte i = 0; i < mfrc522.uid.size; i++) { 
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "); 
      Serial.print(mfrc522.uid.uidByte[i], HEX); 
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ")); 
      content.concat(String(mfrc522.uid.uidByte[i], HEX)); 
    } 
    Serial.println(); 
    Serial.print("Message : "); 
    content.toUpperCase(); 

    //caso de cartao validado
    if (content.substring(1) == "BB 0B 88 AB"){ //change here the UID of the card/cards that you want to give access 
      passagemValida();
    } 
    //caso de cartao nao validado
    else { 
      passagemInvalida();
    }
  
  
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
    delay(500); 
    noTone(BUZZER);
    
    analogWrite(GREENPIN, 0);
    analogWrite(REDPIN, 0);
}
