#include <IRremote.h>

// Pins
#define RECV_PIN  6
#define G_PIN     9
#define R_PIN     10
#define B_PIN     11

// Other files
#include "Codes.hpp"
#include "Functions.hpp"

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  
  irrecv.enableIRIn();    // Start the IR receiver
  pinMode(R_PIN, OUTPUT); // Set output pins
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void loop() {
  // If there is incoming signal
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    handle_ir(results.value);
    irrecv.resume();
  }
  
  set_led();
  delay(50);
}
