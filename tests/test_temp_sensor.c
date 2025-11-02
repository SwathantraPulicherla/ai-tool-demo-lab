/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset

// Forward declarations for functions under test
// These are included directly as they are in the same source file.
int read_temperature_raw();
bool validate_temperature_range(float temp_c);
const char* check_temperature_status(float temp_c);
float get_temperature_celsius();

// --- External Function Stubs ---

// Stub for raw_to_celsius (explicitly listed external dependency)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_val;
} raw_to_celsius_stub_t;
static raw_to_celsius_stub_t raw_to_celsius_stub;

// Definition of the stub function for raw_to_celsius
float raw_to_celsius(int raw_val) {
    raw_to_celsius_stub.was_called = true;
    raw_to_celsius_stub.call_count++;
    raw_to_celsius_stub.last_raw_val = raw_val;
    return raw_to_celsius_stub.return_value;
}

// Stub for rand() (dependency of read_temperature_raw, from stdlib.h, needs to be deterministic for tests)
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} rand_stub_t;
static rand_stub_t rand_stub;

// Definition of the stub function for rand()
int rand(void) {
    rand_stub.was_called = true;
    rand_stub.call_count++;
    return rand_stub.return_value;
}

// --- Constants for Redacted Strings (Inferred from common embedded patterns) ---
#define STATUS_CRITICAL_HOT "[STRING REDACTED]"
#define STATUS_WARNING_HOT "[STRING REDACTED]"
#define STATUS_CRITICAL_COLD "[STRING REDACTED]"
#define STATUS_NORMAL "[STRING REDACTED]"

// --- setUp and tearDown functions ---

void setUp(void) {
    // Reset all stub control structures to a known state before each test
    memset(&raw_to_celsius_stub, 0, sizeof(raw_to_celsius_stub));
    memset(&rand_stub, 0, sizeof(rand_stub));
}

void tearDown(void) {
    // Clean up or verify after each test, also reset stubs for safety
    memset(&raw_to_celsius_stub, 0, sizeof(raw_to_celsius_stub));
    memset(&rand_stub, 0, sizeof(rand_stub));
}

// --- Test Functions for read_temperature_raw() ---

void test_read_temperature_raw_returns_min_from_rand(void) {
    // Configure rand() stub to return the minimum possible value
    rand_stub.return_value = 0;
    int result = read_temperature_raw();
    // Expected: read_temperature_raw should return 0, matching the stubbed rand()
    TEST_ASSERT_EQUAL_INT(0, result);
    // Expected: rand() should have been called exactly once
    TEST_ASSERT_TRUE(rand_stub.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, rand_stub.call_count);
}

void test_read_temperature_raw_returns_max_from_rand(void) {
    // Configure rand() stub to return the maximum possible value for % 1024
    rand_stub.return_value = 1023; // rand() % 1024 would yield 1023
    int result = read_temperature_raw();
    // Expected: read_temperature_raw should return 1023, matching the stubbed rand()
    TEST_ASSERT_EQUAL_INT(1023, result);
    // Expected: rand() should have been called exactly once
    TEST_ASSERT_TRUE(rand_stub.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, rand_stub.call_count);
}

void test_read_temperature_raw_returns_mid_from_rand(void) {
    // Configure rand() stub to return a mid-range value
    rand_stub.return_value = 500;
    int result = read_temperature_raw();
    // Expected: read_temperature_raw should return 500, matching the stubbed rand()
    TEST_ASSERT_EQUAL_INT(500, result);
    // Expected: rand() should have been called exactly once
    TEST_ASSERT_TRUE(rand_stub.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, rand_stub.call_count);
}

// --- Test Functions for validate_temperature_range() ---

void test_validate_temperature_range_valid_min_edge(void) {
    // Test with the minimum valid temperature boundary
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is within range >= 0.0f and <= 125.0f
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_below_min(void) {
    // Test with a temperature just below the minimum valid boundary
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is outside range >= 0.0f and <= 125.0f
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_valid_max_edge(void) {
    // Test with the maximum valid temperature boundary
    bool result = validate_temperature_range(125.0f);
    // Expected: 125.0f is within range >= 0.0f and <= 125.0f
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_above_max(void) {
    // Test with a temperature just above the maximum valid boundary
    bool result = validate_temperature_range(125.1f);
    // Expected: 125.1f is outside range >= 0.0f and <= 125.0f
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_valid_nominal_mid_range(void) {
    // Test with a nominal temperature well within the valid range
    bool result = validate_temperature_range(25.0f);
    // Expected: 25.0f is within range >= 0.0f and <= 125.0f
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_cold_threshold(void) {
    // Test with a temperature near the cold status threshold, but still in valid range
    bool result = validate_temperature_range(0.0f);
    // Expected: 0.0f is within range >= 0.0f and <= 125.0f
    TEST_ASSERT_TRUE(result);
}

// --- Test Functions for check_temperature_status() ---

void test_check_temperature_status_critical_hot_above_threshold(void) {
    // Test a temperature that should trigger critical hot status
    const char* status = check_temperature_status(120.1f);
    // Expected: 120.1f is > 120.0f, thus CRITICAL_HOT_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_HOT, status);
}

void test_check_temperature_status_warning_hot_at_critical_boundary(void) {
    // Test a temperature at the exact boundary for critical hot, falls into warning hot
    const char* status = check_temperature_status(120.0f);
    // Expected: 120.0f is not > 120.0f, but is > 85.0f, thus WARNING_HOT_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_HOT, status);
}

void test_check_temperature_status_warning_hot_above_threshold(void) {
    // Test a temperature that should trigger warning hot status
    const char* status = check_temperature_status(85.1f);
    // Expected: 85.1f is not > 120.0f, but is > 85.0f, thus WARNING_HOT_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_HOT, status);
}

void test_check_temperature_status_normal_at_hot_boundary(void) {
    // Test a temperature at the exact boundary for warning hot, falls into normal
    const char* status = check_temperature_status(85.0f);
    // Expected: 85.0f is not > 120.0f and not > 85.0f, thus NORMAL_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status);
}

void test_check_temperature_status_critical_cold_below_threshold(void) {
    // Test a temperature that should trigger critical cold status
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is < 0.0f, thus CRITICAL_COLD_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_COLD, status);
}

void test_check_temperature_status_normal_at_cold_boundary(void) {
    // Test a temperature at the exact boundary for critical cold, falls into normal
    const char* status = check_temperature_status(0.0f);
    // Expected: 0.0f is not > 120.0f, not > 85.0f, and not < 0.0f, thus NORMAL_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status);
}

void test_check_temperature_status_normal_mid_range(void) {
    // Test a nominal temperature well within the normal range
    const char* status = check_temperature_status(25.0f);
    // Expected: 25.0f falls into the final else block, thus NORMAL_TEMP
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status);
}

// --- Test Functions for get_temperature_celsius() ---

void test_get_temperature_celsius_normal_operation(void) {
    // Configure stubs for a nominal temperature reading
    rand_stub.return_value = 500; // Simulate raw sensor value
    raw_to_celsius_stub.return_value = 25.0f; // Simulate conversion to Celsius

    float result = get_temperature_celsius();

    // Expected: get_temperature_celsius returns the value from raw_to_celsius stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result);
    // Expected: read_temperature_raw (via rand stub) was called
    TEST_ASSERT_TRUE(rand_stub.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, rand_stub.call_count);
    // Expected: raw_to_celsius was called with the value returned by read_temperature_raw
    TEST_ASSERT_TRUE(raw_to_celsius_stub.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, raw_to_celsius_stub.call_count);
    TEST_ASSERT_EQUAL_INT(500, raw_to_celsius_stub.last_raw_val);
}

void test_get_temperature_celsius_edge_min_raw_value(void) {
    // Configure stubs for minimum raw value resulting in minimum valid Celsius
    rand_stub.return_value = 0; // Simulate min raw sensor value
    raw_to_celsius_stub.return_value = 0.0f; // Simulate conversion to min Celsius

    float result = get_temperature_celsius();

    // Expected: get_temperature_celsius returns the value from raw_to_celsius stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
    // Expected: raw_to_celsius was called with the minimum raw value
    TEST_ASSERT_EQUAL_INT(0, raw_to_celsius_stub.last_raw_val);
}

void test_get_temperature_celsius_edge_max_raw_value(void) {
    // Configure stubs for maximum raw value resulting in maximum valid Celsius
    rand_stub.return_value = 1023; // Simulate max raw sensor value
    raw_to_celsius_stub.return_value = 125.0f; // Simulate conversion to max Celsius

    float result = get_temperature_celsius();

    // Expected: get_temperature_celsius returns the value from raw_to_celsius stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result);
    // Expected: raw_to_celsius was called with the maximum raw value
    TEST_ASSERT_EQUAL_INT(1023, raw_to_celsius_stub.last_raw_val);
}

void test_get_temperature_celsius_critical_cold_scenario(void) {
    // Configure stubs to simulate a critical cold scenario
    rand_stub.return_value = 100; // Arbitrary raw value leading to cold
    raw_to_celsius_stub.return_value = 0.0f; // Simulate conversion to critical cold Celsius

    float result = get_temperature_celsius();

    // Expected: get_temperature_celsius returns the critical cold value
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
    // Expected: raw_to_celsius was called with the specified raw value
    TEST_ASSERT_EQUAL_INT(100, raw_to_celsius_stub.last_raw_val);
}

// --- Main function to run all tests ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_min_from_rand);
    RUN_TEST(test_read_temperature_raw_returns_max_from_rand);
    RUN_TEST(test_read_temperature_raw_returns_mid_from_rand);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_validate_temperature_range_valid_nominal_mid_range);
    RUN_TEST(test_validate_temperature_range_valid_cold_threshold);
    RUN_TEST(test_check_temperature_status_critical_hot_above_threshold);
    RUN_TEST(test_check_temperature_status_warning_hot_at_critical_boundary);
    RUN_TEST(test_check_temperature_status_warning_hot_above_threshold);
    RUN_TEST(test_check_temperature_status_normal_at_hot_boundary);
    RUN_TEST(test_check_temperature_status_critical_cold_below_threshold);
    RUN_TEST(test_check_temperature_status_normal_at_cold_boundary);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_get_temperature_celsius_normal_operation);
    RUN_TEST(test_get_temperature_celsius_edge_min_raw_value);
    RUN_TEST(test_get_temperature_celsius_edge_max_raw_value);
    RUN_TEST(test_get_temperature_celsius_critical_cold_scenario);

    return UNITY_END();
}