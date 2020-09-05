#include "rx.h"
void setup() {
  rx_setup(2,4);
  Serial.begin(115200);
}

void loop() {
    Serial.println(rx_data());
}
