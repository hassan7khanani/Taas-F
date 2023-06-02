#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// Firebase Authentication credentials
#define FIREBASE_HOST "iotparking-607b2-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "UgF3KJUjOISTRQRx3IaAfnzlNn6NgRO5xDQcwfHS"

// WiFi credentials
#define WIFI_SSID "V1"
#define WIFI_PASSWORD "12345678910"

// IR sensor pins
#define S1_PIN 2
#define S2_PIN 3
#define S3_PIN 4
#define S4_PIN 5

// LCD pins and settings
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Print the welcome message on the LCD
  lcd.print("IoT Parking App");
  lcd.setCursor(0, 1);
  lcd.print("Total Slots 04");
  delay(5000);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Set the initial state of the parking slots in Firebase
  Firebase.setBool(firebaseData, "s1", LOW);
  Firebase.setBool(firebaseData, "s2", LOW);
  Firebase.setBool(firebaseData, "s3", LOW);
  Firebase.setBool(firebaseData, "s4", LOW);
}

void loop() {
  // Read the state of each IR sensor
  int s1State = digitalRead(S1_PIN);
  int s2State = digitalRead(S2_PIN);
  int s3State = digitalRead(S3_PIN);
  int s4State = digitalRead(S4_PIN);

  // Update the state of each parking slot in Firebase
  Firebase.setBool(firebaseData, "s1", s1State);
  Firebase.setBool(firebaseData, "s2", s2State);
  Firebase.setBool(firebaseData, "s3", s3State);
  Firebase.setBool(firebaseData, "s4", s4State);

  // Print the state of each parking slot on the LCD
  lcd.clear();
  lcd.print(s1State ? "S1: Full" : "S1: Empty");
  lcd.setCursor(0, 1);
  lcd.print(s2State ? "S2: Full" : "S2: Empty");
  delay(3000);
  lcd.clear();
  lcd.print(s3State ? "S3: Full" : "S3: Empty");
  lcd.setCursor(0, 1);
  lcd.print(s4State ? "S4: Full" : "S4: Empty");
  delay(3000);
}
