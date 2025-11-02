/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // Required for memset in setUp/tearDown
#include <stdlib.h> // Required for rand() used in source under test

// Forward declarations for the functions under test (from temp_sensor.c)
// These declarations are necessary because the source file does not have a public header,
// and we are directly testing its internal functions.
int read_temperature_raw();
bool validate_temperature_range(float temp_c);
const char* check_temperature_status(float temp_c);
float get_temperature_celsius();

// --- External Function Stubs ---
// EXTERNAL FUNCTIONS TO STUB: raw_to_celsius
// Inferred signature: float raw_to_celsius(int raw)

typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_param;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_param = raw;
    return stub_raw_to_celsius.return_value;
}

// --- Test Setup and Teardown ---
void setUp(void) {
    // Reset all stub control structures to their default (zeroed) state
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

void tearDown(void) {
    // Reset all stub control structures again to ensure no state leakage for subsequent tests
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Test Cases for read_temperature_raw() ---

// Test that read_temperature_raw returns a value within the expected 00.0f range.
// As rand() cannot be stubbed per the rules, this test checks the range,
// not a specific deterministic value. This is the most realistic assertion possible.
void test_read_temperature_raw_returns_in_expected_range(void) {
    int raw_value;

    raw_value = read_temperature_raw();
    TEST_ASSERT_TRUE(raw_value >= 0);    // Expected: Raw value must be non-negative (due to % operator with positive modulus).
    TEST_ASSERT_TRUE(raw_value <= 1023); // Expected: Raw value must be less than 1024 (due to % 1024).

    raw_value = read_temperature_raw(); // Call again to check another random output within range
    TEST_ASSERT_TRUE(raw_value >= 0);    // Expected: Raw value must be non-negative.
    TEST_ASSERT_TRUE(raw_value <= 1023); // Expected: Raw value must be less than 1024.
}

// --- Test Cases for validate_temperature_range() ---

// Test with a normal temperature within the valid range (0.0f to 125.0f).
void test_validate_temperature_range_normal_valid(void) {
    float temp_c = 25.0f;
    bool result = validate_temperature_range(temp_c);
    TEST_ASSERT_TRUE(result); // Expected: 25.0f is between 0.0f and 125.0f (inclusive), so it should be valid.
}

// Test with the exact minimum valid temperature.
void test_validate_temperature_range_min_edge_valid(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    TEST_ASSERT_TRUE(result); // Expected: 0.0f is the lower inclusive bound, so it should be valid.
}

// Test with the exact maximum valid temperature.
void test_validate_temperature_range_max_edge_valid(void) {
    float temp_c = 125.0f;
    bool result = validate_temperature_range(temp_c);
    TEST_ASSERT_TRUE(result); // Expected: 125.0f is the upper inclusive bound, so it should be valid.
}

// Test with a temperature just below the minimum valid range.
void test_validate_temperature_range_below_min_invalid(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    TEST_ASSERT_FALSE(result); // Expected: 0.0f is less than 0.0f, so it should be invalid.
}

// Test with a temperature just above the maximum valid range.
void test_validate_temperature_range_above_max_invalid(void) {
    float temp_c = 125.1f;
    bool result = validate_temperature_range(temp_c);
    TEST_ASSERT_FALSE(result); // Expected: 125.1f is greater than 125.0f, so it should be invalid.
}

// --- Test Cases for check_temperature_status() ---

// Test a temperature causing a CRITICAL_HOT status (> 120.0f).
void test_check_temperature_status_critical_hot(void) {
    float temp_c = 120.1f; // Just above 120.0f threshold
    const char* status = check_temperature_status(temp_c);
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status); // Expected: 120.1f > 120.0f, returning CRITICAL_HOT string.
}

// Test a temperature at the exact CRITICAL_HOT boundary (120.0f). Should fall into WARNING_HOT.
void test_check_temperature_status_critical_hot_boundary(void) {
    float temp_c = 120.0f; // Exactly at 120.0f threshold
    const char* status = check_temperature_status(temp_c);
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status); // Expected: 120.0f is not > 120.0f, but > 85.0f, returning WARNING_HOT string.
}

// Test a temperature causing a WARNING_HOT status (> 85.0f and <= 120.0f).
void test_check_temperature_status_warning_hot(void) {
    float temp_c = 85.1f; // Just above 85.0f threshold
    const char* status = check_temperature_status(temp_c);
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status); // Expected: 85.1f > 85.0f (and <= 120.0f), returning WARNING_HOT string.
}

// Test a temperature at the exact WARNING_HOT boundary (85.0f). Should fall into NORMAL.
void test_check_temperature_status_warning_hot_boundary(void) {
    float temp_c = 85.0f; // Exactly at 85.0f threshold
    const char* status = check_temperature_status(temp_c);
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status); // Expected: 85.0f is not > 85.0f, but also not < 0.0f, returning NORMAL string.
}

// Test a temperature causing a WARNING_COLD status (< 0.0f).
void test_check_temperature_status_warning_cold(void) {
    float temp_c = 0.0f; // Just below 0.0f threshold
    const char* status = check_temperature_status(temp_c);
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status); // Expected: 0.0f < 0.0f, returning WARNING_COLD string.
}

// Test a temperature at the exact WARNING_COLD boundary (0.0f). Should fall into NORMAL.
void test_check_temperature_status_warning_cold_boundary(void) {
    float temp_c = 0.0f; // Exactly at 0.0f threshold
    const char* status = check_temperature_status(temp_c);
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status); // Expected: 0.0f is not < 0.0f, returning NORMAL string.
}

// Test a temperature causing a NORMAL status (mid-range, e.g., 25.0f).
void test_check_temperature_status_normal_mid_range(void) {
    float temp_c = 25.0f;
    const char* status = check_temperature_status(temp_c);
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status); // Expected: 25.0f is between 0.0f and 85.0f (inclusive), returning NORMAL string.
}

// Test a temperature causing a NORMAL status (at 0.0f).
void test_check_temperature_status_normal_at_zero(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status); // Expected: 0.0f is between 0.0f and 85.0f (inclusive), returning NORMAL string.
}

// --- Test Cases for get_temperature_celsius() ---

// Test `get_temperature_celsius` for a normal raw value conversion.
void test_get_temperature_celsius_normal_conversion(void) {
    // Configure the stub to return a specific celsius value.
    stub_raw_to_celsius.return_value = 25.5f;

    // Call the function under test.
    float result = get_temperature_celsius();

    // Assert that the external stub was called correctly.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);                 // Expected: raw_to_celsius should have been called.
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);      // Expected: raw_to_celsius should have been called exactly once.
    // Assert that the raw value passed to the stub by read_temperature_raw() is within expected limits (00.0f).
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);        // Expected: Raw parameter from read_temperature_raw is >= 0.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param <= 1023);     // Expected: Raw parameter from read_temperature_raw is <= 1023.
    // Assert the final result matches the stub's return value.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result); // Expected: The function should return the value provided by the raw_to_celsius stub.
}

// Test `get_temperature_celsius` for a raw value converting to a cold temperature.
void test_get_temperature_celsius_cold_conversion(void) {
    stub_raw_to_celsius.return_value = 0.0f; // Simulate a cold conversion

    float result = get_temperature_celsius();

    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param <= 1023);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result); // Expected: The function should return the value provided by the raw_to_celsius stub.
}

// Test `get_temperature_celsius` for a raw value converting to a hot temperature.
void test_get_temperature_celsius_hot_conversion(void) {
    stub_raw_to_celsius.return_value = 110.0f; // Simulate a hot conversion

    float result = get_temperature_celsius();

    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param <= 1023);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 110.0f, result); // Expected: The function should return the value provided by the raw_to_celsius stub.
}

// --- Main Unity Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_in_expected_range);
    RUN_TEST(test_validate_temperature_range_normal_valid);
    RUN_TEST(test_validate_temperature_range_min_edge_valid);
    RUN_TEST(test_validate_temperature_range_max_edge_valid);
    RUN_TEST(test_validate_temperature_range_below_min_invalid);
    RUN_TEST(test_validate_temperature_range_above_max_invalid);
    RUN_TEST(test_check_temperature_status_critical_hot);
    RUN_TEST(test_check_temperature_status_critical_hot_boundary);
    RUN_TEST(test_check_temperature_status_warning_hot);
    RUN_TEST(test_check_temperature_status_warning_hot_boundary);
    RUN_TEST(test_check_temperature_status_warning_cold);
    RUN_TEST(test_check_temperature_status_warning_cold_boundary);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_at_zero);
    RUN_TEST(test_get_temperature_celsius_normal_conversion);
    RUN_TEST(test_get_temperature_celsius_cold_conversion);
    RUN_TEST(test_get_temperature_celsius_hot_conversion);

    return UNITY_END();
}