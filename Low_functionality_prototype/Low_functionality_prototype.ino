
// defines pins numbers
const int trigPin = 8;
const int echoPin = 7;
const int buzzer = 2;
const int ledPin = 13;
const int ledPin2 = 8;

// defines variables
long duration;
int distance;
int safetyDistance;


void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer, OUTPUT);
pinMode(ledPin, OUTPUT);
pinMode(ledPin2, OUTPUT);
noTone(buzzer); 
Serial.begin(9600); // Starts the serial communication
}


void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance <= 5){
  tone(buzzer, 30); 
  delay(500); 
  noTone(buzzer);
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin2, LOW);
}
else if (safetyDistance <= 15){

  noTone(buzzer);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, HIGH);
}
else{
  noTone(buzzer);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, LOW);
}

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}
