/* test_temp_converter.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h>   // For bool type
#include <stdint.h>    // For integer types like uint32_t if needed (not strictly for this source, but good practice)
#include <string.h>    // For memset if stubs were present

// Function prototypes from temp_converter.c
// These are declared here to allow the test runner to call them directly,
// as the original source file defines them and no separate header was explicitly provided for inclusion.
float raw_to_celsius(int raw_value);
float celsius_to_fahrenheit(float temp_c);
bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions to stub for this source file.

void setUp(void) {
    // No global state or stubs to initialize for these simple functions.
}

void tearDown(void) {
    // No global state or stubs to clean up.
}

// =============================================================================================
// Tests for raw_to_celsius(int raw_value)
// Expected range of raw_value is typically 00.0f (10-bit ADC).
// Calculation: (raw_value / 1023.0f) * 165.0f - 40.0f
// This results in a Celsius range of 0.0f (for raw=0) to 125.0f (for raw=1023).
// =============================================================================================

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // Calculation: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f tolerance for float comparisons
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Calculation: (1023 / 1023.0f) * 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f tolerance for float comparisons
}

void test_raw_to_celsius_mid_raw_value(void) {
    int raw_value = 511; // Approximately half of 1023
    // Calculation: (511.0f / 1023.0f) * 165.0f - 40.0f = 42.41935...
    float expected_celsius = 42.42f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f tolerance for float comparisons
}

void test_raw_to_celsius_negative_celsius_output(void) {
    int raw_value = 205; // A value that results in a negative Celsius temperature
    // Calculation: (205.0f / 1023.0f) * 165.0f - 40.0f = 0.0f...
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f tolerance for float comparisons
}

void test_raw_to_celsius_small_positive_raw_value(void) {
    int raw_value = 1;
    // Calculation: (1.0f / 1023.0f) * 165.0f - 40.0f = 0.0f...
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Using 0.01f tolerance for float comparisons
}

// =============================================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Calculation: (temp_c * 9.0f / 5.0f) + 32.0f
// =============================================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // Standard conversion: (0 * 9/5) + 32 = 32
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for float comparisons
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // Standard conversion: (100 * 9/5) + 32 = 180 + 32 = 212
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for float comparisons
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f; // Typical room temperature
    float expected_fahrenheit = 77.0f; // Calculation: (25 * 9/5) + 32 = 45 + 32 = 77
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for float comparisons
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    float temp_c = 0.0f; // The point where Celsius and Fahrenheit scales meet
    float expected_fahrenheit = 0.0f; // Calculation: (0.0f * 9/5) + 32 = 0.0f + 32 = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for float comparisons
}

void test_celsius_to_fahrenheit_high_celsius_value(void) {
    float temp_c = 125.0f; // Max Celsius from raw_to_celsius output
    float expected_fahrenheit = 257.0f; // Calculation: (125 * 9/5) + 32 = 225 + 32 = 257
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Using 0.01f tolerance for float comparisons
}

// =============================================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// =============================================================================================

void test_is_temperature_rising_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 3.0f;
    bool expected_result = true; // (25.0f - 20.0f) > 3.0f -> 5.0f > 3.0f is TRUE
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Expected result is true as difference exceeds threshold
}

void test_is_temperature_rising_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 3.0f;
    bool expected_result = false; // (22.0f - 20.0f) > 3.0f -> 2.0f > 3.0f is FALSE
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected result is false as difference is below threshold
}

void test_is_temperature_rising_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 23.0f;
    float threshold = 3.0f;
    bool expected_result = false; // (23.0f - 20.0f) > 3.0f -> 3.0f > 3.0f is FALSE (strictly greater than)
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected result is false as difference is equal to threshold (not strictly greater)
}

void test_is_temperature_rising_falling_temperature(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 3.0f;
    bool expected_result = false; // (20.0f - 25.0f) > 3.0f -> 0.0f > 3.0f is FALSE
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected result is false as temperature is falling
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    bool expected_result = true; // (20.1f - 20.0f) > 0.0f -> 0.1f > 0.0f is TRUE
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Expected result is true for any increase with zero threshold
}

void test_is_temperature_rising_zero_threshold_steady(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool expected_result = false; // (20.0f - 20.0f) > 0.0f -> 0.0f > 0.0f is FALSE
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected result is false when temperature is steady with zero threshold
}

void test_is_temperature_rising_negative_threshold_significant_drop(void) {
    float prev_temp = 20.0f;
    float current_temp = 10.0f;
    float threshold = 0.0f;
    bool expected_result = false; // (10.0f - 20.0f) > 0.0f -> 0.0f > 0.0f is FALSE
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected result is false as drop is larger than negative threshold
}

void test_is_temperature_rising_negative_threshold_slight_drop(void) {
    float prev_temp = 20.0f;
    float current_temp = 16.0f;
    float threshold = 0.0f;
    bool expected_result = true; // (16.0f - 20.0f) > 0.0f -> 0.0f > 0.0f is TRUE
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Expected result is true as drop is not larger than negative threshold (i.e., it's "rising" relative to the negative threshold)
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_negative_celsius_output);
    RUN_TEST(test_raw_to_celsius_small_positive_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_negative_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_high_celsius_value);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_falling_temperature);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_steady);
    RUN_TEST(test_is_temperature_rising_negative_threshold_significant_drop);
    RUN_TEST(test_is_temperature_rising_negative_threshold_slight_drop);

    return UNITY_END();
}