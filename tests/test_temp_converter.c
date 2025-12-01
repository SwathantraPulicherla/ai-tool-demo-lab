/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type

// Function declarations from src/temp_converter.c
// These declarations allow the test file to call the functions defined in temp_converter.c
// without including a non-existent header file or causing multiple definition errors
// by including the .c file directly.
float raw_to_celsius(int raw_value);
float celsius_to_fahrenheit(float temp_c);
bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions to stub, so stub definitions are not needed.

void setUp(void) {
    // No global state or stubs to reset for these simple functions.
}

void tearDown(void) {
    // No cleanup required.
}

// ==============================================================================
// Tests for raw_to_celsius(int raw_value)
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// Input range for raw_value typically 00.0f for 10-bit ADC.
// Expected output range: 0.0f C to 125.0f C.
// ==============================================================================

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Minimum raw value of 0 should correspond to 0.0f C.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Maximum raw value of 1023 should correspond to 125.0 C.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_raw_value(void) {
    int raw_value = 511; // Approximately mid-range for 10-bit ADC
    float expected_celsius = (511 / 1023.0f) * 165.0f - 40.0f; // Approx. 41.5 C
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: A mid-range raw value (511) should yield a positive celsius temperature (approx 41.5 C).
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_typical_room_temp(void) {
    int raw_value = 410; // Value chosen to approximate 25.0 C ( (25+40)/165 * 1023 = 409.8 )
    float expected_celsius = 25.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: A raw value around 410 should convert to a typical room temperature of 25.0 C.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_below_zero(void) {
    int raw_value = 200; // Value for a temperature below 0 C ( (0+40)/165 * 1023 = 248)
    float expected_celsius = (200 / 1023.0f) * 165.0f - 40.0f; // Approx. 0.0f C
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: A raw value around 200 should convert to a negative celsius temperature (approx 0.0f C).
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// ==============================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// ==============================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0.0 * 9.0 / 5.0) + 32.0 = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0 C (freezing point) converts to 32.0 F.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100.0 * 9.0 / 5.0) + 32.0 = 180.0 + 32.0 = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 100.0 C (boiling point) converts to 212.0 F.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // (25.0 * 9.0 / 5.0) + 32.0 = 45.0 + 32.0 = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 25.0 C (room temperature) converts to 77.0 F.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_temperature(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 14.0f; // (0.0f * 9.0 / 5.0) + 32.0 = 0.0f + 32.0 = 14.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f C converts to 14.0 F.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_max_temp_c(void) {
    float temp_c = 125.0f; // Max value from raw_to_celsius conversion
    float expected_fahrenheit = 257.0f; // (125.0 * 9.0 / 5.0) + 32.0 = 225.0 + 32.0 = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 125.0 C converts to 257.0 F.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_min_temp_c(void) {
    float temp_c = 0.0f; // Min value from raw_to_celsius conversion
    float expected_fahrenheit = 0.0f; // (0.0f * 9.0 / 5.0) + 32.0 = 0.0f + 32.0 = 0.0f (unique property)
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f C converts to 0.0f F.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

// ==============================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ==============================================================================

void test_is_temperature_rising_truly_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: current_temp (25.0) - prev_temp (20.0) = 5.0, which is > threshold (2.0), so true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_barely_rising_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.01f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: current_temp (22.01) - prev_temp (20.0) = 2.01, which is > threshold (2.0), so true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: current_temp (22.0) - prev_temp (20.0) = 2.0, which is NOT > threshold (2.0), so false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_rising_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: current_temp (21.0) - prev_temp (20.0) = 1.0, which is NOT > threshold (2.0), so false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_falling(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: current_temp (20.0) - prev_temp (25.0) = 0.0f, which is NOT > threshold (2.0), so false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_no_change(void) {
    float prev_temp = 22.0f;
    float current_temp = 22.0f;
    float threshold = 0.5f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: current_temp (22.0) - prev_temp (22.0) = 0.0, which is NOT > threshold (0.5), so false.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: current_temp (20.1) - prev_temp (20.0) = 0.1, which is > threshold (0.0), so true.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_zero_threshold_no_change(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: current_temp (20.0) - prev_temp (20.0) = 0.0, which is NOT > threshold (0.0), so false.
    TEST_ASSERT_FALSE(result);
}


// ==============================================================================
// Main function to run all tests
// ==============================================================================


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_typical_room_temp);
    RUN_TEST(test_raw_to_celsius_below_zero);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_negative_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_max_temp_c);
    RUN_TEST(test_celsius_to_fahrenheit_min_temp_c);
    RUN_TEST(test_is_temperature_rising_truly_rising);
    RUN_TEST(test_is_temperature_rising_barely_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_falling);
    RUN_TEST(test_is_temperature_rising_no_change);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_no_change);

    return UNITY_END();
}