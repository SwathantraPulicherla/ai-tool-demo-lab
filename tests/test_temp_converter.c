/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h> // Required for bool type

// Source file under test - no direct include of .c, but need function declarations.
// Assuming temp_converter.h exists in the real project for these declarations.
// Since it's not provided, I'll declare them explicitly here for compilation.
// In a real project, this would be #include "temp_converter.h"
extern float raw_to_celsius(int raw_value);
extern float celsius_to_fahrenheit(float temp_c);
extern bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

// No external functions to stub, as per prompt.

void setUp(void) {
    // No stubs to reset as there are no external dependencies to stub.
    // This function remains for Unity framework structure.
}

void tearDown(void) {
    // No stubs to reset as there are no external dependencies to stub.
    // This function remains for Unity framework structure.
}

// region: raw_to_celsius tests
/**
 * @brief Tests raw_to_celsius with the minimum realistic raw value (0).
 *        Expects 0.0f Celsius based on the formula: (0/1023.0f)*165.0f - 40.0f.
 */
void test_raw_to_celsius_MinRawValue(void) {
    int raw_value = 0;
    float expected_celsius = 0.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // 0.01f tolerance for precise calculation
}

/**
 * @brief Tests raw_to_celsius with the maximum realistic raw value (1023).
 *        Expects 125.0f Celsius based on the formula: (1023/1023.0f)*165.0f - 40.0f.
 */
void test_raw_to_celsius_MaxRawValue(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // 0.01f tolerance for precise calculation
}

/**
 * @brief Tests raw_to_celsius with a mid-range realistic raw value (511).
 *        Expects approximately 42.5f Celsius based on the formula.
 */
void test_raw_to_celsius_MidRangeRawValue(void) {
    int raw_value = 511;
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // 0.01f tolerance for precise calculation
}

/**
 * @brief Tests raw_to_celsius with a common realistic raw value (200).
 *        Calculates expected Celsius based on the formula.
 */
void test_raw_to_celsius_CommonRawValue(void) {
    int raw_value = 200;
    float expected_celsius = (200.0f / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius); // 0.01f tolerance for precise calculation
}
// endregion: raw_to_celsius tests


// region: celsius_to_fahrenheit tests
/**
 * @brief Tests celsius_to_fahrenheit with the freezing point of water (0.0f C).
 *        Expects 32.0f F.
 */
void test_celsius_to_fahrenheit_FreezingPoint(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // 0.01f tolerance for temperature conversion
}

/**
 * @brief Tests celsius_to_fahrenheit with the boiling point of water (100.0f C).
 *        Expects 212.0f F.
 */
void test_celsius_to_fahrenheit_BoilingPoint(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // 0.01f tolerance for temperature conversion
}

/**
 * @brief Tests celsius_to_fahrenheit with the minimum valid Celsius temperature (0.0f C).
 *        Expects 0.0f F, as this is the point where both scales align.
 */
void test_celsius_to_fahrenheit_MinCelsius(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 0.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // 0.01f tolerance for temperature conversion
}

/**
 * @brief Tests celsius_to_fahrenheit with the maximum valid Celsius temperature (125.0f C).
 *        Expects 257.0f F.
 */
void test_celsius_to_fahrenheit_MaxCelsius(void) {
    float temp_c = 125.0f;
    float expected_fahrenheit = 257.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // 0.01f tolerance for temperature conversion
}

/**
 * @brief Tests celsius_to_fahrenheit with a nominal room temperature (25.0f C).
 *        Expects 77.0f F.
 */
void test_celsius_to_fahrenheit_NominalCelsius(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit); // 0.01f tolerance for temperature conversion
}
// endregion: celsius_to_fahrenheit tests


// region: is_temperature_rising tests
/**
 * @brief Tests is_temperature_rising when temperature is clearly rising above threshold.
 *        Expects true because current_temp - prev_temp (2.0f) > threshold (1.0f).
 */
void test_is_temperature_rising_TrueCondition(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: (22.0f - 20.0f) = 2.0f, which is > 1.0f
}

/**
 * @brief Tests is_temperature_rising when temperature rise is below the threshold.
 *        Expects false because current_temp - prev_temp (0.5f) <= threshold (1.0f).
 */
void test_is_temperature_rising_FalseCondition_BelowThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: (20.5f - 20.0f) = 0.5f, which is NOT > 1.0f
}

/**
 * @brief Tests is_temperature_rising when temperature rise is exactly equal to the threshold.
 *        Expects false because the condition uses '>', not '>='.
 */
void test_is_temperature_rising_FalseCondition_EqualToThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: (21.0f - 20.0f) = 1.0f, which is NOT > 1.0f
}

/**
 * @brief Tests is_temperature_rising when temperature is falling.
 *        Expects false because current_temp - prev_temp (0.0f) is not > threshold (1.0f).
 */
void test_is_temperature_rising_FalseCondition_FallingTemp(void) {
    float prev_temp = 22.0f;
    float current_temp = 20.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: (20.0f - 22.0f) = 0.0f, which is NOT > 1.0f
}

/**
 * @brief Tests is_temperature_rising with a zero threshold and rising temperature.
 *        Expects true because current_temp - prev_temp (0.1f) > threshold (0.0f).
 */
void test_is_temperature_rising_ZeroThreshold_Rising(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.1f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: (25.1f - 25.0f) = 0.1f, which is > 0.0f
}

/**
 * @brief Tests is_temperature_rising with a zero threshold and stable temperature.
 *        Expects false because current_temp - prev_temp (0.0f) is not > threshold (0.0f).
 */
void test_is_temperature_rising_ZeroThreshold_Stable(void) {
    float prev_temp = 25.0f;
    float current_temp = 25.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Expected: (25.0f - 25.0f) = 0.0f, which is NOT > 0.0f
}

/**
 * @brief Tests is_temperature_rising with a negative threshold and a slight rise.
 *        Expects true because (25.0f - 24.5f) = 0.5f which is > 0.0f.
 */
void test_is_temperature_rising_NegativeThreshold_SlightRise(void) {
    float prev_temp = 24.5f;
    float current_temp = 25.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // Expected: (25.0f - 24.5f) = 0.5f, which is > 0.0f
}
// endregion: is_temperature_rising tests


/**
 * @brief Main function for running Unity tests.
 */


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_MinRawValue);
    RUN_TEST(test_raw_to_celsius_MaxRawValue);
    RUN_TEST(test_raw_to_celsius_MidRangeRawValue);
    RUN_TEST(test_raw_to_celsius_CommonRawValue);
    RUN_TEST(test_celsius_to_fahrenheit_FreezingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_BoilingPoint);
    RUN_TEST(test_celsius_to_fahrenheit_MinCelsius);
    RUN_TEST(test_celsius_to_fahrenheit_MaxCelsius);
    RUN_TEST(test_celsius_to_fahrenheit_NominalCelsius);
    RUN_TEST(test_is_temperature_rising_TrueCondition);
    RUN_TEST(test_is_temperature_rising_FalseCondition_BelowThreshold);
    RUN_TEST(test_is_temperature_rising_FalseCondition_EqualToThreshold);
    RUN_TEST(test_is_temperature_rising_FalseCondition_FallingTemp);
    RUN_TEST(test_is_temperature_rising_ZeroThreshold_Rising);
    RUN_TEST(test_is_temperature_rising_ZeroThreshold_Stable);
    RUN_TEST(test_is_temperature_rising_NegativeThreshold_SlightRise);

    return UNITY_END();
}