// original sketch from http://www.geothread.net/arduino-making-a-simple-bluetooth-data-logger/
// adapted sketch by niq_ro from http://www.tehnic.go.ro
// BT Data Logger
// BlueTooth Configuration
/* Include the software serial port library */
#include <SoftwareSerial.h>
/* to communicate with the Bluetooth module's TXD pin */
#define BT_SERIAL_TX 10
/* to communicate with the Bluetooth module's RXD pin */
#define BT_SERIAL_RX 11
/* Initialise the software serial port */
SoftwareSerial BluetoothSerial(BT_SERIAL_TX, BT_SERIAL_RX);

// DHT-11 Configuration
#include <TinyDHT.h> // lightweight DHT sensor library
// https://github.com/adafruit/TinyDHT
// Uncomment whatever type sensor you are using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
#define TEMPTYPE 0 // Use 0 for Celsius, 1 for Fahrenheit
#define DHTPIN 12
DHT dht(DHTPIN, DHTTYPE); // Define Temp Sensor

int nr = 0;

void setup() {
/* Set the baud rate for the software serial port */
//BluetoothSerial.begin(57600); // Initialise BlueTooth
BluetoothSerial.begin(9600); // Initialise BlueTooth
BluetoothSerial.setTimeout(10000); // timeout for BlueTooth connexion
Serial.begin(9600);
Serial.setTimeout(10000); // timeout for BlueTooth connexion
delay(1000);
dht.begin(); // Initialize DHT Teperature Sensor
BluetoothSerial.print("Starting ...");
Serial.println("Starting ...");
}

void loop() {
delay(5000);
// Take readings
int8_t h = dht.readHumidity(); // Read humidity
int16_t t = dht.readTemperature(TEMPTYPE); // read temperature

delay(1000);
//h = 34;
//t = 32;

if ( t == BAD_TEMP || h == BAD_HUM ) { // if error conditions (see TinyDHT.h)
} else {
// send data on bluetooth device (HC-05 in my case, but work with any bluetooth device)
BluetoothSerial.print(nr);
BluetoothSerial.print(") Temperature: ");
BluetoothSerial.print(t);
BluetoothSerial.print("^C, Humidity: ");
BluetoothSerial.print(h);
BluetoothSerial.print("%RH");
BluetoothSerial.print("\n");

delay(100);
// send data on serial monitor
Serial.print(nr);
Serial.print(") Temperature: ");
Serial.print(t);
Serial.print("^C, Humidity: ");
Serial.print(h);
Serial.print("%RH");
Serial.print("\n");

}

nr = nr + 1;
}
