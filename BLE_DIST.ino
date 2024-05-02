#include <ArduinoBLE.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");  // Bluetooth® Low Energy LED Service

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int LED_1 = 14;  // pin to use for the LED
const int LED_2 = 15;  // pin to use for the LED
const int LED_3 = 16;  // pin to use for the LED
const int LED_4 = 17;  // pin to use for the LED
const int LED_5 = 18;  // pin to use for the LED
const int LED_6 = 19;  // pin to use for the LED
int distance = 100;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // set LED pin to output mode
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);
  digitalWrite(LED_6, LOW);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();
  Serial.println("BLE LED Peripheral");
}

void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to control.");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        distance = switchCharacteristic.value();
        Serial.println(distance);
        if (distance <= 5) {
          digitalWrite(LED_6, HIGH);
        } else {
          digitalWrite(LED_6, LOW);
        }
        if (distance <= 10) {
          digitalWrite(LED_5, HIGH);
        } else {
          digitalWrite(LED_5, LOW);
        }
        if (distance <= 30) {
          digitalWrite(LED_4, HIGH);
        } else {
          digitalWrite(LED_4, LOW);
        }
        if (distance <= 40) {
          digitalWrite(LED_3, HIGH);
        } else {
          digitalWrite(LED_3, LOW);
        }
        if (distance <= 50) {
          digitalWrite(LED_2, HIGH);
        } else {
          digitalWrite(LED_2, LOW);
        }
        if (distance <= 60) {
          digitalWrite(LED_1, HIGH);
        } else {
          digitalWrite(LED_1, LOW);
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from control."));
    Serial.println(central.address());
  }
}
