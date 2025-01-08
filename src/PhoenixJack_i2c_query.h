/*
	PhoenixJack_i2c_query
	V0.0.1
*/
#include <Wire.h>
const uint8_t max_buff_size = 255;

struct PhoenixJack_i2c_query{
  char found[max_buff_size + 1];
  char errors[max_buff_size + 1];
  uint8_t found_index = 0;
  uint8_t errors_index = 0;
  byte first_address_found = 0;
  byte last_address_found = 0;
  uint8_t num_nonblocking_scans = 0;
  uint8_t num_devices_found = 0;
  uint8_t num_errors = 0;
  byte check(byte this_address);
  bool isGood(byte this_address);
  bool blocking_scan();
  byte non_blocking_scan();
};

byte PhoenixJack_i2c_query::check(byte this_address) {  // should return a 0 or a 4
  Wire.beginTransmission(this_address);
  return Wire.endTransmission();
}

bool PhoenixJack_i2c_query::isGood(byte this_address) {
  return (check(this_address) == 0);
}

bool PhoenixJack_i2c_query::blocking_scan() {
  found[0] = (char)0;
  found_index = 0;
  errors[0] = (char)0;
  errors_index = 0;
  char hex_buffer[3];
  first_address_found = 0;
  num_devices_found = 0;
  num_errors = 0;
  byte curr_address, curr_error;
  for (curr_address = 1; curr_address < 127; curr_address++) {
    curr_error = check(curr_address);          // should be a 0 or a 4
    sprintf(hex_buffer, "02X", curr_address);  // format it
    if (curr_error == 0) {                     // 0 means good
      if (num_devices_found == 0) {            // if this IS the first address we've found
        first_address_found = curr_address;    // store it; it's probably our only
      }                                        //
      last_address_found = curr_address;       // store it
      strcpy(found, hex_buffer);               // append it
      num_devices_found++;                     // increment the count
    }                                          //
    if (curr_error == 4) {                     // 4 means error
      strcpy(errors, hex_buffer);              // append it
      num_errors++;                            // increment the count
    }                                          //
  }                                            //
  found[num_devices_found * 2] = (char)0;      // terminate the buffer
  errors[num_errors * 2] = (char)0;            // will always have 2 characters per entry
  return (num_devices_found > 0);
}

byte PhoenixJack_i2c_query::non_blocking_scan() {
  static byte curr_address = 0;  // initialize our static variable
  if (curr_address > 127) {      // if we've reached the end,
    curr_address = 0;            // reset to the beginning
    num_nonblocking_scans++;     // increment the counter so someone can know if we've completed a scan
  }                              //
  curr_address++;                // we'll always start with address 1; never 0
  if (isGood(curr_address)) {    // check for a response
    last_address_found = curr_address;
  }
  return last_address_found;  // returns the address of the last_address_found OR a zero if nothing has been found
}