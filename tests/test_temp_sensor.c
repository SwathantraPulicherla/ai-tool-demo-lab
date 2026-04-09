/* test_temp_sensor.c – Auto-generated Expert Unity Tests */

#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // Required for memset and TEST_ASSERT_EQUAL_STRING
#include <stdlib.h> // Required for srand, rand (to make raw temp tests more robust)

// --- Source Function Prototypes (mimicking what would be in temp_sensor.h) ---
// These declarations are necessary because we are not including "temp_sensor.h"
// and to satisfy the compiler when linking with temp_sensor.c.
// They match the exact signatures from the source file.
extern int read_temperature_raw(void);
extern bool validate_temperature_range(float temp_c);
extern const char* check_temperature_status(float temp_c);
extern float get_temperature_celsius(void);

// --- External Function Stubs ---
// Signature inferred from get_temperature_celsius calling raw_to_celsius(raw)
// Assumes raw_to_celsius takes an int and returns a float.
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_val;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw_val) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_val = raw_val;
    return stub_raw_to_celsius.return_value;
}

// --- Placeholder for [STRING REDACTED] ---
// These constants define the expected string outputs based on the source logic.
const char* CRITICAL_HOT_STATUS = "CRITICAL_HOT";
const char* WARNING_HOT_STATUS = "WARNING_HOT";
const char* WARNING_COLD_STATUS = "WARNING_COLD";
const char* NORMAL_STATUS = "NORMAL";

// --- SetUp and TearDown Functions ---
void setUp(void) {
    // Reset all stubs before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // Seed rand for read_temperature_raw tests, though its output is still non-deterministic
    // within the test itself, we can only verify its range.
    srand(1); 
}

void tearDown(void) {
    // Reset all stubs after each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Test Functions for read_temperature_raw() ---
void test_read_temperature_raw_returns_within_valid_range(void) {
    int raw_val;
    // Expected: raw value should be within the 0 to 1023 range (from rand() % 1024)
    for (int i = 0; i < 5; i++) { // Test multiple calls to ensure consistent range
        raw_val = read_temperature_raw();
        // Expected: Raw value is non-negative
        TEST_ASSERT_GREATER_OR_EQUAL_INT(0, raw_val);
        // Expected: Raw value is less than 1024
        TEST_ASSERT_LESS_OR_EQUAL_INT(1023, raw_val);
    }
}

// --- Test Functions for validate_temperature_range() ---
void test_validate_temperature_range_valid_min_edge(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 0.0f is exactly on the lower valid boundary, so it should be valid
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_below_min_edge(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 0.0f is below the lower valid boundary, so it should be invalid
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_valid_max_edge(void) {
    float temp_c = 125.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 125.0f is exactly on the upper valid boundary, so it should be valid
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_invalid_above_max_edge(void) {
    float temp_c = 125.1f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 125.1f is above the upper valid boundary, so it should be invalid
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_valid_nominal(void) {
    float temp_c = 25.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 25.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_valid_zero(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 0.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

// --- Test Functions for check_temperature_status() ---
void test_check_temperature_status_critical_hot_above_edge(void) {
    float temp_c = 120.1f;
    const char* status = check_temperature_status(temp_c);
    // Expected: temp_c > 120.0f returns CRITICAL_HOT_STATUS
    TEST_ASSERT_EQUAL_STRING(CRITICAL_HOT_STATUS, status);
}

void test_check_temperature_status_warning_hot_on_edge(void) {
    float temp_c = 120.0f; // Exactly on 120.0f, so not > 120.0f, falls to > 85.0f
    const char* status = check_temperature_status(temp_c);
    // Expected: 120.0f is not > 120.0f, but is > 85.0f, returns WARNING_HOT_STATUS
    TEST_ASSERT_EQUAL_STRING(WARNING_HOT_STATUS, status);
}

void test_check_temperature_status_warning_hot_above_edge(void) {
    float temp_c = 85.1f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 85.1f is not > 120.0f, but is > 85.0f, returns WARNING_HOT_STATUS
    TEST_ASSERT_EQUAL_STRING(WARNING_HOT_STATUS, status);
}

void test_check_temperature_status_normal_on_hot_edge(void) {
    float temp_c = 85.0f; // Exactly on 85.0f, so not > 85.0f, falls to < 0.0f or else
    const char* status = check_temperature_status(temp_c);
    // Expected: 85.0f is not > 85.0f, and not < 0.0f, returns NORMAL_STATUS
    TEST_ASSERT_EQUAL_STRING(NORMAL_STATUS, status);
}

void test_check_temperature_status_warning_cold_below_edge(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 0.0f is < 0.0f, returns WARNING_COLD_STATUS
    TEST_ASSERT_EQUAL_STRING(WARNING_COLD_STATUS, status);
}

void test_check_temperature_status_normal_on_cold_edge(void) {
    float temp_c = 0.0f; // Exactly on 0.0f, so not < 0.0f, falls to else
    const char* status = check_temperature_status(temp_c);
    // Expected: 0.0f is not < 0.0f, returns NORMAL_STATUS
    TEST_ASSERT_EQUAL_STRING(NORMAL_STATUS, status);
}

void test_check_temperature_status_normal_mid_range(void) {
    float temp_c = 25.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 25.0f is not in critical, warning hot, or warning cold ranges, returns NORMAL_STATUS
    TEST_ASSERT_EQUAL_STRING(NORMAL_STATUS, status);
}

void test_check_temperature_status_normal_zero(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: 0.0f is not in critical, warning hot, or warning cold ranges, returns NORMAL_STATUS
    TEST_ASSERT_EQUAL_STRING(NORMAL_STATUS, status);
}

// --- Test Functions for get_temperature_celsius() ---
void test_get_temperature_celsius_nominal_conversion(void) {
    // Configure stub to return a nominal Celsius value
    stub_raw_to_celsius.return_value = 25.5f;
    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    // Expected: raw_to_celsius's last_raw_val should be within [0, 1023] (from read_temperature_raw)
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_val);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_val);
    // Expected: get_temperature_celsius returns the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result);
}

void test_get_temperature_celsius_cold_conversion(void) {
    // Configure stub to return a cold Celsius value
    stub_raw_to_celsius.return_value = 0.0f;
    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    // Expected: raw_to_celsius's last_raw_val should be within [0, 1023]
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_val);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_val);
    // Expected: get_temperature_celsius returns the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

void test_get_temperature_celsius_hot_conversion(void) {
    // Configure stub to return a hot Celsius value
    stub_raw_to_celsius.return_value = 100.0f;
    float result = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    // Expected: raw_to_celsius should have been called exactly once
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    // Expected: raw_to_celsius's last_raw_val should be within [0, 1023]
    TEST_ASSERT_GREATER_OR_EQUAL_INT(0, stub_raw_to_celsius.last_raw_val);
    TEST_ASSERT_LESS_OR_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_val);
    // Expected: get_temperature_celsius returns the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 100.0f, result);
}

// --- Main function to run all tests ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_within_valid_range);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max_edge);
    RUN_TEST(test_validate_temperature_range_valid_nominal);
    RUN_TEST(test_validate_temperature_range_valid_zero);
    RUN_TEST(test_check_temperature_status_critical_hot_above_edge);
    RUN_TEST(test_check_temperature_status_warning_hot_on_edge);
    RUN_TEST(test_check_temperature_status_warning_hot_above_edge);
    RUN_TEST(test_check_temperature_status_normal_on_hot_edge);
    RUN_TEST(test_check_temperature_status_warning_cold_below_edge);
    RUN_TEST(test_check_temperature_status_normal_on_cold_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_zero);
    RUN_TEST(test_get_temperature_celsius_nominal_conversion);
    RUN_TEST(test_get_temperature_celsius_cold_conversion);
    RUN_TEST(test_get_temperature_celsius_hot_conversion);

    return UNITY_END();
}