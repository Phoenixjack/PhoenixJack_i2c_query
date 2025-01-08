# PhoenixJack_i2c_query

Collection of functions to rapidly interrogate the I2C bus; contains single query, blocking and nonblocking searches.

## Constructor
    PhoenixJack_i2c_query your_instance;

## Functions
    - byte check(byte this_address);
        returns the raw error code (0 or 4) for the given address.
    - bool isGood(byte this_address);
        returns true if given address responded.
    - bool blocking_scan();
        initiates a blocking scan of all valid I2C addresses.
        returns true if it found anything
    - byte non_blocking_scan();

## Accessible Variables
    - char found[I2C_QUERY_MAXIMUM_BUFFER_SIZE + 1];
        null-terminated array of 2 byte (hex) values
    - char errors[I2C_QUERY_MAXIMUM_BUFFER_SIZE + 1];
        null-terminated array of 2 byte (hex) values
    - byte first_address_found = 0;
        the first I2C address found during a scan
        is reset by calling blocking_scan()
    - byte last_address_found = 0;
        the last I2C address found during a scan
        is set by during blocking_scan() and non_blocking_scan()
    - uint8_t num_nonblocking_scans = 0;
        the number of full non_blocking_scan() sweeps performed
        does not reset / will rollover at 255
    - uint8_t num_devices_found = 0;
        the number of devices found
        only set or reset by blocking_scan()
    - uint8_t num_errors = 0;
        the number of devices that returned an error
        only set or reset by blocking_scan()

## ISSUES AND WARNINGS
    - Nothing is private, so DO NOT assign anything to any accessible variable
    - The char arrays (found and error) do not have a parser to break them into an array.
    - non_blocking_scan() does NOT track num_devices_found or num_errors

## TODO
    - Create an array of found addresses
    - Create a lookup feature to identify the device