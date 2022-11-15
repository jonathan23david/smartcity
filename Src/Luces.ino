


#define pinLED1 6
#define pinLED2 7
#define pinLED3 8
#define pinLED4 9

void setup() {
 
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);
  pinMode(pinLED4, OUTPUT);
  
  Serial.begin(9600);
 
}

void loop() {
  Luces();
  delay(300);
}

void Luces(){
  int v = analogRead(A5);
  
  Serial.println(v);
  if (v < 630) {
    digitalWrite(pinLED1, HIGH);
    digitalWrite(pinLED2, HIGH);
    digitalWrite(pinLED3, HIGH);
    digitalWrite(pinLED4, HIGH);
  }else{
    digitalWrite(pinLED1, LOW);
    digitalWrite(pinLED2, LOW);
    digitalWrite(pinLED3, LOW);
    digitalWrite(pinLED4, LOW);
  }
}
