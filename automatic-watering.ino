
#define HUMIDITY_SENSOR 10
#define WATER_PUMP 9
#define MODE 4 
#define LED 13 

#define HUMIDITY_THRESHOLD 50 //TODO estimate value //TODO2 Replace with analog input
#define PUMP_FREQUENCY 1000 // Replace with analog input
#define PUMP_ENABLE_TIME 1000 // Time to be enabled (in ms)

int mode;
int humidityRead;
long lastTimeActive;
bool pumpEnabled;

void setup(){
  pinMode(HUMIDITY_SENSOR, INPUT);
  pinMode(WATER_PUMP, OUTPUT); 
  pinMode(LED, OUTPUT); 

  pinMode(MODE, INPUT); digitalWrite(MODE,HIGH);
  
  disablePump();
  Serial.begin(9600);
}

void loop(){
  mode = LOW;//digitalRead(MODE);
  Serial.print("Mode: ");
  Serial.println(mode);
  if (mode == HIGH) { //time mode
    if (!pumpEnabled && millis() > lastTimeActive + PUMP_FREQUENCY) {
      enablePump();
      lastTimeActive = millis();
    } 
    if (pumpEnabled && millis() > lastTimeActive + PUMP_ENABLE_TIME) {
      disablePump();
      lastTimeActive = millis();
    }
  } else { //Humidity mode

    humidityRead = analogRead(A0);
    Serial.print("Humidity read: ");
     Serial.println(humidityRead);
     
    if (humidityRead < HUMIDITY_THRESHOLD) {
      if (!pumpEnabled) enablePump();
    } else {
      if (pumpEnabled) disablePump();
    }
  }
  
  //TODO replace with jeelib/sleep delay (power efficient)
  delay(1000);
}

void enablePump() {
    Serial.println("Enable pump");

    digitalWrite(WATER_PUMP, HIGH); 
    digitalWrite(LED, HIGH); 

    pumpEnabled = true;
}


void disablePump() {
  Serial.println("Disable pump");

  digitalWrite(WATER_PUMP, LOW); 
  digitalWrite(LED, LOW); 

  pumpEnabled = false;
}
