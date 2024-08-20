#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Initialize Serial Communication
SoftwareSerial Serial1(2, 3);  // RX = 2, TX = 3
SoftwareSerial gps(10, 11);    // RX = 10, TX = 11
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

// Accelerometer Pins
#define x A1
#define y A2
#define z A3

// Variables for Accelerometer Calibration
int xsample = 0;
int ysample = 0;
int zsample = 0;
const int samples = 10;
const int minVal = -50;
const int maxVal = 50;

// GPS Variables
int gps_status = 0;
float latitude = 0;
float longitude = 0;
String Speed = "";
String gpsString = "";
char *test = "$GPRMC";

// Function Prototypes
void initModule(String cmd, char *res, int t);
void gpsEvent();
void get_gps();
void show_coordinate();
void coordinate2dec();
void Send();
void serialPrint();

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.print("Accident Alert");
  lcd.setCursor(0, 1);
  lcd.print("System");
  delay(2000);
  lcd.clear();
  lcd.print("Initializing");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait...");
  delay(1000);

  // Initialize GSM Module
  initModule("AT", "OK", 1000);
  initModule("ATE1", "OK", 1000);
  initModule("AT+CPIN?", "READY", 1000);
  initModule("AT+CMGF=1", "OK", 1000);
  initModule("AT+CNMI=2,2,0,0,0", "OK", 1000);

  lcd.clear();
  lcd.print("Calibrating");
  lcd.setCursor(0, 1);
  lcd.print("Accelerometer");
  
  for (int i = 0; i < samples; i++) {
    xsample += analogRead(x);
    ysample += analogRead(y);
    zsample += analogRead(z);
  }
  
  xsample /= samples;
  ysample /= samples;
  zsample /= samples;

  lcd.clear();
  lcd.print("Waiting For GPS");
  lcd.setCursor(0, 1);
  lcd.print("Signal");
  delay(2000);
  
  gps.begin(9600);
  get_gps();
  show_coordinate();
  
  lcd.clear();
  lcd.print("System Ready");
  delay(1000);
}

void loop() {
  int xValue = xsample - analogRead(x);
  int yValue = ysample - analogRead(y);
  int zValue = zsample - analogRead(z);

  Serial.print("x=");
  Serial.println(xValue);
  Serial.print("y=");
  Serial.println(yValue);
  Serial.print("z=");
  Serial.println(zValue);

  if (xValue < minVal || xValue > maxVal || yValue < minVal || yValue > maxVal || zValue < minVal || zValue > maxVal) {
    get_gps();
    show_coordinate();
    lcd.clear();
    lcd.print("Sending SMS");
    Send();
    lcd.clear();
    lcd.print("System Ready");
  }
}

void initModule(String cmd, char *res, int t) {
  while (true) {
    Serial1.println(cmd);
    delay(100);
    if (Serial1.find(res)) {
      Serial.println(res);
      delay(t);
      return;
    } else {
      Serial.println("Error");
    }
    delay(t);
  }
}

void gpsEvent() {
  gpsString = "";
  while (gps.available() > 0) {
    char inChar = (char)gps.read();
    gpsString += inChar;

    if (gpsString.startsWith(test)) {
      gps_status = 1;
      break;
    }
  }
}

void get_gps() {
  lcd.clear();
  lcd.print("Getting GPS Data");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait...");
  
  while (!gps_status) {
    gpsEvent();
    coordinate2dec();
  }
}

void show_coordinate() {
  lcd.clear();
  lcd.print("Lat:");
  lcd.print(latitude, 6);
  lcd.setCursor(0, 1);
  lcd.print("Log:");
  lcd.print(longitude, 6);

  Serial.print("Latitude: ");
  Serial.println(latitude, 6);
  Serial.print("Longitude: ");
  Serial.println(longitude, 6);
  Serial.print("Speed (knots): ");
  Serial.println(Speed);

  delay(2000);
  lcd.clear();
  lcd.print("Speed (Knots):");
  lcd.setCursor(0, 1);
  lcd.print(Speed);
}

void coordinate2dec() {
  String lat_degree = gpsString.substring(20, 22);
  String lat_minute = gpsString.substring(22, 29);
  String log_degree = gpsString.substring(32, 35);
  String log_minute = gpsString.substring(35, 42);
  Speed = gpsString.substring(45, 48);

  latitude = lat_degree.toFloat() + lat_minute.toFloat() / 60;
  longitude = log_degree.toFloat() + log_minute.toFloat() / 60;
}

void Send() {
  Serial1.println("AT");
  delay(500);
  serialPrint();
  
  Serial1.println("AT+CMGF=1");
  delay(500);
  serialPrint();
  
  Serial1.print("AT+CMGS=\"+1234567890\""); // Replace with actual phone number
  delay(500);
  serialPrint();
  
  Serial1.print("Latitude: ");
  Serial1.println(latitude, 6);
  Serial1.print("Longitude: ");
  Serial1.println(longitude, 6);
  Serial1.print("Speed: ");
  Serial1.println(Speed);
  Serial1.print("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=");
  Serial1.print(latitude, 6);
  Serial1.print("+");
  Serial1.print(longitude, 6);
  
  Serial1.write(26);
  delay(2000);
  serialPrint();
}

void serialPrint() {
  while (Serial1.available() > 0) {
    Serial.print((char)Serial1.read());
  }
}
