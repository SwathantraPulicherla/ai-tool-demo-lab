/* test_temp_converter.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

extern int main(void);

/* No external dependencies to stub */

void setUp(void) {
}

void tearDown(void) {
}

void test_raw_to_celsius_normal_mid_range(void) {
    // Expected: raw value 512 should result in a Celsius temperature near 42.48°C
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 42.48f, raw_to_celsius(512));
}

void test_raw_to_celsius_min_edge_valid(void) {
    // Expected: raw value 0 should result in the minimum Celsius temperature of 0.0f°C
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, raw_to_celsius(0));
}

void test_raw_to_celsius_max_edge_valid(void) {
    // Expected: raw value 1023 should result in the maximum Celsius temperature of 125°C
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, raw_to_celsius(1023));
}

void test_raw_to_celsius_below_zero(void) {
    // Expected: raw value 200 results in a Celsius temperature below 0°C
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, raw_to_celsius(200));
}

void test_celsius_to_fahrenheit_normal_mid_range(void) {
    // Expected: 25°C should convert to 77°F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 77.0f, celsius_to_fahrenheit(25.0f));
}

void test_celsius_to_fahrenheit_min_edge_valid(void) {
    // Expected: 0.0f°C should convert to 0.0f°F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_max_edge_valid(void) {
    // Expected: 125°C should convert to 257°F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 257.0f, celsius_to_fahrenheit(125.0f));
}

void test_celsius_to_fahrenheit_zero(void) {
    // Expected: 0°C should convert to 32°F
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_is_temperature_rising_rising_true(void) {
    // Expected: current_temp is 1°C above prev_temp, threshold is 0.5, so it's rising
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 21.0f, 0.5f));
}

void test_is_temperature_rising_rising_false(void) {
    // Expected: current_temp is equal to prev_temp, threshold is 0.5, so it's not rising
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.0f, 0.5f));
}

void test_is_temperature_rising_falling_false(void) {
    // Expected: current_temp is below prev_temp, threshold is 0.5, so it's not rising
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 19.0f, 0.5f));
}

void test_is_temperature_rising_equal_threshold_false(void) {
    // Expected: current_temp is 0.5 above prev_temp, threshold is 0.5, so it's not rising
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.5f, 0.5f));
}




int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_normal_mid_range);
    RUN_TEST(test_raw_to_celsius_min_edge_valid);
    RUN_TEST(test_raw_to_celsius_max_edge_valid);
    RUN_TEST(test_raw_to_celsius_below_zero);
    RUN_TEST(test_celsius_to_fahrenheit_normal_mid_range);
    RUN_TEST(test_celsius_to_fahrenheit_min_edge_valid);
    RUN_TEST(test_celsius_to_fahrenheit_max_edge_valid);
    RUN_TEST(test_celsius_to_fahrenheit_zero);
    RUN_TEST(test_is_temperature_rising_rising_true);
    RUN_TEST(test_is_temperature_rising_rising_false);
    RUN_TEST(test_is_temperature_rising_falling_false);
    RUN_TEST(test_is_temperature_rising_equal_threshold_false);

    return UNITY_END();
}