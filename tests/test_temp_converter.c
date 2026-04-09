/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type

// External function declarations from src/temp_converter.c
// These are declared as extern to link with the actual implementation during compilation
extern float raw_to_celsius(int raw_value);
extern float celsius_to_fahrenheit(float temp_c);
extern bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions to stub, so no stub control structures are needed.

void setUp(void) {
    // No global state or stubs to reset in this module
}

void tearDown(void) {
    // No global state or stubs to clean up in this module
}

// ==============================================================================
// Tests for raw_to_celsius(int raw_value)
// Expected range: raw_value 00.0f (typical 10-bit ADC)
// Output Celsius: 0.0f to 125.0f
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// ==============================================================================

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Minimum ADC value should convert to minimum temperature 0.0f C
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Maximum ADC value should convert to maximum temperature 125.0f C
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f; // Approx 42.4f C
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: Mid-range ADC value should convert correctly based on formula
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_low_positive_raw_value(void) {
    int raw_value = 100;
    float expected_celsius = (100.0f / 1023.0f) * 165.0f - 40.0f; // Approx 0.0f C
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: A low positive ADC value should yield a negative Celsius temperature
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_high_positive_raw_value(void) {
    int raw_value = 900;
    float expected_celsius = (900.0f / 1023.0f) * 165.0f - 40.0f; // Approx 95.11f C
    float actual_celsius = raw_to_celsius(raw_value);
    // Expected: A high positive ADC value should yield a high positive Celsius temperature
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// ==============================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// ==============================================================================

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f Celsius should convert to 32.0f Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 100.0f Celsius should convert to 212.0f Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_forty_degrees(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 0.0f Celsius should convert to 0.0f Fahrenheit (the crossover point)
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 25.0f Celsius should convert to 77.0f Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_high_temperature(void) {
    float temp_c = 125.0f; // Max temperature from raw_to_celsius conversion
    float expected_fahrenheit = 257.0f; // (125.0f * 9.0f / 5.0f) + 32.0f = 225.0f + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    // Expected: 125.0f Celsius should convert to 257.0f Fahrenheit
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// ==============================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ==============================================================================

void test_is_temperature_rising_true_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.1f;
    float threshold = 2.0f;
    bool expected_rising = true; // (22.1f - 20.0f) = 2.1f; 2.1f > 2.0f is true
    bool actual_rising = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature difference (2.1f) is strictly greater than threshold (2.0f), so true
    TEST_ASSERT_TRUE(actual_rising);
}

void test_is_temperature_rising_false_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    bool expected_rising = false; // (22.0f - 20.0f) = 2.0f; 2.0f > 2.0f is false
    bool actual_rising = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature difference (2.0f) is equal to threshold (2.0f), not strictly greater, so false
    TEST_ASSERT_FALSE(actual_rising);
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.9f;
    float threshold = 2.0f;
    bool expected_rising = false; // (21.9f - 20.0f) = 1.9f; 1.9f > 2.0f is false
    bool actual_rising = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature difference (1.9f) is less than threshold (2.0f), so false
    TEST_ASSERT_FALSE(actual_rising);
}

void test_is_temperature_rising_false_falling_temperature(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 0.5f;
    bool expected_rising = false; // (20.0f - 25.0f) = 0.0f; 0.0f > 0.5f is false
    bool actual_rising = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature is falling, difference is negative, so false
    TEST_ASSERT_FALSE(actual_rising);
}

void test_is_temperature_rising_false_no_change(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.1f;
    bool expected_rising = false; // (25.0f - 25.0f) = 0.0f; 0.0f > 0.1f is false
    bool actual_rising = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: Temperature has not changed, difference is 0.0f, so false
    TEST_ASSERT_FALSE(actual_rising);
}

void test_is_temperature_rising_true_zero_threshold_slight_increase(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.01f;
    float threshold = 0.0f;
    bool expected_rising = true; // (20.01f - 20.0f) = 0.01f; 0.01f > 0.0f is true
    bool actual_rising = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: With a zero threshold, any positive increase should return true
    TEST_ASSERT_TRUE(actual_rising);
}

void test_is_temperature_rising_false_zero_threshold_no_increase(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool expected_rising = false; // (20.0f - 20.0f) = 0.0f; 0.0f > 0.0f is false
    bool actual_rising = is_temperature_rising(prev_temp, current_temp, threshold);
    // Expected: With a zero threshold, no increase should return false due to strict inequality
    TEST_ASSERT_FALSE(actual_rising);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_low_positive_raw_value);
    RUN_TEST(test_raw_to_celsius_high_positive_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty_degrees);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_high_temperature);
    RUN_TEST(test_is_temperature_rising_true_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_falling_temperature);
    RUN_TEST(test_is_temperature_rising_false_no_change);
    RUN_TEST(test_is_temperature_rising_true_zero_threshold_slight_increase);
    RUN_TEST(test_is_temperature_rising_false_zero_threshold_no_increase);

    return UNITY_END();
}