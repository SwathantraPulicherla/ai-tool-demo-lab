/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h> // For memset

// Forward declaration of functions from source file
// These are internal functions, NOT to be stubbed according to rules.
// They will be called directly in tests.
// Note: The original source code contains "[STRING REDACTED]" placeholders
//       which are treated as distinct string literals by the compiler.
//       For tests involving these, we will use the same "[STRING REDACTED]" literal.
//       If these were actual string constants (e.g., "CRITICAL_HOT"), they
//       would typically be defined in an associated header file.
int read_temperature_raw();
bool validate_temperature_range(float temp_c);
const char* check_temperature_status(float temp_c);
float get_temperature_celsius();

// --- External Function Stubs ---

// Stubs for functions not in the source file but called by it.
// These are inferred from usage in the source code.

// raw_to_celsius stub signature: float raw_to_celsius(int raw)
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

// rand() stub (from <stdlib.h>, external dependency implicitly)
// We provide our own rand to make read_temperature_raw deterministic.
typedef struct {
    int return_value;
    bool was_called;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand = {0};

// Extern declaration to override the standard library's rand for testing.
// The linker will typically pick up this definition before the standard library one.
extern int rand(void);

int rand(void) {
    stub_rand.was_called = true;
    stub_rand.call_count++;
    return stub_rand.return_value;
}

// --- Test Fixture Setup and Teardown ---

void setUp(void) {
    // Reset all stub control structures
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // Default to a normal temp, but this should be explicitly set per test for specific scenarios
    stub_raw_to_celsius.return_value = 25.0f; 

    memset(&stub_rand, 0, sizeof(stub_rand));
    stub_rand.return_value = 0; // Default rand() to 0
}

void tearDown(void) {
    // Reset all stub control structures completely
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    memset(&stub_rand, 0, sizeof(stub_rand));
}

// --- Test Cases for read_temperature_raw ---

void test_read_temperature_raw_returns_expected_min_value(void) {
    // Configure rand to return 0, so read_temperature_raw returns 0 % 1024 = 0
    stub_rand.return_value = 0;
    int raw_temp = read_temperature_raw();
    // Expected: rand() should be called once to generate the raw value
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    // Expected: read_temperature_raw returns 0, based on rand() returning 0
    TEST_ASSERT_EQUAL_INT(0, raw_temp);
}

void test_read_temperature_raw_returns_expected_max_value(void) {
    // Configure rand to return 1023, so read_temperature_raw returns 1023 % 1024 = 1023
    stub_rand.return_value = 1023;
    int raw_temp = read_temperature_raw();
    // Expected: rand() should be called once to generate the raw value
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    // Expected: read_temperature_raw returns 1023, based on rand() returning 1023
    TEST_ASSERT_EQUAL_INT(1023, raw_temp);
}

void test_read_temperature_raw_returns_expected_mid_range_value(void) {
    // Configure rand to return a value that results in a mid-range raw value (e.g., 512)
    stub_rand.return_value = 512;
    int raw_temp = read_temperature_raw();
    // Expected: rand() should be called once to generate the raw value
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    // Expected: read_temperature_raw returns 512, based on rand() returning 512
    TEST_ASSERT_EQUAL_INT(512, raw_temp);
}

// --- Test Cases for validate_temperature_range ---

void test_validate_temperature_range_min_edge_valid(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is included in the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_max_edge_valid(void) {
    float temp = 125.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.0f is included in the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_nominal_valid(void) {
    float temp = 25.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 25.0f is within the valid range [0.0f, 125.0f]
    TEST_ASSERT_TRUE(result);
}

void test_validate_temperature_range_below_min_invalid(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is below the valid range [0.0f, 125.0f]
    TEST_ASSERT_FALSE(result);
}

void test_validate_temperature_range_above_max_invalid(void) {
    float temp = 125.1f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.1f is above the valid range [0.0f, 125.0f]
    TEST_ASSERT_FALSE(result);
}

// --- Test Cases for check_temperature_status ---

void test_check_temperature_status_critical_hot_above_120(void) {
    float temp = 120.1f;
    const char* status = check_temperature_status(temp);
    // Expected: 120.1f is > 120.0f, returning "[STRING REDACTED]" (CRITICAL_HOT)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_critical_hot_max_valid_temp(void) {
    float temp = 125.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 125.0f is > 120.0f, returning "[STRING REDACTED]" (CRITICAL_HOT)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_warning_hot_above_85_edge(void) {
    float temp = 85.1f;
    const char* status = check_temperature_status(temp);
    // Expected: 85.1f is > 85.0f but not > 120.0f, returning "[STRING REDACTED]" (WARNING_HOT)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_warning_hot_up_to_120_edge(void) {
    float temp = 120.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 120.0f is > 85.0f but not > 120.0f (it's equal), returning "[STRING REDACTED]" (WARNING_HOT)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_warning_cold_below_minus_10_edge(void) {
    float temp = 0.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is < 0.0f, returning "[STRING REDACTED]" (WARNING_COLD)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_warning_cold_min_valid_temp(void) {
    float temp = 0.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is < 0.0f, returning "[STRING REDACTED]" (WARNING_COLD)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_normal_at_minus_10_edge(void) {
    float temp = 0.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is not > 120.0f, not > 85.0f, and not < 0.0f (it's equal), returning "[STRING REDACTED]" (NORMAL)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_normal_at_0_degrees(void) {
    float temp = 0.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is not in any warning/critical range, returning "[STRING REDACTED]" (NORMAL)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

void test_check_temperature_status_normal_at_85_degrees_edge(void) {
    float temp = 85.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 85.0f is not > 120.0f, not > 85.0f (it's equal), and not < 0.0f, returning "[STRING REDACTED]" (NORMAL)
    TEST_ASSERT_EQUAL_STRING("[STRING REDACTED]", status);
}

// --- Test Cases for get_temperature_celsius ---

void test_get_temperature_celsius_returns_celsius_from_raw_min(void) {
    // Configure rand to return 0, so read_temperature_raw returns 0
    stub_rand.return_value = 0;
    // Configure raw_to_celsius for an input of 0 to return 0.0f (minimum valid temperature)
    stub_raw_to_celsius.return_value = 0.0f;

    float temp_c = get_temperature_celsius();

    // Expected: rand() should be called once by read_temperature_raw
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    // Expected: raw_to_celsius called once with the raw value 0
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.last_raw_param);
    // Expected: get_temperature_celsius returns 0.0f, matching the stub's return
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, temp_c);
}

void test_get_temperature_celsius_returns_celsius_from_raw_max(void) {
    // Configure rand to return 1023, so read_temperature_raw returns 1023
    stub_rand.return_value = 1023;
    // Configure raw_to_celsius for an input of 1023 to return 125.0f (maximum valid temperature)
    stub_raw_to_celsius.return_value = 125.0f;

    float temp_c = get_temperature_celsius();

    // Expected: rand() should be called once by read_temperature_raw
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    // Expected: raw_to_celsius called once with the raw value 1023
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_param);
    // Expected: get_temperature_celsius returns 125.0f, matching the stub's return
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, temp_c);
}

void test_get_temperature_celsius_returns_celsius_from_raw_mid_range(void) {
    // Configure rand to return 512, so read_temperature_raw returns 512
    stub_rand.return_value = 512;
    // Configure raw_to_celsius for an input of 512 to return 25.0f (nominal temperature)
    stub_raw_to_celsius.return_value = 25.0f;

    float temp_c = get_temperature_celsius();

    // Expected: rand() should be called once by read_temperature_raw
    TEST_ASSERT_TRUE(stub_rand.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_rand.call_count);
    // Expected: raw_to_celsius called once with the raw value 512
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(512, stub_raw_to_celsius.last_raw_param);
    // Expected: get_temperature_celsius returns 25.0f, matching the stub's return
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, temp_c);
}

// --- Main for Unity Test Runner ---



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_expected_min_value);
    RUN_TEST(test_read_temperature_raw_returns_expected_max_value);
    RUN_TEST(test_read_temperature_raw_returns_expected_mid_range_value);
    RUN_TEST(test_validate_temperature_range_min_edge_valid);
    RUN_TEST(test_validate_temperature_range_max_edge_valid);
    RUN_TEST(test_validate_temperature_range_nominal_valid);
    RUN_TEST(test_validate_temperature_range_below_min_invalid);
    RUN_TEST(test_validate_temperature_range_above_max_invalid);
    RUN_TEST(test_check_temperature_status_critical_hot_above_120);
    RUN_TEST(test_check_temperature_status_critical_hot_max_valid_temp);
    RUN_TEST(test_check_temperature_status_warning_hot_above_85_edge);
    RUN_TEST(test_check_temperature_status_warning_hot_up_to_120_edge);
    RUN_TEST(test_check_temperature_status_warning_cold_below_minus_10_edge);
    RUN_TEST(test_check_temperature_status_warning_cold_min_valid_temp);
    RUN_TEST(test_check_temperature_status_normal_at_minus_10_edge);
    RUN_TEST(test_check_temperature_status_normal_at_0_degrees);
    RUN_TEST(test_check_temperature_status_normal_at_85_degrees_edge);
    RUN_TEST(test_get_temperature_celsius_returns_celsius_from_raw_min);
    RUN_TEST(test_get_temperature_celsius_returns_celsius_from_raw_max);
    RUN_TEST(test_get_temperature_celsius_returns_celsius_from_raw_mid_range);

    return UNITY_END();
}