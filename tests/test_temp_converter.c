/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <string.h> // Not strictly needed, but common for memset in setUp/tearDown

// Include the source file directly for internal function access,
// assuming no conflicting declarations in a header.
// If temp_converter.h existed and declared these functions,
// we would include temp_converter.h instead and link against temp_converter.o
// but the prompt implies direct inclusion for internal testing.
// Since the functions are defined directly in the .c file,
// we can call them directly without an explicit header inclusion if
// the functions are not marked static and are compiled within the same context.
// However, the standard practice is to include the header.
// Given "[STRING REDACTED]" I will assume no header is provided and
// directly declare the functions for compilation purposes if needed.
// But since the functions are *defined* in the provided source block,
// and we are effectively testing that compilation unit,
// we don't need `extern` declarations; they are visible.

// --- Function Prototypes (from source code analysis) ---
// These are not extern, they are actual definitions from the source file.
// We declare them here to make them visible to the test runner, simulating
// including a header file or having them in the same compilation unit.
float raw_to_celsius(int raw_value);
float celsius_to_fahrenheit(float temp_c);
bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// --- EXTERNAL STUBS (None required as per prompt for this source) ---
// No external dependencies listed, so no stubs are needed.

// --- Test Setup and Teardown ---
void setUp(void) {
    // No stubs to reset, no global state to initialize for these simple functions
}

void tearDown(void) {
    // No stubs to reset, no global state to clean up
}

// --- Test Cases for raw_to_celsius ---

// Test raw_to_celsius with the minimum raw value (0)
void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f; // (0 / 1023.0f) * 165.0f - 40.0f = 0.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Expected: 0.0f when raw_value is 0.
}

// Test raw_to_celsius with the maximum raw value (1023)
void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Expected: 125.0f when raw_value is 1023.
}

// Test raw_to_celsius with a mid-range raw value (511)
void test_raw_to_celsius_mid_raw_value(void) {
    int raw_value = 511;
    float expected_celsius = (511 / 1023.0f) * 165.0f - 40.0f; // Approx 42.42f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Expected: Correct calculated value for 511.
}

// Test raw_to_celsius to get approximately 0 Celsius
void test_raw_to_celsius_zero_celsius_point(void) {
    // To get 0 C: (raw / 1023.0f) * 165.0f - 40.0f = 0
    // (raw / 1023.0f) * 165.0f = 40.0f
    // raw = (40.0f / 165.0f) * 1023.0f = 248.0f approx
    int raw_value = 248; // Closest integer raw value to achieve 0.0f C
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius); // Expected: Approx 0.0f C for raw_value 248.
}

// Test raw_to_celsius with a realistic high temperature value
void test_raw_to_celsius_high_realistic_value(void) {
    int raw_value = 800;
    float expected_celsius = (800 / 1023.0f) * 165.0f - 40.0f; // Approx 88.95f C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // Expected: Correct calculated value for 800.
}

// --- Test Cases for celsius_to_fahrenheit ---

// Test celsius_to_fahrenheit with freezing point (0 C)
void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0.0f * 9.0f / 5.0f) + 32.0f = 32.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Expected: 32.0f F for 0.0f C.
}

// Test celsius_to_fahrenheit with boiling point (100 C)
void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f = 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Expected: 212.0f F for 100.0f C.
}

// Test celsius_to_fahrenheit with negative value (0.0f C)
void test_celsius_to_fahrenheit_negative_value(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f; // (0.0f * 9.0f / 5.0f) + 32.0f = 0.0f + 32.0f = 0.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Expected: 0.0f F for 0.0f C.
}

// Test celsius_to_fahrenheit with a normal room temperature value (25 C)
void test_celsius_to_fahrenheit_normal_value(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f = 77.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Expected: 77.0f F for 25.0f C.
}

// Test celsius_to_fahrenheit with the maximum valid Celsius value (125 C)
void test_celsius_to_fahrenheit_max_value(void) {
    float temp_c = 125.0f;
    float expected_fahrenheit = 257.0f; // (125.0f * 9.0f / 5.0f) + 32.0f = 225.0f + 32.0f = 257.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // Expected: 257.0f F for 125.0f C.
}

// --- Test Cases for is_temperature_rising ---

// Test is_temperature_rising when temperature difference is clearly above threshold
void test_is_temperature_rising_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: true because (25.0 - 20.0) = 5.0, which is > 3.0.
}

// Test is_temperature_rising when temperature difference is exactly at threshold
void test_is_temperature_rising_equal_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 23.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: false because (23.0 - 20.0) = 3.0, which is NOT > 3.0.
}

// Test is_temperature_rising when temperature difference is below threshold
void test_is_temperature_rising_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: false because (22.0 - 20.0) = 2.0, which is NOT > 3.0.
}

// Test is_temperature_rising when temperature is decreasing
void test_is_temperature_rising_decreasing_temp(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 3.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: false because (20.0 - 25.0) = 0.0f, which is NOT > 3.0.
}

// Test is_temperature_rising with a zero threshold and rising temperature
void test_is_temperature_rising_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: true because (20.1 - 20.0) = 0.1, which is > 0.0.
}

// Test is_temperature_rising with a zero threshold and stable temperature
void test_is_temperature_rising_zero_threshold_stable(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: false because (20.0 - 20.0) = 0.0, which is NOT > 0.0.
}

// Test is_temperature_rising with a negative threshold and temperature rising
void test_is_temperature_rising_negative_threshold_rising(void) {
    float prev_temp = 10.0f;
    float current_temp = 12.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: true because (12.0 - 10.0) = 2.0, which is > 0.0f.
}

// Test is_temperature_rising with a negative threshold and temperature falling, but still above threshold
void test_is_temperature_rising_negative_threshold_falling_but_above(void) {
    float prev_temp = 10.0f;
    float current_temp = 8.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: true because (8.0 - 10.0) = 0.0f, which is > 0.0f.
}

// Test is_temperature_rising with a negative threshold and temperature falling below threshold
void test_is_temperature_rising_negative_threshold_falling_below(void) {
    float prev_temp = 10.0f;
    float current_temp = 5.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: false because (5.0 - 10.0) = 0.0f, which is NOT > 0.0f.
}


// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_zero_celsius_point);
    RUN_TEST(test_raw_to_celsius_high_realistic_value);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_value);
    RUN_TEST(test_celsius_to_fahrenheit_normal_value);
    RUN_TEST(test_celsius_to_fahrenheit_max_value);
    RUN_TEST(test_is_temperature_rising_above_threshold);
    RUN_TEST(test_is_temperature_rising_equal_threshold);
    RUN_TEST(test_is_temperature_rising_below_threshold);
    RUN_TEST(test_is_temperature_rising_decreasing_temp);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_stable);
    RUN_TEST(test_is_temperature_rising_negative_threshold_rising);
    RUN_TEST(test_is_temperature_rising_negative_threshold_falling_but_above);
    RUN_TEST(test_is_temperature_rising_negative_threshold_falling_below);

    return UNITY_END();
}