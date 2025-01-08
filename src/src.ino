#include "PhoenixJack_i2c_query.h" // https://github.com/Phoenixjack/PhoenixJack_i2c_query

PhoenixJack_i2c_query i2c_query;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("\n\n\n\n\nRunning I2C Scan [blocking]"));
  Serial.println(F("\n----RESULTS-----"));
  if (i2c_query.blocking_scan()) {
    if (i2c_query.num_devices_found > 0) {
      Serial.print(F("FOUND: "));
      Serial.println(i2c_query.found);
    }
    if (i2c_query.num_errors > 0) {
      Serial.print(F("ERRORS: "));
      Serial.println(i2c_query.errors);
    }
  } else {
    Serial.println(F("NOTHING"));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
