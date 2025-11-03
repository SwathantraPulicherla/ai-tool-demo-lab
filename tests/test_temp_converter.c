/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <string.h> // Not strictly needed but commonly included
#include <stdint.h> // Not strictly needed but commonly included

// Include the source file directly for internal functions or use a header if available
// For this problem, assume direct access to functions defined in the .c file for testing.
// In a real project, you would include "temp_converter.h" if it existed.
// Since the prompt instructs "ONLY use existing headers from source" and "temp_converter.h" is redacted,
// we'll proceed assuming the compiler will see the function definitions from the source
// by including the source file for testing purposes, or by declaring them as extern.
// Given the setup of Unity for embedded, often the source .c file is compiled directly with the test file.
// To avoid compilation errors for the test file not knowing the function prototypes,
// we will declare them here.

// Function prototypes from src/temp_converter.c
extern float raw_to_celsius(int raw_value);
extern float celsius_to_fahrenheit(float temp_c);
extern bool is_temperature_rising(float prev_temp, float current_temp, float threshold);


// No external functions to stub, so no stub structures or functions are needed.

void setUp(void) {
    // No global state to initialize or stubs to reset since there are no external dependencies or global variables.
}

void tearDown(void) {
    // No global state to clean up or stubs to reset.
}

// ====================================================================================================
// Tests for raw_to_celsius(int raw_value)
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// Expected range of raw_value: 0 to 1023 (typical for 10-bit ADC where 1023 is max reading)
// Corresponding Celsius range: 0.0f to 125.0f
// ====================================================================================================

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Raw value 0 should convert to 0.0f Celsius
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Raw value 1023 should convert to 125.0 Celsius
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_raw_value(void) {
    int raw_value = 511; // Approximately mid-range for 00.0f
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f; // Calculation for mid-range
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Raw value 511 should convert to calculated Celsius value (approx 42.4 Celsius)
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_quarter_raw_value(void) {
    int raw_value = 255; // Approximately a quarter of the max raw value
    float expected_celsius = (255.0f / 1023.0f) * 165.0f - 40.0f; // Calculation for a quarter range
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Raw value 255 should convert to calculated Celsius value (approx 0.9 Celsius)
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// ====================================================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// Realistic temp_c range from raw_to_celsius: 0.0f to 125.0f
// ====================================================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0 Celsius (freezing) should convert to 32.0 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 100.0 Celsius (boiling) should convert to 212.0 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 25.0 Celsius (room temp) should convert to 77.0 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_same_value(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f Celsius should convert to 0.0f Fahrenheit (the point where scales meet)
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_max_valid_celsius(void) {
    float temp_c = 125.0f; // Max Celsius from raw_to_celsius conversion
    float expected_fahrenheit = (125.0f * 9.0f / 5.0f) + 32.0f; // 225.0f + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 125.0 Celsius should convert to 257.0 Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// ====================================================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ====================================================================================================

void test_is_temperature_rising_true_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.1f;
    float threshold = 2.0f;
    bool expected_result = true; // (22.1 - 20.0) = 2.1; 2.1 > 2.0 is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temperature rising significantly above threshold should return true
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_false_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    bool expected_result = false; // (22.0 - 20.0) = 2.0; 2.0 > 2.0 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temperature increase exactly equal to threshold should return false (due to strict '>')
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.9f;
    float threshold = 2.0f;
    bool expected_result = false; // (21.9 - 20.0) = 1.9; 1.9 > 2.0 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Current temperature increase below threshold should return false
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_false_falling_temperature(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 1.0f;
    bool expected_result = false; // (20.0 - 25.0) = 0.0f; 0.0f > 1.0 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Falling temperature should return false
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_false_stable_temperature_zero_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.0f;
    bool expected_result = false; // (25.0 - 25.0) = 0.0; 0.0 > 0.0 is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Stable temperature with zero threshold should return false
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_true_rising_temperature_zero_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.1f;
    float threshold = 0.0f;
    bool expected_result = true; // (25.1 - 25.0) = 0.1; 0.1 > 0.0 is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Slightly rising temperature with zero threshold should return true
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_true_with_negative_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.5f; // A slight drop
    float threshold = 0.0f;
    bool expected_result = true; // (19.5 - 20.0) = 0.0f; 0.0f > 0.0f is true (meaning it's not falling "too much")
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: A slight drop might still be considered "rising" if the negative threshold is lower than the drop
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_false_with_negative_threshold_significant_drop(void) {
    float prev_temp = 20.0f;
    float current_temp = 18.0f; // A significant drop
    float threshold = 0.0f;
    bool expected_result = false; // (18.0 - 20.0) = 0.0f; 0.0f > 0.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: A significant drop falling below a negative threshold should return false
    TEST_ASSERT_FALSE(actual_result);
}


// ====================================================================================================
// Main test runner
// ====================================================================================================


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_quarter_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_negative_same_value);
    RUN_TEST(test_celsius_to_fahrenheit_max_valid_celsius);
    RUN_TEST(test_is_temperature_rising_true_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_falling_temperature);
    RUN_TEST(test_is_temperature_rising_false_stable_temperature_zero_threshold);
    RUN_TEST(test_is_temperature_rising_true_rising_temperature_zero_threshold);
    RUN_TEST(test_is_temperature_rising_true_with_negative_threshold);
    RUN_TEST(test_is_temperature_rising_false_with_negative_threshold_significant_drop);

    return UNITY_END();
}