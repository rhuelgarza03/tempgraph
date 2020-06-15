// only using 1 library (VirtualWire)
#include <VirtualWire.h>

// PINS FOR RECEIVER
const int RX_PIN = 2;  // pin to receive data
const int PTT_PIN = 1; // for Push To Talk (not required)

void setup() {
  // Serial port for logging
  Serial.begin(9600); // 4800 because 4800bps?
  //Serial.println("starting...");

  vw_set_rx_pin(RX_PIN); // set the rx pin
  
  // vw_set_ptt_inverted(true);
  // vw_set_ptt_pin(PTT_PIN);
  // optional ^

  vw_setup(2000); // Bits per second
  vw_rx_start();  // Start the receiver PLL running
}

void loop() {
  // actually not too sure what these are
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    digitalWrite(13, true); // flash pin 13 light to show that the message was received
    
    //Serial.print("Got: ");

    String rcv;

    for (int i = 0; i < buflen; i++) {  // prints the message as characters (actual words/numbers)
      rcv += (char)buf[i];
    }
    //delay(2000);
    delay(100);
    Serial.println(rcv);
    //Serial.println(rcv);
    //Serial.println("hello");
    
    //Serial.println((char*)buf);

   /*
    for (int i = 0; i < buflen; i++) {  // prints the message as hexadecimal
      //Serial.print(buf[i], HEX);
      //Serial.println(buf[i], HEX);
      //Serial.print(" ");
    }
    */

    //Serial.println("");
    digitalWrite(13, false);
  }
}
