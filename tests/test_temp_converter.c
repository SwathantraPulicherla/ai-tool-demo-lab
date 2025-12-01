/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // Required for 'bool' type used in source
#include <string.h>  // Not strictly needed but good practice for memset if stubs were present

// Forward declarations for the functions under test, as if they were in a header.
// This allows the test file to compile without including the actual .c file directly
// or requiring a specific .h file if one isn't explicitly provided/referenced.
// In a real project, we'd #include "temp_converter.h".
// Given the prompt's constraint "ONLY use existing headers from source" and the source having "[STRING REDACTED]",
// and no `temp_converter.h` was provided, explicitly declaring them here mirrors the internal analysis
// of their signatures.
extern float raw_to_celsius(int raw_value);
extern float celsius_to_fahrenheit(float temp_c);
extern bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions to stub based on the prompt.

void setUp(void) {
    // No global state or stubs to initialize for this module.
}

void tearDown(void) {
    // No global state or stubs to clean up for this module.
}

// ====================================================================================================
// Tests for raw_to_celsius(int raw_value)
// Formula: (raw_value / 1023.0f) * 165.0f - 40.0f
// Expected range for raw_value: 0 to 1023 (10-bit ADC)
// Corresponding Celsius range: 0.0f to 125.0f
// ====================================================================================================

void test_raw_to_celsius_MinRawValue(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // Expected: (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_MaxRawValue(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // Expected: (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_MidRangeRawValue(void) {
    int raw_value = 511; // Approximately mid-point of a 10-bit ADC range
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f; // Expected: Accurate calculation based on formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_LowPositiveRawValue(void) {
    int raw_value = 255; // Arbitrary value in lower range
    float expected_celsius = (255.0f / 1023.0f) * 165.0f - 40.0f; // Expected: Accurate calculation based on formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_HighPositiveRawValue(void) {
    int raw_value = 767; // Arbitrary value in upper range
    float expected_celsius = (767.0f / 1023.0f) * 165.0f - 40.0f; // Expected: Accurate calculation based on formula
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// ====================================================================================================
// Tests for celsius_to_fahrenheit(float temp_c)
// Formula: (temp_c * 9.0f / 5.0f) + 32.0f
// Typical Celsius range for sensor: 0.0f to 125.0f
// ====================================================================================================

void test_celsius_to_fahrenheit_FreezingPoint(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_BoilingPoint(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // Expected: (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_Negative40C(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // Expected: (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f (the only point where C == F)
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_RoomTemperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // Expected: (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_MaxSensorTemperature(void) {
    float temp_c = 125.0f; // Max temperature from raw_to_celsius conversion
    float expected_fahrenheit = (125.0f * 9.0f / 5.0f) + 32.0f; // Expected: 225.0f + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_fahrenheit, actual_fahrenheit);
}

// ====================================================================================================
// Tests for is_temperature_rising(float prev_temp, float current_temp, float threshold)
// Logic: (current_temp - prev_temp) > threshold
// ====================================================================================================

void test_is_temperature_rising_IsRising(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 2.0f;
    bool expected_result = true; // Expected: (25.0f - 20.0f) > 2.0f -> 5.0f > 2.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_JustRising(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.1f;
    float threshold = 2.0f;
    bool expected_result = true; // Expected: (22.1f - 20.0f) > 2.0f -> 2.1f > 2.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_NotRising_BelowThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 2.0f;
    bool expected_result = false; // Expected: (21.0f - 20.0f) > 2.0f -> 1.0f > 2.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_NotRising_AtThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    bool expected_result = false; // Expected: (22.0f - 20.0f) > 2.0f -> 2.0f > 2.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_TemperatureFalling(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 2.0f;
    bool expected_result = false; // Expected: (20.0f - 25.0f) > 2.0f -> 0.0f > 2.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_TemperatureConstant(void) {
    float prev_temp = 22.0f;
    float current_temp = 22.0f;
    float threshold = 1.0f;
    bool expected_result = false; // Expected: (22.0f - 22.0f) > 1.0f -> 0.0f > 1.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}

void test_is_temperature_rising_NegativeThreshold_Rising(void) {
    float prev_temp = 10.0f;
    float current_temp = 10.5f;
    float threshold = 0.0f;
    bool expected_result = true; // Expected: (10.5f - 10.0f) > 0.0f -> 0.5f > 0.0f is true
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(actual_result);
}

void test_is_temperature_rising_NegativeThreshold_Falling(void) {
    float prev_temp = 10.0f;
    float current_temp = 9.0f;
    float threshold = 0.0f;
    bool expected_result = false; // Expected: (9.0f - 10.0f) > 0.0f -> 0.0f > 0.0f is false
    bool actual_result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(actual_result);
}




int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_MinRawValue);
    RUN_TEST(test_raw_to_celsius_MaxRawValue);
    RUN_TEST(test_raw_to_celsius_MidRangeRawValue);
    RUN_TEST(test_raw_to_celsius_LowPositiveRawValue);
    RUN_TEST(test_raw_to_celsius_HighPositiveRawValue);
    RUN_TEST(test_celsius_to_fahrenheit_FreezingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_BoilingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_Negative40C);
    RUN_TEST(test_celsius_to_fahrenheit_RoomTemperature);
    RUN_TEST(test_celsius_to_fahrenheit_MaxSensorTemperature);
    RUN_TEST(test_is_temperature_rising_IsRising);
    RUN_TEST(test_is_temperature_rising_JustRising);
    RUN_TEST(test_is_temperature_rising_NotRising_BelowThreshold);
    RUN_TEST(test_is_temperature_rising_NotRising_AtThreshold);
    RUN_TEST(test_is_temperature_rising_TemperatureFalling);
    RUN_TEST(test_is_temperature_rising_TemperatureConstant);
    RUN_TEST(test_is_temperature_rising_NegativeThreshold_Rising);
    RUN_TEST(test_is_temperature_rising_NegativeThreshold_Falling);

    return UNITY_END();
}