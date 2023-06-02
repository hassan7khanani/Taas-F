#include <WiFi.h>
#include <FirebaseESP32.h>
#include <LiquidCrystal_I2C.h>
#define FIREBASE_HOST "iotparking-607b2-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "UgF3KJUjOISTRQRx3IaAfnzlNn6NgRO5xDQcwfHS" // Add your Firebase authentication key here

// #define FIREBASE_HOST "testing-ceb6a-default-rtdb.firebaseio.com/" // Add your Firebase project URL here
// #define FIREBASE_AUTH "YOjqZ58qZFN8ffJhvGtokhwQqyQJurXNFJAn86RN" // Add your Firebase authentication key here
#define WIFI_SSID "V1" // Add your Wi-Fi network name here
#define WIFI_PASSWORD "12345678910" // Add your Wi-Fi network password here

#define S1_PIN 12 // Connect the S1 sensor to GPIO pin 12
#define S2_PIN 2 // Connect the S2 sensor to GPIO pin 2
#define S3_PIN 14 // Connect the S3 sensor to GPIO pin 14
#define S4_PIN 15 // Connect the S4 sensor to GPIO pin 15
// LCD pins and settings
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, LCD_ROWS);  

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  // Print the welcome message on the LCD
  lcd.print("IoT Parking App");
  lcd.setCursor(0, 1);
  lcd.print("Total Slots 04");
  delay(5000);
  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    pinMode(S1_PIN,INPUT);
    pinMode(S2_PIN,INPUT);
    pinMode(S3_PIN,INPUT);
    pinMode(S4_PIN,INPUT);
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setFloat(firebaseData,"/IoT/S1", 0);
  Firebase.setFloat(firebaseData,"/IoT/S2", 0);
  Firebase.setFloat(firebaseData,"/IoT/S3", 0);
  Firebase.setFloat(firebaseData,"/IoT/S4", 0);
}

void loop() {
  // Read values of IR sensors
  int s1Value = digitalRead(S1_PIN);
  int s2Value = digitalRead(S2_PIN);
  int s3Value = digitalRead(S3_PIN);
  int s4Value = digitalRead(S4_PIN);
  Serial.println("###################################################");
  Serial.println(s1Value);
  Serial.println(s2Value);
  Serial.println(s3Value);
  Serial.println(s4Value);

  Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

  lcd.clear();
  // lcd.print(s1Value ? "S1: Empty" : "S1: Full");
  // lcd.setCursor(0, 1);
  // lcd.print(s2Value ? "S2: Empty" : "S2: Full");
  // delay(3000);
  // lcd.clear();
  // lcd.print(s3Value ? "S3: Empty" : "S3: Full");
  // lcd.setCursor(0, 1);
  // lcd.print(s4Value ? "S4: Empty" : "S4: Full");
  // delay(3000);
  if (s1Value == LOW) {
    lcd.print("S1: Full");
  } else{
    lcd.print("S1: Empty");
  }
  lcd.setCursor(0, 1);
  if (s2Value == LOW) {
    lcd.print("S2: Full");
  } else{
    lcd.print("S2: Empty");

  delay(3000);
  lcd.clear();

  }
    if (s3Value == LOW) {
    lcd.print("S3: Full");
  } else{
    lcd.print("S3: Empty");

  }
  lcd.setCursor(0, 1);

    if (s4Value == LOW) {
    lcd.print("S4: Full");
  } else{
    lcd.print("S4: Empty");

  }
  delay(3000);
  // lcd.clear();

  // Print values
  // Serial.print("S1: ");
  // Serial.print(s1Value);
  // Serial.print(", S2: ");
  // Serial.print(s2Value);
  // Serial.print(", S3: ");
  // Serial.print(s3Value);
  // Serial.print(", S4: ");
  // Serial.println(s4Value);

  // Print "full" if the value is high and "empty" if the value is low
  if (s1Value == LOW) {
    Serial.println("S1: Parking Slot#01 is Full");
    Firebase.setFloat(firebaseData,"/IoT/S1", 0);
  } else {
    Serial.println("S1: Parking Slot#01 is Empty");
    Firebase.setFloat(firebaseData,"/IoT/S1", 1);
  }
  if (s2Value == LOW) {
    Serial.println("S2: Parking Slot#02 is Full");
    Firebase.setFloat(firebaseData,"/IoT/S2", 0);
  } else {
    Serial.println("S2: Parking Slot#02 is Empty");
    Firebase.setFloat(firebaseData,"/IoT/S2",1);
  }
  if (s3Value == LOW) {
    Serial.println("S3: Parking Slot#03 is Full");
    Firebase.setFloat(firebaseData,"/IoT/S3", 0);
  } else {
    Serial.println("S3: Parking Slot#03 is Empty");
    Firebase.setFloat(firebaseData,"/IoT/S3", 1);
  }
  if (s4Value == LOW) {
    Serial.println("S4: Parking Slot#03 is Full");
    Firebase.setFloat(firebaseData,"/IoT/S4", 0);
  } else {
    Serial.println("S4: Parking Slot#04 is Empty");
    Firebase.setFloat(firebaseData,"/IoT/S4", 1);
  }
  Serial.print("----------------------");
  Serial.println();
  delay(1000); // Wait for 1 second before reading again
}