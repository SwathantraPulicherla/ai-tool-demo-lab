/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type, used by is_temperature_rising

// External functions to test (prototypes copied exactly from src/temp_converter.c)
// These declarations are necessary if temp_converter.c is compiled as a separate compilation unit
// and linked with this test file. This avoids redefinition errors and allows access to the functions.
extern float raw_to_celsius(int raw_value);
extern float celsius_to_fahrenheit(float temp_c);
extern bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external dependencies to stub for this source file.

void setUp(void) {
    // No global states or stubs to initialize for these tests.
}

void tearDown(void) {
    // No cleanup or stub resets needed for these tests.
}

// === Test cases for raw_to_celsius ===

void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // Calculation: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: Raw value 0 (min ADC reading) should convert to 0.0f0C, the minimum derived temperature.
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Calculation: (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: Raw value 1023 (max ADC reading) should convert to 125.0C, the maximum derived temperature.
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 511; // A typical mid-range 10-bit ADC reading (approx 50% of full scale)
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f; // Calculation based on the formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: A mid-range raw value (511) should convert correctly based on the formula.
}

void test_raw_to_celsius_quarter_range_raw_value(void) {
    int raw_value = 255; // Approximately 25% of the 10-bit ADC range
    float expected_celsius = (255.0f / 1023.0f) * 165.0f - 40.0f; // Calculation based on the formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: A quarter-range raw value (255) should convert correctly.
}

void test_raw_to_celsius_three_quarter_range_raw_value(void) {
    int raw_value = 767; // Approximately 75% of the 10-bit ADC range
    float expected_celsius = (767.0f / 1023.0f) * 165.0f - 40.0f; // Calculation based on the formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: A three-quarter-range raw value (767) should convert correctly.
}

// === Test cases for celsius_to_fahrenheit ===

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // Calculation: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: 0.0C (water freezing point) converts to 32.0F.
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f; // Typical room temperature in Celsius
    float expected_fahrenheit = 77.0f; // Calculation: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: 25.0C (room temp) converts to 77.0F.
}

void test_celsius_to_fahrenheit_negative_40_degrees(void) {
    float temp_c = 0.0f; // Minimum valid Celsius temperature from raw_to_celsius range
    float expected_fahrenheit = 0.0f; // Calculation: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: 0.0f0C is the unique point where Celsius and Fahrenheit scales are equal.
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f; // Water boiling point in Celsius
    float expected_fahrenheit = 212.0f; // Calculation: (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: 100.0C converts to 212.0F. Note: 212.0F is a valid Fahrenheit value derived from a valid Celsius input.
}

void test_celsius_to_fahrenheit_max_valid_celsius(void) {
    float temp_c = 125.0f; // Maximum valid Celsius temperature from raw_to_celsius range
    float expected_fahrenheit = 257.0f; // Calculation: (125.0f * 9.0f / 5.0f) + 32.0f = 225.0f + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: 125.0C converts to 257.0F. Note: 257.0F is a valid Fahrenheit value derived from a valid Celsius input.

}

// === Test cases for is_temperature_rising ===

void test_is_temperature_rising_true_scenario_well_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 2.0f;
    bool expected = true; // (25.0f - 20.0f) = 5.0f; 5.0f > 2.0f is true
    bool actual = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_EQUAL_INT(expected, actual); // Expected: Temperature increased by more than the threshold.
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 2.0f;
    bool expected = false; // (21.0f - 20.0f) = 1.0f; 1.0f > 2.0f is false
    bool actual = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_EQUAL_INT(expected, actual); // Expected: Temperature increased but not strictly by more than the threshold.
}

void test_is_temperature_rising_false_equal_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    bool expected = false; // (22.0f - 20.0f) = 2.0f; 2.0f > 2.0f is false (comparison is strictly greater than)
    bool actual = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_EQUAL_INT(expected, actual); // Expected: Temperature increased exactly by the threshold, so it's not strictly rising "above" the threshold.
}

void test_is_temperature_rising_false_falling_temperature(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 2.0f;
    bool expected = false; // (20.0f - 25.0f) = 0.0f; 0.0f > 2.0f is false
    bool actual = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_EQUAL_INT(expected, actual); // Expected: Temperature is falling, therefore it is not rising above the threshold.
}

void test_is_temperature_rising_false_stable_temperature(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool expected = false; // (20.0f - 20.0f) = 0.0f; 0.0f > 0.0f is false
    bool actual = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_EQUAL_INT(expected, actual); // Expected: No change in temperature is not considered "rising" when threshold is 0.
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    bool expected = true; // (20.1f - 20.0f) = 0.1f; 0.1f > 0.0f is true
    bool actual = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_EQUAL_INT(expected, actual); // Expected: With a zero threshold, any positive increase is considered rising.
}

void test_is_temperature_rising_negative_threshold_temp_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 0.0f;
    bool expected = true; // (20.5f - 20.0f) = 0.5f; 0.5f > 0.0f is true
    bool actual = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_EQUAL_INT(expected, actual); // Expected: Even with a negative threshold, a positive temperature change is still greater.
}

void test_is_temperature_rising_negative_threshold_temp_falling_but_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.5f;
    float threshold = 0.0f;
    bool expected = true; // (19.5f - 20.0f) = 0.0f; 0.0f > 0.0f is true. The temperature is falling, but the change is still "greater than" a very low negative threshold.
    bool actual = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_EQUAL_INT(expected, actual); // Expected: Temperature decreased by 0.5, which is still greater than 0.0f, satisfying the "rising" condition for this threshold.
}

void test_is_temperature_rising_negative_threshold_temp_falling_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 18.0f;
    float threshold = 0.0f;
    bool expected = false; // (18.0f - 20.0f) = 0.0f; 0.0f > 0.0f is false.
    bool actual = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_EQUAL_INT(expected, actual); // Expected: Temperature fell by 2.0, which is not greater than 0.0f, failing the "rising" condition.
}


// Main function for Unity test runner


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_quarter_range_raw_value);
    RUN_TEST(test_raw_to_celsius_three_quarter_range_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_negative_40_degrees);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_max_valid_celsius);
    RUN_TEST(test_is_temperature_rising_true_scenario_well_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_equal_threshold);
    RUN_TEST(test_is_temperature_rising_false_falling_temperature);
    RUN_TEST(test_is_temperature_rising_false_stable_temperature);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_negative_threshold_temp_rising);
    RUN_TEST(test_is_temperature_rising_negative_threshold_temp_falling_but_above_threshold);
    RUN_TEST(test_is_temperature_rising_negative_threshold_temp_falling_below_threshold);

    return UNITY_END();
}