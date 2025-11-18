/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type
#include <string.h>  // Not strictly needed, but common for embedded tests. Removing as no use case here.
#include <math.h> // For fabsf for tolerance calculation, if needed, but Unity's FLOAT_WITHIN handles it.

// Mocked header inclusion for the device under test (DUT).
// In a real project, this would be #include "temp_converter.h" if it existed.
// Since the source code provided functions without a `.h` file and "[STRING REDACTED]"
// was present, we define the prototypes directly to allow the test file to compile.
// This is done to avoid inventing headers, as per the rules.
float raw_to_celsius(int raw_value);
float celsius_to_fahrenheit(float temp_c);
bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions to stub based on the prompt.
// setUp runs before each test
void setUp(void) {
    // No state to initialize, no stubs to reset as there are no external dependencies.
}

// tearDown runs after each test
void tearDown(void) {
    // No state to clean up, no stubs to reset.
}

// Tolerance for float comparisons (e.g., 0.1 degrees Celsius/Fahrenheit)
#define TEMPERATURE_TOLERANCE 0.01f // Using a tighter tolerance for calculations, 0.1 is quite wide.

// region: Tests for raw_to_celsius(int raw_value)

void test_raw_to_celsius_min_raw_value_yields_min_celsius(void) {
    int raw_value = 0; // Mimics 10-bit ADC min value
    float expected_celsius = 0.0f; // Expected: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value_yields_max_celsius(void) {
    int raw_value = 1023; // Mimics 10-bit ADC max value
    float expected_celsius = 125.0f; // Expected: (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 511; // Approximately mid-range for 00.0f
    float expected_celsius = (511 / 1023.0f) * 165.0f - 40.0f; // Expected: calculation based on source formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_quarter_range_raw_value(void) {
    int raw_value = 256; // Approximately quarter-range
    float expected_celsius = (256 / 1023.0f) * 165.0f - 40.0f; // Expected: calculation based on source formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_three_quarter_range_raw_value(void) {
    int raw_value = 767; // Approximately three-quarter range
    float expected_celsius = (767 / 1023.0f) * 165.0f - 40.0f; // Expected: calculation based on source formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius);
}

// endregion

// region: Tests for celsius_to_fahrenheit(float temp_c)

void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f; // Freezing point in Celsius
    float expected_fahrenheit = 32.0f; // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f; // Boiling point in Celsius
    float expected_fahrenheit = 212.0f; // Expected: (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_forty_degrees(void) {
    float temp_c = 0.0f; // Temperature where Celsius and Fahrenheit are equal
    float expected_fahrenheit = 0.0f; // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_sensor_max_celsius(void) {
    float temp_c = 125.0f; // Max Celsius output from raw_to_celsius
    float expected_fahrenheit = (125.0f * 9.0f / 5.0f) + 32.0f; // Expected: 225.0f + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f; // Typical room temperature
    float expected_fahrenheit = 77.0f; // Expected: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    float temp_c = 0.0f; // A negative Celsius value
    float expected_fahrenheit = 14.0f; // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 14.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

// endregion

// region: Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)

void test_is_temperature_rising_true_when_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 1.0f;
    bool expected_result = true; // Expected: (22.0f - 20.0f) = 2.0f > 1.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_false_when_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 1.0f;
    bool expected_result = false; // Expected: (20.5f - 20.0f) = 0.5f > 1.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_false_when_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 1.0f;
    bool expected_result = false; // Expected: (21.0f - 20.0f) = 1.0f > 1.0f is false (strictly greater)
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_false_when_falling(void) {
    float prev_temp = 20.0f;
    float current_temp = 18.0f;
    float threshold = 0.5f;
    bool expected_result = false; // Expected: (18.0f - 20.0f) = 0.0f > 0.5f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_false_when_stable_and_positive_threshold(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.1f;
    bool expected_result = false; // Expected: (25.0f - 25.0f) = 0.0f > 0.1f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_true_with_zero_threshold_and_slight_increase(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.01f;
    float threshold = 0.0f;
    bool expected_result = true; // Expected: (25.01f - 25.0f) = 0.01f > 0.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_false_with_zero_threshold_and_no_increase(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.0f;
    bool expected_result = false; // Expected: (25.0f - 25.0f) = 0.0f > 0.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_true_with_negative_threshold_and_slight_fall(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.5f;
    float threshold = 0.0f;
    bool expected_result = true; // Expected: (19.5f - 20.0f) = 0.0f > 0.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_false_with_negative_threshold_and_larger_fall(void) {
    float prev_temp = 20.0f;
    float current_temp = 18.5f;
    float threshold = 0.0f;
    bool expected_result = false; // Expected: (18.5f - 20.0f) = 0.0f > 0.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

// endregion



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value_yields_min_celsius);
    RUN_TEST(test_raw_to_celsius_max_raw_value_yields_max_celsius);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_quarter_range_raw_value);
    RUN_TEST(test_raw_to_celsius_three_quarter_range_raw_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_forty_degrees);
    RUN_TEST(test_celsius_to_fahrenheit_sensor_max_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_negative_celsius);
    RUN_TEST(test_is_temperature_rising_true_when_above_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_falling);
    RUN_TEST(test_is_temperature_rising_false_when_stable_and_positive_threshold);
    RUN_TEST(test_is_temperature_rising_true_with_zero_threshold_and_slight_increase);
    RUN_TEST(test_is_temperature_rising_false_with_zero_threshold_and_no_increase);
    RUN_TEST(test_is_temperature_rising_true_with_negative_threshold_and_slight_fall);
    RUN_TEST(test_is_temperature_rising_false_with_negative_threshold_and_larger_fall);

    return UNITY_END();
}