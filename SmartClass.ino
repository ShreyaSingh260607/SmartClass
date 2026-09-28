// Smart Classroom Energy Saver

int pirPin = 2;
int ledPin = 13;
int ldrPin = A0;
int tempPin = A1;
int motorPin = 7;

// Energy usage counters
unsigned long lightTime = 0;
unsigned long fanTime = 0;
unsigned long lastTime = 0;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  Serial.begin(9600);

  lastTime = millis();
}

void loop() {

  // Read sensors
  int motion = digitalRead(pirPin);
  int ldrValue = analogRead(ldrPin);

  int tempValue = analogRead(tempPin);
  float voltage = tempValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;

  // Light control
  bool lightOn = false;

  if (motion == HIGH && ldrValue < 400) {
    digitalWrite(ledPin, HIGH);
    lightOn = true;
  }
  else {
    digitalWrite(ledPin, LOW);
  }

  // Fan control
  bool fanOn = false;

  if (motion == HIGH && temperature >= 28) {
    digitalWrite(motorPin, HIGH);
    fanOn = true;
  }
  else {
    digitalWrite(motorPin, LOW);
  }

  // Calculate time used
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - lastTime;

  if (lightOn) {
    lightTime += elapsedTime;
  }

  if (fanOn) {
    fanTime += elapsedTime;
  }

  lastTime = currentTime;

  // Convert milliseconds to seconds
  float lightSeconds = lightTime / 1000.0;
  float fanSeconds = fanTime / 1000.0;

  // Serial Dashboard
  Serial.println();
  Serial.println("================================");
  Serial.println("     SMART CLASSROOM");
  Serial.println("================================");

  Serial.print("Room Status : ");
  if (motion == HIGH)
    Serial.println("OCCUPIED");
  else
    Serial.println("EMPTY");

  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Light       : ");
  if (lightOn)
    Serial.println("ON");
  else
    Serial.println("OFF");

  Serial.print("Fan         : ");
  if (fanOn)
    Serial.println("ON");
  else
    Serial.println("OFF");

  Serial.println("--------------------------------");
  Serial.println("ENERGY USAGE");
  Serial.println("--------------------------------");

  Serial.print("Light Used  : ");
  Serial.print(lightSeconds);
  Serial.println(" seconds");

  Serial.print("Fan Used    : ");
  Serial.print(fanSeconds);
  Serial.println(" seconds");

  Serial.println("================================");

  delay(1000);
}