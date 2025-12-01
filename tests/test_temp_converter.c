/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // For 'bool' type
#include <string.h>  // Not strictly needed for this module, but included as a common utility header in embedded testing if stubs were present.

// Extern declarations for the functions under test
// These functions are defined in src/temp_converter.c and exposed for testing.
extern float raw_to_celsius(int raw_value);
extern float celsius_to_fahrenheit(float temp_c);
extern bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions to stub are specified, so no stub control structures are needed.

void setUp(void) {
    // No stubs or global state to initialize/reset for this specific module,
    // as all dependencies are internal and tested directly or no dependencies exist.
}

void tearDown(void) {
    // No stubs or global state to clean up for this specific module.
}

// ====================================================================
// Tests for raw_to_celsius
// Logic: (raw_value / 1023.0f) * 165.0f - 40.0f
// Assumed raw_value range: 0 to 1023 (typical for a 10-bit ADC)
// Corresponding Celsius output range: 0.0f to 125.0f
// Tolerance for temperature assertions: 0.1f as per requirements.
// ====================================================================

void test_raw_to_celsius_MinRawValue(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // Calculation: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: Minimum raw value should result in minimum Celsius output.
}

void test_raw_to_celsius_MaxRawValue(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Calculation: (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: Maximum raw value should result in maximum Celsius output.
}

void test_raw_to_celsius_MidRawValue(void) {
    int raw_value = 511; // Approximately half of the 10-bit ADC range (00.0f)
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f; // Calculation: Approximately 42.49C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: Mid-range raw value should yield a corresponding mid-range Celsius temperature.
}

void test_raw_to_celsius_TypicalRoomTemperature(void) {
    // raw_value for ~25.0C: 25 = (raw/1023)*165 - 40 => 65 = (raw/1023)*165 => raw = (65*1023)/165 = 403.45. Using 403.
    int raw_value = 403;
    float expected_celsius = (403.0f / 1023.0f) * 165.0f - 40.0f; // Calculation: Approximately 24.96C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: A raw value corresponding to a typical room temperature.
}

void test_raw_to_celsius_NegativeOutputTemperature(void) {
    // raw_value for ~0.0f0C: 0.0f = (raw/1023)*165 - 40 => 30 = (raw/1023)*165 => raw = (30*1023)/165 = 186.
    int raw_value = 186;
    float expected_celsius = (186.0f / 1023.0f) * 165.0f - 40.0f; // Calculation: Approximately 0.0f04C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: A raw value resulting in a negative Celsius temperature.
}

// ====================================================================
// Tests for celsius_to_fahrenheit
// Logic: (temp_c * 9.0f / 5.0f) + 32.0f
// Tolerance for temperature assertions: 0.1f as per requirements.
// ====================================================================

void test_celsius_to_fahrenheit_FreezingPoint(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // Calculation: (0 * 9/5) + 32 = 32
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: 0 degrees Celsius should convert to 32 degrees Fahrenheit.
}

void test_celsius_to_fahrenheit_BoilingPoint(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // Calculation: (100 * 9/5) + 32 = 180 + 32 = 212
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: 100 degrees Celsius should convert to 212 degrees Fahrenheit.
}

void test_celsius_to_fahrenheit_MinCelsiusEquivalence(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // Calculation: (0.0f * 9/5) + 32 = 0.0f + 32 = 0.0f (where Celsius and Fahrenheit are equal)
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: 0.0f degrees Celsius should convert to 0.0f degrees Fahrenheit.
}

void test_celsius_to_fahrenheit_MaxCelsiusFromSensor(void) {
    float temp_c = 125.0f; // Maximum temperature output from raw_to_celsius()
    float expected_fahrenheit = 257.0f; // Calculation: (125 * 9/5) + 32 = 225 + 32 = 257
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: Maximum sensor Celsius output converts correctly to Fahrenheit.
}

void test_celsius_to_fahrenheit_TypicalRoomTemperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // Calculation: (25 * 9/5) + 32 = 45 + 32 = 77
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit); // Expected: A typical room temperature in Celsius converts correctly to Fahrenheit.
}

// ====================================================================
// Tests for is_temperature_rising
// Logic: (current_temp - prev_temp) > threshold
// This function checks a boolean condition based on temperature difference.
// ====================================================================

void test_is_temperature_rising_ClearlyRising(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 0.5f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Expected: Temperature difference (1.0f) is strictly greater than threshold (0.5f).
}

void test_is_temperature_rising_RisingExactlyAtThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 0.5f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected: Temperature difference (0.5f) is NOT strictly greater than threshold (0.5f).
}

void test_is_temperature_rising_RisingBelowThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.4f;
    float threshold = 0.5f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected: Temperature difference (0.4f) is NOT strictly greater than threshold (0.5f).
}

void test_is_temperature_rising_StableTemperature(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.1f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected: Temperature difference (0.0f) is NOT strictly greater than threshold (0.1f).
}

void test_is_temperature_rising_FallingTemperature(void) {
    float prev_temp = 30.0f;
    float current_temp = 29.0f;
    float threshold = 0.5f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected: Temperature difference (0.0f) is NOT strictly greater than threshold (0.5f).
}

void test_is_temperature_rising_NegativeTemperaturesRising(void) {
    float prev_temp = 0.0f;
    float current_temp = 0.0f;
    float threshold = 0.5f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result); // Expected: Difference (1.0f) is strictly greater than threshold (0.5f), even with negative temperatures.
}

void test_is_temperature_rising_NegativeTemperaturesFalling(void) {
    float prev_temp = 0.0f;
    float current_temp = 0.0f;
    float threshold = 0.5f;
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result); // Expected: Difference (0.0f) is NOT strictly greater than threshold (0.5f).
}

// ====================================================================
// Main function to run all tests
// ====================================================================


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_MinRawValue);
    RUN_TEST(test_raw_to_celsius_MaxRawValue);
    RUN_TEST(test_raw_to_celsius_MidRawValue);
    RUN_TEST(test_raw_to_celsius_TypicalRoomTemperature);
    RUN_TEST(test_raw_to_celsius_NegativeOutputTemperature);
    RUN_TEST(test_celsius_to_fahrenheit_FreezingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_BoilingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_MinCelsiusEquivalence);
    RUN_TEST(test_celsius_to_fahrenheit_MaxCelsiusFromSensor);
    RUN_TEST(test_celsius_to_fahrenheit_TypicalRoomTemperature);
    RUN_TEST(test_is_temperature_rising_ClearlyRising);
    RUN_TEST(test_is_temperature_rising_RisingExactlyAtThreshold);
    RUN_TEST(test_is_temperature_rising_RisingBelowThreshold);
    RUN_TEST(test_is_temperature_rising_StableTemperature);
    RUN_TEST(test_is_temperature_rising_FallingTemperature);
    RUN_TEST(test_is_temperature_rising_NegativeTemperaturesRising);
    RUN_TEST(test_is_temperature_rising_NegativeTemperaturesFalling);

    return UNITY_END();
}