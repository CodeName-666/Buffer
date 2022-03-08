#include <Arduino.h>
#include "FiFo.h"


void setup() {
    FiFo<uint16_t> fifo_one;
    uint16_t a = 5, b = 10, c = 20;
    Serial.begin(9600);
    
    fifo_one.write(&a);
    fifo_one.write(&b);
    fifo_one.write(&c);

    Serial.print("Last value = "); Serial.println(fifo_one.read());
    Serial.print("Next value = "); Serial.println(fifo_one.read());
    Serial.print("Next value = "); Serial.println(fifo_one.read());
    Serial.print("Next value = "); Serial.println(fifo_one.read());
}

void loop() {




}