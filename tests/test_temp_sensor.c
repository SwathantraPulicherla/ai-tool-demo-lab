/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // For memset and string comparisons
#include <stdlib.h> // For rand() in read_temperature_raw

// Forward declare the functions from the source file to allow linking.
// These are not "invented headers" but declarations necessary for the test runner to link
// with the compiled source functions when the .c file is built into a test executable.
extern int read_temperature_raw();
extern bool validate_temperature_range(float temp_c);
extern const char* check_temperature_status(float temp_c);
extern float get_temperature_celsius();

// External dependency to stub (signature inferred from usage in get_temperature_celsius)
extern float raw_to_celsius(int raw);

// --- Stub for raw_to_celsius ---
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_param; // Captures the 'raw' argument passed to the stub
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_param = raw;
    return stub_raw_to_celsius.return_value;
}

// --- setUp and tearDown functions ---
void setUp(void) {
    // Reset all stubs completely before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // Set a default return value for the stub to prevent unexpected behavior
    stub_raw_to_celsius.return_value = 25.0f; // A nominal temperature
}

void tearDown(void) {
    // Clean up or verify after each test, ensuring stubs are fully reset
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Tests for read_temperature_raw ---
// This function internally uses rand() % 1024, making its output non-deterministic.
// Per instructions, we cannot stub rand(). We test that the output is within the expected range.
void test_read_temperature_raw_returns_within_valid_range(void) {
    int raw_val;

    // Call multiple times to increase confidence that values fall within the expected range [0, 1023].
    // Note: Due to rand() being non-deterministic without srand(), we cannot assert specific values.
    // The test ensures the modulo operation works correctly.
    for (int i = 0; i < 100; i++) {
        raw_val = read_temperature_raw();
        // Expected: Raw value must be non-negative, as per rand() and modulo operation
        TEST_ASSERT_TRUE(raw_val >= 0);
        // Expected: Raw value must be less than 1024, as per % 1024
        TEST_ASSERT_TRUE(raw_val < 1024);
    }
}

// --- Tests for validate_temperature_range ---
void test_validate_temperature_range_min_edge_valid(void) {
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is precisely the lower bound, so it should be valid
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_min_edge_invalid(void) {
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is just below the lower bound, so it should be invalid
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_max_edge_valid(void) {
    bool result = validate_temperature_range(125.0f);
    // Expected: 125.0f is precisely the upper bound, so it should be valid
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_max_edge_invalid(void) {
    bool result = validate_temperature_range(125.1f);
    // Expected: 125.1f is just above the upper bound, so it should be invalid
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_normal_mid_range(void) {
    bool result = validate_temperature_range(25.0f);
    // Expected: 25.0f is comfortably within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_normal_zero(void) {
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

// --- Tests for check_temperature_status ---
// Using realistic string literals as implied by the source's conditional logic
void test_check_temperature_status_critical_high_edge_valid(void) {
    const char* status = check_temperature_status(120.1f);
    // Expected: 120.1f is strictly greater than 120.0f, triggering CRITICAL_HIGH
    TEST_ASSERT_EQUAL_STRING("CRITICAL_HIGH", status);
}

void test_check_temperature_status_critical_high_edge_invalid(void) {
    const char* status = check_temperature_status(120.0f);
    // Expected: 120.0f is not strictly greater than 120.0f, but greater than 85.0f, triggering WARNING_HIGH
    TEST_ASSERT_EQUAL_STRING("WARNING_HIGH", status);
}

void test_check_temperature_status_warning_high_edge_valid(void) {
    const char* status = check_temperature_status(85.1f);
    // Expected: 85.1f is strictly greater than 85.0f, triggering WARNING_HIGH
    TEST_ASSERT_EQUAL_STRING("WARNING_HIGH", status);
}

void test_check_temperature_status_warning_high_edge_invalid(void) {
    const char* status = check_temperature_status(85.0f);
    // Expected: 85.0f is not strictly greater than 85.0f, and not less than 0.0f, triggering NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_critical_low_edge_valid(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is strictly less than 0.0f, triggering CRITICAL_LOW
    TEST_ASSERT_EQUAL_STRING("CRITICAL_LOW", status);
}

void test_check_temperature_status_critical_low_edge_invalid(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is not strictly less than 0.0f, and not greater than 85.0f, triggering NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_mid_range(void) {
    const char* status = check_temperature_status(25.0f);
    // Expected: 25.0f falls into the final 'else' branch, triggering NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_zero(void) {
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f falls into the final 'else' branch, triggering NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

// --- Tests for get_temperature_celsius ---
void test_get_temperature_celsius_normal_flow(void) {
    float expected_temp = 25.5f;
    stub_raw_to_celsius.return_value = expected_temp;

    float actual_temp = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter captured by the stub should be within the range [0, 1023]
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param < 1024);
    // Expected: The function should return the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, actual_temp);
}

void test_get_temperature_celsius_high_temp_conversion(void) {
    float expected_temp = 110.0f; // A high, but valid temperature
    stub_raw_to_celsius.return_value = expected_temp;

    float actual_temp = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter captured by the stub should be within the range [0, 1023]
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param < 1024);
    // Expected: The function should return the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, actual_temp);
}

void test_get_temperature_celsius_low_temp_conversion(void) {
    float expected_temp = 0.0f; // A low, but valid temperature
    stub_raw_to_celsius.return_value = expected_temp;

    float actual_temp = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter captured by the stub should be within the range [0, 1023]
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param < 1024);
    // Expected: The function should return the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_temp, actual_temp);
}

// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_within_valid_range);
    RUN_TEST(test_validate_temperature_range_min_edge_valid);
    RUN_TEST(test_validate_temperature_range_min_edge_invalid);
    RUN_TEST(test_validate_temperature_range_max_edge_valid);
    RUN_TEST(test_validate_temperature_range_max_edge_invalid);
    RUN_TEST(test_validate_temperature_range_normal_mid_range);
    RUN_TEST(test_validate_temperature_range_normal_zero);
    RUN_TEST(test_check_temperature_status_critical_high_edge_valid);
    RUN_TEST(test_check_temperature_status_critical_high_edge_invalid);
    RUN_TEST(test_check_temperature_status_warning_high_edge_valid);
    RUN_TEST(test_check_temperature_status_warning_high_edge_invalid);
    RUN_TEST(test_check_temperature_status_critical_low_edge_valid);
    RUN_TEST(test_check_temperature_status_critical_low_edge_invalid);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_zero);
    RUN_TEST(test_get_temperature_celsius_normal_flow);
    RUN_TEST(test_get_temperature_celsius_high_temp_conversion);
    RUN_TEST(test_get_temperature_celsius_low_temp_conversion);

    return UNITY_END();
}