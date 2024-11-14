 // Define analog input pins for V2 and V3
int V2Pin = A0;  // Pin for V2
int V3Pin = A3;  // Pin for V3

// Variables for storing voltages
float V2 = 0.0;
float V3 = 0.0;

void setup() {

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog values at V2 and V3 (from 0 to 1023)
  int analogValueV2 = analogRead(V2Pin);
  int analogValueV3 = analogRead(V3Pin);
  
   // Convert the analog values to voltages
   // Assuming 5V reference, scale by 5.0 / 1023
  V2 = (analogValueV2 * 5.0) / 1023.0;
  V3 = (analogValueV3 * 5.0) / 1023.0;

  // Print the voltages to the serial monitor
  Serial.print("V2:");
  Serial.print(V2);
  Serial.println(" V");

  Serial.print("V3:");
  Serial.print(V3);
  Serial.println("V");

   // Delay before next reading
   delay ( 1000);
}