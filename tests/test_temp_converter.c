/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For bool type

// Function declarations from the source file.
// We declare them here to directly test the functions defined in temp_converter.c.
// No separate header file (e.g., "temp_converter.h") is included as it was not provided
// and the functions are fully defined in the source, implying they can be linked directly.
float raw_to_celsius(int raw_value);
float celsius_to_fahrenheit(float temp_c);
bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// Define a common tolerance for float comparisons, suitable for temperature calculations.
// A tolerance of 0.1f is generally appropriate for practical temperature measurements.
#define TEMPERATURE_TOLERANCE 0.1f

void setUp(void) {
    // No external dependencies are listed for stubbing, so no setup is required here.
    // This function must still be present as per Unity framework requirements.
}

void tearDown(void) {
    // No external dependencies are listed for stubbing, so no cleanup is required here.
    // This function must still be present as per Unity framework requirements.
}

// --- Tests for raw_to_celsius function ---

/**
 * @brief Test `raw_to_celsius` with the minimum possible raw sensor value (0).
 *        Expects conversion to the minimum Celsius temperature supported by the sensor range (0.0f C).
 */
void test_raw_to_celsius_min_raw_value_should_be_min_celsius(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // Calculation: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius); // Assert min raw value maps to min Celsius
}

/**
 * @brief Test `raw_to_celsius` with the maximum possible raw sensor value (1023).
 *        Expects conversion to the maximum Celsius temperature supported by the sensor range (125.0f C).
 */
void test_raw_to_celsius_max_raw_value_should_be_max_celsius(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Calculation: (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius); // Assert max raw value maps to max Celsius
}

/**
 * @brief Test `raw_to_celsius` with a mid-range raw sensor value (e.g., 511, approximately half of 1023).
 *        Verifies the calculation for a typical operational point.
 */
void test_raw_to_celsius_mid_range_raw_value(void) {
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511 / 1023.0f) * 165.0f - 40.0f; // Calculation: (0.4995f) * 165.0f - 40.0f = 82.4175f - 40.0f = 42.4175f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius); // Assert mid-range raw value calculation
}

/**
 * @brief Test `raw_to_celsius` for a raw value that should correspond to the freezing point (0.0f Celsius).
 *        The raw value is approximated by solving the inverse formula: raw = 1023 * (Celsius + 40) / 165.
 */
void test_raw_to_celsius_freezing_point(void) {
    // For 0.0f C: raw = 1023.0f * (0.0f + 40.0f) / 165.0f = 1023.0f * 40.0f / 165.0f = 248.0f (approx)
    int raw_value = 248;
    float expected_celsius = 0.0f; // Expected output should be close to 0C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius); // Assert raw value converts to freezing point
}

/**
 * @brief Test `raw_to_celsius` for a raw value that should correspond to a typical room temperature (25.0f Celsius).
 *        The raw value is approximated by solving the inverse formula.
 */
void test_raw_to_celsius_room_temperature(void) {
    // For 25.0f C: raw = 1023.0f * (25.0f + 40.0f) / 165.0f = 1023.0f * 65.0f / 165.0f = 403.0f (approx)
    int raw_value = 403;
    float expected_celsius = 25.0f; // Expected output should be close to 25C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_celsius, actual_celsius); // Assert raw value converts to room temperature
}

// --- Tests for celsius_to_fahrenheit function ---

/**
 * @brief Test `celsius_to_fahrenheit` with the freezing point (0.0f Celsius).
 *        Expects conversion to 32.0f Fahrenheit.
 */
void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f; // Valid Celsius input
    float expected_fahrenheit = 32.0f; // Calculation: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit); // Assert 0C converts to 32F
}

/**
 * @brief Test `celsius_to_fahrenheit` with the boiling point (100.0f Celsius).
 *        Expects conversion to 212.0f Fahrenheit. Note: 100C is within the operational range of many sensors.
 */
void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f; // Valid Celsius input (within -40C to 125C range)
    float expected_fahrenheit = 212.0f; // Calculation: (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit); // Assert 100C converts to 212F
}

/**
 * @brief Test `celsius_to_fahrenheit` with the minimum valid Celsius temperature (0.0f C).
 *        Expects conversion to 0.0f Fahrenheit, as this is the point where both scales align.
 */
void test_celsius_to_fahrenheit_min_valid_celsius(void) {
    float temp_c = 0.0f; // Minimum valid Celsius input from sensor range (-40C to 125C)
    float expected_fahrenheit = 0.0f; // Calculation: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit); // Assert -40C converts to -40F
}

/**
 * @brief Test `celsius_to_fahrenheit` with the maximum valid Celsius temperature (125.0f C).
 *        Expects conversion to 257.0f Fahrenheit.
 */
void test_celsius_to_fahrenheit_max_valid_celsius(void) {
    float temp_c = 125.0f; // Maximum valid Celsius input from sensor range (-40C to 125C)
    float expected_fahrenheit = 257.0f; // Calculation: (125.0f * 9.0f / 5.0f) + 32.0f = 225.0f + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit); // Assert 125C converts to 257F
}

/**
 * @brief Test `celsius_to_fahrenheit` with a common room temperature (25.0f Celsius).
 *        Expects conversion to 77.0f Fahrenheit.
 */
void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f; // Common room temperature (within -40C to 125C range)
    float expected_fahrenheit = 77.0f; // Calculation: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(TEMPERATURE_TOLERANCE, expected_fahrenheit, actual_fahrenheit); // Assert 25C converts to 77F
}

// --- Tests for is_temperature_rising function ---

/**
 * @brief Test `is_temperature_rising` when the temperature rise significantly exceeds the threshold.
 *        Expects `true`.
 */
void test_is_temperature_rising_true_when_rise_exceeds_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.1f;
    float threshold = 2.0f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Assert that temperature is rising: (22.1 - 20.0) = 2.1; 2.1 > 2.0 is true
}

/**
 * @brief Test `is_temperature_rising` when the temperature rise exactly equals the threshold.
 *        Expects `false` because the comparison is strictly greater than (>).
 */
void test_is_temperature_rising_false_when_rise_equals_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Assert that temperature is not rising: (22.0 - 20.0) = 2.0; 2.0 > 2.0 is false
}

/**
 * @brief Test `is_temperature_rising` when the temperature rise is below the threshold.
 *        Expects `false`.
 */
void test_is_temperature_rising_false_when_rise_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.9f;
    float threshold = 2.0f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Assert that temperature is not rising: (21.9 - 20.0) = 1.9; 1.9 > 2.0 is false
}

/**
 * @brief Test `is_temperature_rising` when the temperature is actually falling.
 *        Expects `false`.
 */
void test_is_temperature_rising_false_when_falling(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 2.0f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Assert that temperature is not rising: (20.0 - 25.0) = 0.0f; 0.0f > 2.0 is false
}

/**
 * @brief Test `is_temperature_rising` with a zero threshold and a very slight temperature increase.
 *        Expects `true` as any positive difference will exceed a zero threshold.
 */
void test_is_temperature_rising_true_with_zero_threshold_and_slight_rise(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.01f;
    float threshold = 0.0f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Assert even a slight rise is detected: (20.01 - 20.0) = 0.01; 0.01 > 0.0 is true
}

/**
 * @brief Test `is_temperature_rising` with a zero threshold and no change in temperature.
 *        Expects `false` as `0.0 > 0.0` is false.
 */
void test_is_temperature_rising_false_with_zero_threshold_and_no_rise(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Assert no rise detected: (20.0 - 20.0) = 0.0; 0.0 > 0.0 is false
}

/**
 * @brief Test `is_temperature_rising` with temperatures at the high end of the valid range.
 *        Expects `true` for a rise exceeding threshold.
 */
void test_is_temperature_rising_high_end_range_true(void) {
    float prev_temp = 120.0f; // High end, but within -40C to 125C
    float current_temp = 123.0f; // High end, but within -40C to 125C
    float threshold = 2.0f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // (123.0 - 120.0) = 3.0; 3.0 > 2.0 is true
}

/**
 * @brief Test `is_temperature_rising` with temperatures at the low end of the valid range.
 *        Expects `false` for a rise not exceeding threshold.
 */
void test_is_temperature_rising_low_end_range_false(void) {
    float prev_temp = 0.0f; // Low end, but within -40C to 125C
    float current_temp = 0.0f; // Low end, but within -40C to 125C
    float threshold = 1.0f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // (0.0f - 0.0f) = 0.5; 0.5 > 1.0 is false
}


// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value_should_be_min_celsius);
    RUN_TEST(test_raw_to_celsius_max_raw_value_should_be_max_celsius);
    RUN_TEST(test_raw_to_celsius_mid_range_raw_value);
    RUN_TEST(test_raw_to_celsius_freezing_point);
    RUN_TEST(test_raw_to_celsius_room_temperature);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_min_valid_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_max_valid_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_room_temperature);
    RUN_TEST(test_is_temperature_rising_true_when_rise_exceeds_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_rise_equals_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_rise_below_threshold);
    RUN_TEST(test_is_temperature_rising_false_when_falling);
    RUN_TEST(test_is_temperature_rising_true_with_zero_threshold_and_slight_rise);
    RUN_TEST(test_is_temperature_rising_false_with_zero_threshold_and_no_rise);
    RUN_TEST(test_is_temperature_rising_high_end_range_true);
    RUN_TEST(test_is_temperature_rising_low_end_range_false);

    return UNITY_END();
}