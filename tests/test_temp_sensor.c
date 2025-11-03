/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // Required for memset in setUp/tearDown

// Source file functions (no extern needed as they will be linked directly)
// int read_temperature_raw();
// bool validate_temperature_range(float temp_c);
// const char* check_temperature_status(float temp_c);
// float get_temperature_celsius();

// --- External Function Stubs ---
// EXTERNAL FUNCTIONS TO STUB: raw_to_celsius
// Inferred signature: float raw_to_celsius(int raw_val)

typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_val;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius_control;

float raw_to_celsius(int raw_val) {
    stub_raw_to_celsius_control.was_called = true;
    stub_raw_to_celsius_control.call_count++;
    stub_raw_to_celsius_control.last_raw_val = raw_val;
    return stub_raw_to_celsius_control.return_value;
}

// --- Test Fixture Setup/Teardown ---
void setUp(void) {
    // Reset all stubs
    memset(&stub_raw_to_celsius_control, 0, sizeof(stub_raw_to_celsius_t));
}

void tearDown(void) {
    // Reset all stubs
    memset(&stub_raw_to_celsius_control, 0, sizeof(stub_raw_to_celsius_t));
}

// --- Source Functions (included for direct compilation in the test context) ---
// Note: In a real build system, these would be compiled separately and linked.
// For self-contained testing, if not building a library, including the .c is common.
// Assuming the source file is `src/temp_sensor.c` and we are testing it directly.
// We must not modify the original source code.
// The includes inside temp_sensor.c ([STRING REDACTED]) are handled by the original file.

// --- Tests for read_temperature_raw() ---
// This function uses rand(), which is non-deterministic and not listed for stubbing.
// We can only assert its output is within the expected range, as per rand() % 1024.
void test_read_temperature_raw_returns_within_range(void) {
    // Expected: The raw temperature should be between 0 and 1023 (inclusive)
    int raw_temp = read_temperature_raw();
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, raw_temp);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, raw_temp);
}

void test_read_temperature_raw_multiple_calls_within_range(void) {
    // Expected: Multiple calls should also return values within the 00.0f range
    for (int i = 0; i < 5; i++) {
        int raw_temp = read_temperature_raw();
        TEST_ASSERT_GREATER_OR_EQUAL_INT(0, raw_temp);
        TEST_ASSERT_LESS_OR_EQUAL_INT(1023, raw_temp);
    }
}

// --- Tests for validate_temperature_range() ---

void test_validate_temperature_range_valid_mid_range(void) {
    float temp_c = 25.0f;
    // Expected: 25.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_valid_min_edge(void) {
    float temp_c = 0.0f;
    // Expected: 0.0f is the minimum valid temperature
    TEST_ASSERT_TRUE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_invalid_below_min_edge(void) {
    float temp_c = 0.0f;
    // Expected: 0.0f is below the minimum valid temperature
    TEST_ASSERT_FALSE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_valid_max_edge(void) {
    float temp_c = 125.0f;
    // Expected: 125.0f is the maximum valid temperature
    TEST_ASSERT_TRUE(validate_temperature_range(temp_c));
}

void test_validate_temperature_range_invalid_above_max_edge(void) {
    float temp_c = 125.1f;
    // Expected: 125.1f is above the maximum valid temperature
    TEST_ASSERT_FALSE(validate_temperature_range(temp_c));
}

// --- Tests for check_temperature_status() ---

void test_check_temperature_status_critical_above_120(void) {
    float temp_c = 120.1f;
    // Expected: Temperature > 120.0f is CRITICAL
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", check_temperature_status(temp_c));
}

void test_check_temperature_status_critical_at_max_valid_temp(void) {
    float temp_c = 125.0f;
    // Expected: Temperature > 120.0f is CRITICAL, even at max valid physical temp
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", check_temperature_status(temp_c));
}

void test_check_temperature_status_hot_above_85_edge(void) {
    float temp_c = 85.1f;
    // Expected: Temperature > 85.0f (and not > 120.0f) is HOT
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", check_temperature_status(temp_c));
}

void test_check_temperature_status_hot_below_120_edge(void) {
    float temp_c = 120.0f;
    // Expected: Temperature <= 120.0f (and > 85.0f) is HOT
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", check_temperature_status(temp_c));
}

void test_check_temperature_status_normal_above_minus_10_edge(void) {
    float temp_c = 0.0f;
    // Expected: Temperature >= 0.0f (and not HOT/CRITICAL) is NORMAL
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", check_temperature_status(temp_c));
}

void test_check_temperature_status_normal_mid_range(void) {
    float temp_c = 25.0f;
    // Expected: 25.0f is in the normal range (0.0f to 85.0f inclusive)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", check_temperature_status(temp_c));
}

void test_check_temperature_status_normal_below_85_edge(void) {
    float temp_c = 85.0f;
    // Expected: Temperature <= 85.0f (and >= 0.0f) is NORMAL
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", check_temperature_status(temp_c));
}

void test_check_temperature_status_cold_below_minus_10(void) {
    float temp_c = 0.0f;
    // Expected: Temperature < 0.0f is COLD
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", check_temperature_status(temp_c));
}

void test_check_temperature_status_cold_at_min_valid_temp(void) {
    float temp_c = 0.0f;
    // Expected: Temperature < 0.0f is COLD, even at min valid physical temp
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", check_temperature_status(temp_c));
}

// --- Tests for get_temperature_celsius() ---

void test_get_temperature_celsius_normal_conversion(void) {
    // Configure stub for raw_to_celsius to return a known value
    float expected_celsius = 25.5f;
    stub_raw_to_celsius_control.return_value = expected_celsius;

    // Call the function under test
    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_control.call_count);
    // Expected: The return value should match the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);

    // Note: Due to rand() in read_temperature_raw() not being stubbed (as it's not
    // listed as an external dependency and read_temperature_raw is internal),
    // we cannot assert the specific 'raw_val' passed to raw_to_celsius_stub.
    // We only confirm that raw_to_celsius was called and its return propagated.
}

void test_get_temperature_celsius_another_conversion_value(void) {
    // Configure stub for raw_to_celsius for a different conversion
    float expected_celsius = 100.0f;
    stub_raw_to_celsius_control.return_value = expected_celsius;

    // Call the function under test
    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once again
    TEST_ASSERT_TRUE(stub_raw_to_celsius_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_control.call_count);
    // Expected: The return value should match the configured stub return
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_negative_conversion_value(void) {
    // Configure stub for raw_to_celsius for a negative conversion
    float expected_celsius = 0.0f;
    stub_raw_to_celsius_control.return_value = expected_celsius;

    // Call the function under test
    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius_control.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius_control.call_count);
    // Expected: The return value should match the configured stub return
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// --- Main Test Runner ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_within_range);
    RUN_TEST(test_read_temperature_raw_multiple_calls_within_range);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max_edge);
    RUN_TEST(test_check_temperature_status_critical_above_120);
    RUN_TEST(test_check_temperature_status_critical_at_max_valid_temp);
    RUN_TEST(test_check_temperature_status_hot_above_85_edge);
    RUN_TEST(test_check_temperature_status_hot_below_120_edge);
    RUN_TEST(test_check_temperature_status_normal_above_minus_10_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_below_85_edge);
    RUN_TEST(test_check_temperature_status_cold_below_minus_10);
    RUN_TEST(test_check_temperature_status_cold_at_min_valid_temp);
    RUN_TEST(test_get_temperature_celsius_normal_conversion);
    RUN_TEST(test_get_temperature_celsius_another_conversion_value);
    RUN_TEST(test_get_temperature_celsius_negative_conversion_value);

    return UNITY_END();
}