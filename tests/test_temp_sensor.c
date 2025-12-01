/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset
#include <stdlib.h> // For rand() in the source file, not stubbed here

// --- Forward declarations for functions in temp_sensor.c (since no temp_sensor.h is provided in source) ---
// Note: These functions are defined in the source file and are not stubbed; they are called directly.
int read_temperature_raw(void);
bool validate_temperature_range(float temp_c);
const char* check_temperature_status(float temp_c);
float get_temperature_celsius(void);

// --- Stub for external dependency: raw_to_celsius ---
// Infer signature: float raw_to_celsius(int raw)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_param;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

// Stub implementation for raw_to_celsius
float raw_to_celsius(int raw) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_param = raw;
    return stub_raw_to_celsius.return_value;
}

// --- Helper strings for check_temperature_status (inferring from context of [STRING REDACTED]) ---
// These are assumed string literals the `check_temperature_status` function returns.
// In a real scenario, these would be `#define` or `const char*` in a header file.
// For testing purposes, we define them here to compare against.
static const char* const STATUS_CRITICAL_HIGH_TEMP = "CRITICAL_HIGH_TEMP";
static const char* const STATUS_WARNING_HIGH_TEMP  = "WARNING_HIGH_TEMP";
static const char* const STATUS_WARNING_LOW_TEMP   = "WARNING_LOW_TEMP";
static const char* const STATUS_NORMAL_TEMP        = "NORMAL_TEMP";

// --- Setup and Teardown functions ---
void setUp(void) {
    // Reset all stubs to their default state before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // For read_temperature_raw which uses rand(), we cannot directly stub rand() as it's stdlib.h.
    // If a deterministic rand() was needed, it would require linker trickery or a custom build configuration.
    // For these tests, we will just ensure the raw value is within its expected range (00.0f).
}

void tearDown(void) {
    // Reset all stubs after each test (redundant with setUp, but good practice for safety)
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Test functions for read_temperature_raw ---

// Test that read_temperature_raw returns a value within the expected range (00.0f)
void test_read_temperature_raw_returns_within_valid_range(void) {
    int raw = read_temperature_raw();
    // Expected: Raw value should be between 0 and 1023 (inclusive) from rand() % 1024
    TEST_ASSERT_TRUE(raw >= 0);
    // Expected: Raw value should be between 0 and 1023 (inclusive) from rand() % 1024
    TEST_ASSERT_TRUE(raw <= 1023);

    // Call it a few more times to increase confidence in the range check
    raw = read_temperature_raw();
    TEST_ASSERT_TRUE(raw >= 0);
    TEST_ASSERT_TRUE(raw <= 1023);

    raw = read_temperature_raw();
    TEST_ASSERT_TRUE(raw >= 0);
    TEST_ASSERT_TRUE(raw <= 1023);
}

// --- Test functions for validate_temperature_range ---

// Test minimum valid temperature for range validation
void test_validate_temperature_range_min_valid(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

// Test temperature just below the minimum valid range
void test_validate_temperature_range_min_invalid_below(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is outside the valid range [0.0f, 125.0f]
    TEST_ASSERT_FALSE(result);
}

// Test maximum valid temperature for range validation
void test_validate_temperature_range_max_valid(void) {
    float temp = 125.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

// Test temperature just above the maximum valid range
void test_validate_temperature_range_max_invalid_above(void) {
    float temp = 125.1f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.1f is outside the valid range [0.0f, 125.0f]
    TEST_ASSERT_FALSE(result);
}

// Test a nominal temperature within the valid range
void test_validate_temperature_range_nominal_valid(void) {
    float temp = 25.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 25.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

// Test zero temperature within the valid range
void test_validate_temperature_range_nominal_zero(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

// --- Test functions for check_temperature_status ---

// Test temperature in the critical high range (> 120.0f)
void test_check_temperature_status_critical_high(void) {
    float temp = 120.1f;
    const char* status = check_temperature_status(temp);
    // Expected: 120.1f is > 120.0f, so CRITICAL_HIGH_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_HIGH_TEMP, status);
}

// Test temperature at the edge of critical high (120.0f)
void test_check_temperature_status_critical_high_edge(void) {
    float temp = 120.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 120.0f is not > 120.0f, but it is > 85.0f, so WARNING_HIGH_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_HIGH_TEMP, status);
}

// Test temperature just above the warning high range (> 85.0f)
void test_check_temperature_status_warning_high_above_edge(void) {
    float temp = 85.1f;
    const char* status = check_temperature_status(temp);
    // Expected: 85.1f is not > 120.0f, but it is > 85.0f, so WARNING_HIGH_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_HIGH_TEMP, status);
}

// Test temperature at the edge of warning high (85.0f)
void test_check_temperature_status_warning_high_below_edge(void) {
    float temp = 85.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 85.0f is not > 120.0f and not > 85.0f, and not < 0.0f, so NORMAL_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL_TEMP, status);
}

// Test temperature just below the warning low range (< 0.0f)
void test_check_temperature_status_warning_low_below_edge(void) {
    float temp = 0.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is < 0.0f, so WARNING_LOW_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_LOW_TEMP, status);
}

// Test temperature at the edge of warning low (0.0f)
void test_check_temperature_status_warning_low_above_edge(void) {
    float temp = 0.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is not > 120.0f, not > 85.0f, and not < 0.0f, so NORMAL_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL_TEMP, status);
}

// Test a nominal temperature in the normal range
void test_check_temperature_status_normal_mid_range(void) {
    float temp = 25.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 25.0f falls into the 'else' branch, so NORMAL_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL_TEMP, status);
}

// Test zero temperature in the normal range
void test_check_temperature_status_normal_zero(void) {
    float temp = 0.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f falls into the 'else' branch, so NORMAL_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL_TEMP, status);
}

// Test temperature just below the warning high threshold but still normal
void test_check_temperature_status_normal_upper_edge(void) {
    float temp = 84.9f;
    const char* status = check_temperature_status(temp);
    // Expected: 84.9f falls into the 'else' branch, so NORMAL_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL_TEMP, status);
}

// --- Test functions for get_temperature_celsius ---

// Test a normal temperature conversion flow
void test_get_temperature_celsius_normal_conversion(void) {
    // Configure the stub to return a specific Celsius value
    stub_raw_to_celsius.return_value = 25.5f;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter passed to stub_raw_to_celsius should be in the 00.0f range
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param <= 1023);
    // Expected: The function should return the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result);
}

// Test another temperature conversion, e.g., a cold value
void test_get_temperature_celsius_cold_conversion(void) {
    // Configure the stub to return a cold Celsius value
    stub_raw_to_celsius.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter passed to stub_raw_to_celsius should be in the 00.0f range
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param <= 1023);
    // Expected: The function should return the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

// Test a boundary high temperature conversion
void test_get_temperature_celsius_boundary_high_conversion(void) {
    // Configure the stub to return a high Celsius value
    stub_raw_to_celsius.return_value = 120.5f;

    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter passed to stub_raw_to_celsius should be in the 00.0f range
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param <= 1023);
    // Expected: The function should return the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 120.5f, result);
}


// --- Main function to run all tests ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_within_valid_range);
    RUN_TEST(test_validate_temperature_range_min_valid);
    RUN_TEST(test_validate_temperature_range_min_invalid_below);
    RUN_TEST(test_validate_temperature_range_max_valid);
    RUN_TEST(test_validate_temperature_range_max_invalid_above);
    RUN_TEST(test_validate_temperature_range_nominal_valid);
    RUN_TEST(test_validate_temperature_range_nominal_zero);
    RUN_TEST(test_check_temperature_status_critical_high);
    RUN_TEST(test_check_temperature_status_critical_high_edge);
    RUN_TEST(test_check_temperature_status_warning_high_above_edge);
    RUN_TEST(test_check_temperature_status_warning_high_below_edge);
    RUN_TEST(test_check_temperature_status_warning_low_below_edge);
    RUN_TEST(test_check_temperature_status_warning_low_above_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_zero);
    RUN_TEST(test_check_temperature_status_normal_upper_edge);
    RUN_TEST(test_get_temperature_celsius_normal_conversion);
    RUN_TEST(test_get_temperature_celsius_cold_conversion);
    RUN_TEST(test_get_temperature_celsius_boundary_high_conversion);

    return UNITY_END();
}