// original sketch: http://www.geothread.net/arduino-making-a-simple-bluetooth-data-logger/
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
// Uncomment whatever type sensor you are using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
#define TEMPTYPE 0 // Use 0 for Celsius, 1 for Fahrenheit
#define DHTPIN 12
DHT dht(DHTPIN, DHTTYPE); // Define Temp Sensor

void setup() {
/* Set the baud rate for the software serial port */
//BluetoothSerial.begin(57600); // Initialise BlueTooth - in original sketch
BluetoothSerial.begin(9600); // Initialise BlueTooth - for may device
delay(1000);
dht.begin(); // Initialize DHT Teperature Sensor
BluetoothSerial.print("Starting ...");
}

void loop() {
// Take readings
int8_t h = dht.readHumidity(); // Read humidity
int16_t t = dht.readTemperature(TEMPTYPE); // read temperature
delay(500);
if ( t == BAD_TEMP || h == BAD_HUM ) { // if error conditions (see TinyDHT.h)
} else {
BluetoothSerial.print("Temperature: ");
BluetoothSerial.print(t);
BluetoothSerial.print(", Humidity: ");
BluetoothSerial.print(h);
BluetoothSerial.print("\n");
}
delay(500);
}
