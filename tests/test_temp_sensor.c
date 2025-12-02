/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h> // For rand()

// External function declarations for functions under test
// These are declared extern to call them from the test file.
extern int read_temperature_raw(void);
extern bool validate_temperature_range(float temp_c);
extern const char* check_temperature_status(float temp_c);
extern float get_temperature_celsius(void);

// === External Dependency Stubs ===

// Stub for raw_to_celsius
// Signature inferred from `float get_temperature_celsius() { return raw_to_celsius(raw); }`
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

// === Test Setup and Teardown ===

void setUp(void) {
    // Reset all stubs to their default state
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // Default return value for raw_to_celsius to prevent uninitialized behavior
    stub_raw_to_celsius.return_value = 0.0f;
}

void tearDown(void) {
    // Clean up or verify after each test, ensure complete reset
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// === Tests for read_temperature_raw() ===

void test_read_temperature_raw_returnsInRange(void) {
    int raw_temp = read_temperature_raw();
    // Expected: The raw temperature should be within the 0 to 1023 range
    TEST_ASSERT_INT_WITHIN(1024, 511, raw_temp); // Check if within range [0, 1023]
    TEST_ASSERT_TRUE(raw_temp >= 0); // Expected: Raw value is non-negative
    TEST_ASSERT_TRUE(raw_temp <= 1023); // Expected: Raw value is less than 1024 (exclusive for modulo)
}

void test_read_temperature_raw_multipleCallsInRange(void) {
    for (int i = 0; i < 100; i++) { // Call multiple times to increase confidence
        int raw_temp = read_temperature_raw();
        // Expected: Each call should return a value within the 0 to 1023 range
        TEST_ASSERT_TRUE(raw_temp >= 0);
        TEST_ASSERT_TRUE(raw_temp <= 1023);
    }
}

// === Tests for validate_temperature_range() ===

void test_validate_temperature_range_valid_min_edge(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 0.0f is exactly the lower valid boundary, so it should be true
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_max_edge(void) {
    float temp_c = 125.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 125.0f is exactly the upper valid boundary, so it should be true
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_nominal(void) {
    float temp_c = 25.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 25.0f is within the valid range [0.0f, 125.0f], so it should be true
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_below_min(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 0.0f is below the lower valid boundary, so it should be false
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_invalid_above_max(void) {
    float temp_c = 125.1f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 125.1f is above the upper valid boundary, so it should be false
    TEST_ASSERT_FALSE(result);
}

// === Tests for check_temperature_status() ===

void test_check_temperature_status_critical_hot_above_edge(void) {
    float temp_c = 120.1f;
    const char* status = check_temperature_status(temp_c);
    // Expected: > 120.0f should return "CRITICAL_HOT"
    TEST_ASSERT_EQUAL_STRING("CRITICAL_HOT", status);
}

void test_check_temperature_status_critical_hot_nominal(void) {
    float temp_c = 150.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 150.0f is significantly > 120.0f, should return "CRITICAL_HOT"
    TEST_ASSERT_EQUAL_STRING("CRITICAL_HOT", status);
}

void test_check_temperature_status_warm_above_edge(void) {
    float temp_c = 85.1f;
    const char* status = check_temperature_status(temp_c);
    // Expected: > 85.0f (but <= 120.0f) should return "WARM"
    TEST_ASSERT_EQUAL_STRING("WARM", status);
}

void test_check_temperature_status_warm_below_critical_edge(void) {
    float temp_c = 120.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 120.0f is not > 120.0f, but is > 85.0f, so it should be "WARM"
    TEST_ASSERT_EQUAL_STRING("WARM", status);
}

void test_check_temperature_status_cold_below_edge(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: < 0.0f should return "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

void test_check_temperature_status_cold_nominal(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 0.0f is significantly < 0.0f, should return "COLD"
    TEST_ASSERT_EQUAL_STRING("COLD", status);
}

void test_check_temperature_status_normal_low_edge(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 0.0f is not < 0.0f, and not > 85.0f, so it should be "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_high_edge(void) {
    float temp_c = 85.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 85.0f is not > 85.0f, and not < 0.0f, so it should be "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

void test_check_temperature_status_normal_nominal(void) {
    float temp_c = 25.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 25.0f falls within the "NORMAL" range [0.0f, 85.0f], so it should be "NORMAL"
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
}

// === Tests for get_temperature_celsius() ===

void test_get_temperature_celsius_returns_stubbed_value(void) {
    float expected_celsius = 25.5f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter passed to raw_to_celsius should be within its valid range
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param <= 1023);
    // Expected: The function should return the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_returns_different_stubbed_value(void) {
    float expected_celsius = 0.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw parameter passed to raw_to_celsius should be within its valid range
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_param <= 1023);
    // Expected: The function should return the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// === Main Test Runner ===



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returnsInRange);
    RUN_TEST(test_read_temperature_raw_multipleCallsInRange);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_valid_nominal);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_check_temperature_status_critical_hot_above_edge);
    RUN_TEST(test_check_temperature_status_critical_hot_nominal);
    RUN_TEST(test_check_temperature_status_warm_above_edge);
    RUN_TEST(test_check_temperature_status_warm_below_critical_edge);
    RUN_TEST(test_check_temperature_status_cold_below_edge);
    RUN_TEST(test_check_temperature_status_cold_nominal);
    RUN_TEST(test_check_temperature_status_normal_low_edge);
    RUN_TEST(test_check_temperature_status_normal_high_edge);
    RUN_TEST(test_check_temperature_status_normal_nominal);
    RUN_TEST(test_get_temperature_celsius_returns_stubbed_value);
    RUN_TEST(test_get_temperature_celsius_returns_different_stubbed_value);

    return UNITY_END();
}