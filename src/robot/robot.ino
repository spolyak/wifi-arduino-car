// Robot via aREST + WiFi

#include <Adafruit_CC3000.h>
#include <SPI.h>
#include <aREST.h>
#include <avr/wdt.h>
#include <NewPing.h>

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// CC3000 pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// Robot speed
#define MOTOR_SPEED 160
#define DELAY 1000

// Motor pins
const int LEFT_MOTOR_PIN = 8;
const int RIGHT_MOTOR_PIN = 2;
const int BACK_PIN = 9;
const int WIRELESS_LED = 4;

// CC3000 instance
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT);

// Create aREST instance
aREST rest = aREST();

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Server instance
Adafruit_CC3000_Server restServer(LISTEN_PORT);

#define WLAN_SSID       "<SSID>"        // cannot be longer than 32 characters!
#define WLAN_PASS       "<password>"
#define WLAN_SECURITY   WLAN_SEC_WPA2

// Variable to be exposed to the API
int distance;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup(void)
{  
  // Start Serial
  Serial.begin(115200);

  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(BACK_PIN, OUTPUT);
  pinMode(WIRELESS_LED, OUTPUT);
      
  // Give name to robot
  rest.set_id("1");
  rest.set_name("robot");
  
  // Expose variables to REST API
  rest.variable("distance",&distance);
  
  // Expose functions
  rest.function("forward",forward);
  rest.function("backward",backward);
  rest.function("left",left);
  rest.function("right",right);
  rest.function("stop",stop);
  // Set up CC3000 and get connected to the wireless network.
  if (!cc3000.begin())
  {
    while(1);
  }
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    while(1);
  }
  Serial.println(F("get connected3..."));
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }
  Serial.println(F("start server..."));
  // Start server
  restServer.begin();
  Serial.println(F("Listening for connections..."));
  
  displayConnectionDetails();
  
  // Init sensor
  //dht.begin();
  
  wdt_enable(WDTO_4S);
  //indicate wireless is on.
  digitalWrite(WIRELESS_LED, HIGH);
}

void loop() {  

  distance = sonar.ping_cm();

  // Handle REST calls
  Adafruit_CC3000_ClientRef client = restServer.available();
  rest.handle(client);
  wdt_reset();
  
  // Check connection
  if(!cc3000.checkConnected()){while(1){}}
  wdt_reset(); 

}
int i = 0; 
// Forward
int forward(String command) {

  Serial.println(F("Go forward\r\n"));

  digitalWrite(BACK_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_PIN, LOW);
      
  return 1;
}

// Backward
int backward(String command) {
  
  Serial.println(F("Go backward\r\n"));
  digitalWrite(BACK_PIN, LOW);
  return 1;
}

// Left
int left(String command) {

  Serial.println(F("Go left\r\n"));  
  digitalWrite(BACK_PIN, HIGH);   
  digitalWrite(LEFT_MOTOR_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_PIN, HIGH);
   
  return 1;
}

// Right
int right(String command) {

  Serial.println(F("Go right\r\n"));  
  digitalWrite(BACK_PIN, HIGH);   
  digitalWrite(LEFT_MOTOR_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN, LOW); 
  return 1;
}

// Stop
int stop(String command) {

  Serial.println(F("Stop!\r\n"));  
  digitalWrite(BACK_PIN, HIGH);  
  digitalWrite(LEFT_MOTOR_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN, HIGH);  
  return 1;
}

// Print connection details of the CC3000 chip
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
