#include "dbwtrs.h"
void setup() {
  //tx_setup(2,3,50);
  rx_setup(2,3);
  Serial.begin(2000000);
}

void loop() {
      Serial.println(rx_data());
}
