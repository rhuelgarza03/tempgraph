// only using 1 library (VirtualWire)
#include <VirtualWire.h>

// PINS FOR TRANSMITTER
const int TX_PIN = 2;  // pin to receive data
const int PTT_PIN = 1; // for Push To Talk (not required)



#include <SparkFunMAX31855k.h> // Using the max31855k driver
#include <SPI.h>  // Included here too due Arduino IDE; Used in above header

// Define SPI Arduino pin numbers (Arduino Pro Mini)
const uint8_t CHIP_SELECT_PIN = 10; // Using standard CS line (SS)
// SCK & MISO are defined by Arduiino
const uint8_t VCC = 14; // Powering board straight from Arduino Pro Mini
const uint8_t GND = 15;

// Instantiate an instance of the SparkFunMAX31855k class
SparkFunMAX31855k probe(CHIP_SELECT_PIN, VCC, GND);



void setup() {
  // Serial port for logging
  Serial.begin(9600); // 4800 because 4800bps?
  //Serial.println("starting...");

  vw_set_tx_pin(TX_PIN); // set the rx pin
  
  // vw_set_ptt_inverted(true);
  // vw_set_ptt_pin(PTT_PIN);
  // optional ^

  vw_setup(2000); // Bits per second
  delay(50); // Let IC stabilize or first readings will be garbage
}
void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  float temperature = probe.readCJT(); // get temp from probe

  // Read the temperature in Fahrenheit
  temperature = probe.readTempF();
  
  if (!isnan(temperature)) {
    //Serial.print("\tTemp[F]=");
    //Serial.println(temperature);

    String thingy = String(temperature);

    int str_len = thingy.length() + 1;
    char char_array[str_len];
    
    //const char *msg = char(temperature);
    thingy.toCharArray(char_array, str_len);
    const char *msg = thingy.c_str();

    //Serial.println(msg);

    digitalWrite(13, true);                // flash light to show transmitting
  
    vw_send((uint8_t *)msg, strlen(msg));  // send the message
    vw_wait_tx();                          // wait until the whole message has sent
  
    digitalWrite(13, false);
  
    //delay(2000);                            // delay between each transmit
  }

/*
  //const char *msg = char(temperature); // message to transmit (temperature logs later)
  const char *msg = char(temperature);

  digitalWrite(13, true);                // flash light to show transmitting
  
  vw_send((uint8_t *)msg, strlen(msg));  // send the message
  vw_wait_tx();                          // wait until the whole message has sent
  
  digitalWrite(13, false);
  
  delay(200);                            // delay between each transmit
  */
}
