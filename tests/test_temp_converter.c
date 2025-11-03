/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <string.h> // Not strictly needed, but common for setup/teardown memset

// Declare the functions under test as extern, so the linker can find their definitions
// in the compiled source file (e.g., temp_converter.o).
extern float raw_to_celsius(int raw_value);
extern float celsius_to_fahrenheit(float temp_c);
extern bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions to stub, so stub control structs are not needed.

void setUp(void) {
    // No stubs or global state to initialize/reset for this module
}

void tearDown(void) {
    // No stubs or global state to clean up/reset for this module
}

// ====================================================================
// Tests for raw_to_celsius(int raw_value)
// Logic: (raw_value / 1023.0f) * 165.0f - 40.0f
// Input range for raw_value: typically 00.0f for a 10-bit ADC
// Output range for Celsius: 0.0f to 125.0f
// ====================================================================

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Minimum possible temperature (0.0f) when raw_value is 0
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Maximum possible temperature (125.0f) when raw_value is 1023
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 512;
    float expected_celsius = 42.6f; // (512.0f / 1023.0f) * 165.0f - 40.0f approx 42.58f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Mid-range Celsius temperature (approx 42.6f) for a mid-range raw_value (512)
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_low_mid_range_raw_value(void) {
    int raw_value = 250;
    float expected_celsius = 0.3f; // (250.0f / 1023.0f) * 165.0f - 40.0f approx 0.32f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Low-mid range Celsius temperature (approx 0.3f) for raw_value 250
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_high_mid_range_raw_value(void) {
    int raw_value = 750;
    float expected_celsius = 81.0f; // (750.0f / 1023.0f) * 165.0f - 40.0f approx 80.97f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: High-mid range Celsius temperature (approx 81.0f) for raw_value 750
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// ====================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Logic: (temp_c * 9.0f / 5.0f) + 32.0f
// Input range for temp_c: typically 0.0f to 125.0f
// ====================================================================

void test_celsius_to_fahrenheit_celsius_zero(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0 degrees Celsius should be 32 degrees Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_celsius_min(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f degrees Celsius should be 0.0f degrees Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_celsius_max(void) {
    float temp_c = 125.0f;
    float expected_fahrenheit = 257.0f; // (125.0f * 9.0f / 5.0f) + 32.0f = 225.0f + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: Maximum Celsius temperature (125.0f) should convert to 257.0f Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_celsius_boiling(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: Water boiling point at 100C should be 212F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_celsius_room_temp(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: Normal room temperature 25C should be 77F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

// ====================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ====================================================================

void test_is_temperature_rising_true_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 3.0f;
    // Expected: (25.0f - 20.0f) = 5.0f, which is > 3.0f, so true
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 3.0f;
    // Expected: (22.0f - 20.0f) = 2.0f, which is NOT > 3.0f, so false
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 23.0f;
    float threshold = 3.0f;
    // Expected: (23.0f - 20.0f) = 3.0f, which is NOT > 3.0f, so false (strict greater than)
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_falling_temp(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 3.0f;
    // Expected: (20.0f - 25.0f) = 0.0f, which is NOT > 3.0f, so false
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_stable_temp(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.5f;
    // Expected: (20.0f - 20.0f) = 0.0f, which is NOT > 0.5f, so false
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_true_negative_temps(void) {
    float prev_temp = 0.0f;
    float current_temp = 0.0f;
    float threshold = 3.0f;
    // Expected: (0.0f - 0.0f) = 5.0f, which is > 3.0f, so true
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_false_negative_temps_falling(void) {
    float prev_temp = 0.0f;
    float current_temp = 0.0f;
    float threshold = 3.0f;
    // Expected: (0.0f - 0.0f) = 0.0f, which is NOT > 3.0f, so false
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_with_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    // Expected: (20.1f - 20.0f) = 0.1f, which is > 0.0f, so true
    TEST_ASSERT_TRUE(is_temperature_rising(prev_temp, current_temp, threshold));
}

void test_is_temperature_rising_with_zero_threshold_stable(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    // Expected: (20.0f - 20.0f) = 0.0f, which is NOT > 0.0f, so false
    TEST_ASSERT_FALSE(is_temperature_rising(prev_temp, current_temp, threshold));
}

// ====================================================================
// Main test runner
// ====================================================================



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_low_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_high_mid_range_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_celsius_zero);
    RUN_TEST(test_celsius_to_fahrenheit_celsius_min);
    RUN_TEST(test_celsius_to_fahrenheit_celsius_max);
    RUN_TEST(test_celsius_to_fahrenheit_celsius_boiling);
    RUN_TEST(test_celsius_to_fahrenheit_celsius_room_temp);
    RUN_TEST(test_is_temperature_rising_true_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_at_threshold);
    RUN_TEST(test_is_temperature_rising_false_falling_temp);
    RUN_TEST(test_is_temperature_rising_false_stable_temp);
    RUN_TEST(test_is_temperature_rising_true_negative_temps);
    RUN_TEST(test_is_temperature_rising_false_negative_temps_falling);
    RUN_TEST(test_is_temperature_rising_with_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_with_zero_threshold_stable);

    return UNITY_END();
}