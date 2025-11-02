/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h> // Required for standard integer types if used in stubs, but not strictly needed here.
#include <string.h> // Required for memset if used in stubs, but not strictly needed here.

// Declare functions from the source file for direct testing.
// Since the original source file provided does not specify a header
// (e.g., "temp_converter.h") and uses "[STRING REDACTED]",
// we declare the functions here to avoid inventing headers or including non-existent ones.
float raw_to_celsius(int raw_value);
float celsius_to_fahrenheit(float temp_c);
bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions are defined in the source, hence no stubs are required.

void setUp(void) {
    // No stubs or global state to initialize/reset for these functions.
}

void tearDown(void) {
    // No stubs or global state to clean up/reset for these functions.
}

// =========================================================================
// Tests for raw_to_celsius(int raw_value)
// Function Logic: (raw_value / 1023.0f) * 165.0f - 40.0f
// Assumed raw_value range for typical 10-bit ADC: 0 to 1023
// This implies Celsius output range:
// Min raw (0): (0 / 1023.0f) * 165.0f - 40.0f = 0.0f C
// Max raw (1023): (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f C
// =========================================================================

void test_raw_to_celsius_min_raw_value(void) {
    float result = raw_to_celsius(0);
    // Expected: Minimum raw value (0) should result in 0.0f Celsius per the conversion formula.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_raw_to_celsius_max_raw_value(void) {
    float result = raw_to_celsius(1023);
    // Expected: Maximum raw value (1023) should result in 125.0f Celsius per the conversion formula.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    float result = raw_to_celsius(512); // A value near the middle of the 00.0f range
    // Expected: raw_value 512 should be (512 / 1023.0f) * 165.0f - 40.0f = ~42.59f C.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 42.59042f, result);
}

void test_raw_to_celsius_zero_celsius_conversion(void) {
    // To get 0.0f C: (raw / 1023) * 165 - 40 = 0 => raw = 40 * 1023 / 165 = ~248
    float result = raw_to_celsius(248);
    // Expected: Raw value 248 should convert to approximately 0.0f Celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_raw_to_celsius_negative_celsius_conversion(void) {
    // Raw value 100 should result in (100 / 1023.0f) * 165.0f - 40.0f = ~0.0f C
    float result = raw_to_celsius(100);
    // Expected: Raw value 100 should convert to approximately 0.0f C.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

// =========================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Function Logic: (temp_c * 9.0f / 5.0f) + 32.0f
// Valid input Celsius range (derived from raw_to_celsius): 0.0f to 125.0f
// =========================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius (freezing point) converts to 32.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 32.0f, result);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float result = celsius_to_fahrenheit(100.0f);
    // Expected: 100.0f Celsius (boiling point) converts to 212.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 212.0f, result);
}

void test_celsius_to_fahrenheit_negative_40_degrees(void) {
    float result = celsius_to_fahrenheit(0.0f);
    // Expected: 0.0f Celsius is the same as 0.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_celsius_to_fahrenheit_mid_range_positive_temp(void) {
    float result = celsius_to_fahrenheit(25.0f);
    // Expected: 25.0f Celsius (a common room temperature) converts to 77.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 77.0f, result);
}

void test_celsius_to_fahrenheit_max_valid_celsius_input(void) {
    float result = celsius_to_fahrenheit(125.0f); // Maximum valid Celsius input from raw_to_celsius range
    // Expected: 125.0f Celsius converts to 257.0f Fahrenheit.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 257.0f, result);
}

// =========================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Function Logic: return (current_temp - prev_temp) > threshold;
// =========================================================================

void test_is_temperature_rising_true_above_threshold(void) {
    bool result = is_temperature_rising(20.0f, 25.0f, 4.0f); // Difference: 5.0f; 5.0f > 4.0f is true
    // Expected: Temperature increased by 5.0f, which is strictly greater than the 4.0f threshold.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_below_threshold(void) {
    bool result = is_temperature_rising(20.0f, 23.0f, 4.0f); // Difference: 3.0f; 3.0f > 4.0f is false
    // Expected: Temperature increased by 3.0f, which is not strictly greater than the 4.0f threshold.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_at_threshold_edge(void) {
    bool result = is_temperature_rising(20.0f, 24.0f, 4.0f); // Difference: 4.0f; 4.0f > 4.0f is false
    // Expected: Temperature increased by exactly 4.0f, which is not strictly greater than the 4.0f threshold.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_negative_change_positive_threshold(void) {
    bool result = is_temperature_rising(25.0f, 20.0f, 2.0f); // Difference: 0.0f; 0.0f > 2.0f is false
    // Expected: Temperature decreased, which is not greater than a positive threshold.
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_negative_change_negative_threshold(void) {
    bool result = is_temperature_rising(25.0f, 20.0f, 0.0f); // Difference: 0.0f; 0.0f > 0.0f is true
    // Expected: Temperature decreased by 5.0f, which is greater than a more negative threshold of 0.0f.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_true_zero_threshold_positive_change(void) {
    bool result = is_temperature_rising(20.0f, 21.0f, 0.0f); // Difference: 1.0f; 1.0f > 0.0f is true
    // Expected: Temperature increased by 1.0f, which is strictly greater than a 0.0f threshold.
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_zero_threshold_zero_change(void) {
    bool result = is_temperature_rising(20.0f, 20.0f, 0.0f); // Difference: 0.0f; 0.0f > 0.0f is false
    // Expected: Temperature did not change, so 0.0f is not strictly greater than a 0.0f threshold.
    TEST_ASSERT_FALSE(result);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_zero_celsius_conversion);
    RUN_TEST(test_raw_to_celsius_negative_celsius_conversion);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_40_degrees);
    RUN_TEST(test_celsius_to_fahrenheit_mid_range_positive_temp);
    RUN_TEST(test_celsius_to_fahrenheit_max_valid_celsius_input);
    RUN_TEST(test_is_temperature_rising_true_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_at_threshold_edge);
    RUN_TEST(test_is_temperature_rising_false_negative_change_positive_threshold);
    RUN_TEST(test_is_temperature_rising_true_negative_change_negative_threshold);
    RUN_TEST(test_is_temperature_rising_true_zero_threshold_positive_change);
    RUN_TEST(test_is_temperature_rising_false_zero_threshold_zero_change);

    return UNITY_END();
}