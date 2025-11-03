/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdint.h>   // For uint32_t
#include <stdbool.h>  // For bool
#include <string.h>   // For memset

// Forward declarations of functions under test (from temp_sensor.c)
// These are not static, so they are visible externally.
int read_temperature_raw(void);
bool validate_temperature_range(float temp_c);
const char* check_temperature_status(float temp_c);
float get_temperature_celsius(void);

// Constants for redacted status strings, inferred from common embedded scenarios
#define STATUS_CRITICAL_HOT "CRITICAL_OVERHEAT"
#define STATUS_HOT          "WARNING_HOT"
#define STATUS_COLD         "WARNING_COLD"
#define STATUS_NORMAL       "NORMAL"

// --- Mock/Stub for rand() ---
// As read_temperature_raw() depends on rand(), we need to stub rand()
// to make read_temperature_raw() deterministic for testing.
typedef struct {
    int return_value;
    uint32_t call_count;
} stub_rand_t;
static stub_rand_t stub_rand = {0};

// Stub implementation for rand()
int rand(void) {
    stub_rand.call_count++;
    return stub_rand.return_value;
}

// --- Mock/Stub for raw_to_celsius() ---
// This is an external dependency as specified in the prompt.
// Signature is inferred from get_temperature_celsius() call: raw_to_celsius(raw).
typedef struct {
    float return_value;
    bool was_called;
    uint3    uint32_t call_count;
    int last_raw_param; // To capture the parameter passed to the stub
} stub_raw_to_celsius_t;
static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

// Stub implementation for raw_to_celsius()
float raw_to_celsius(int raw) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_param = raw;
    return stub_raw_to_celsius.return_value;
}

// --- Test Setup and Teardown ---
void setUp(void) {
    // Reset all stub control structures before each test
    memset(&stub_rand, 0, sizeof(stub_rand));
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));

    // Default stub return values
    stub_rand.return_value = 0; // Default to a known value
    stub_raw_to_celsius.return_value = 0.0f; // Default to a known value
}

void tearDown(void) {
    // Ensure all stubs are reset after each test
    memset(&stub_rand, 0, sizeof(stub_rand));
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Tests for read_temperature_raw() ---

// Test case for read_temperature_raw returning the minimum possible raw value (0)
void test_read_temperature_raw_returns_min_value(void) {
    stub_rand.return_value = 0; // Configure rand() to return 0
    int result = read_temperature_raw();
    TEST_ASSERT_EQUAL_INT(0, result); // Expected: 0, as 0 % 1024 is 0
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count); // Expected: rand() called once
}

// Test case for read_temperature_raw returning a mid-range raw value (e.g., 500)
void test_read_temperature_raw_returns_mid_range_value(void) {
    stub_rand.return_value = 500; // Configure rand() to return 500
    int result = read_temperature_raw();
    TEST_ASSERT_EQUAL_INT(500, result); // Expected: 500, as 500 % 1024 is 500
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count); // Expected: rand() called once
}

// Test case for read_temperature_raw returning the maximum possible raw value (1023)
void test_read_temperature_raw_returns_max_value(void) {
    stub_rand.return_value = 1023; // Configure rand() to return 1023
    int result = read_temperature_raw();
    TEST_ASSERT_EQUAL_INT(1023, result); // Expected: 1023, as 1023 % 1024 is 1023
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count); // Expected: rand() called once
}

// Test case for read_temperature_raw when rand() returns a value greater than 1023
void test_read_temperature_raw_returns_value_above_modulo(void) {
    stub_rand.return_value = 2048; // Configure rand() to return 2048 (e.g., if RAND_MAX is large)
    int result = read_temperature_raw();
    TEST_ASSERT_EQUAL_INT(0, result); // Expected: 0, as 2048 % 1024 is 0
    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count); // Expected: rand() called once
}


// --- Tests for validate_temperature_range() ---

// Test case for temperature at the minimum valid edge
void test_validate_temperature_range_min_edge_valid(void) {
    bool result = validate_temperature_range(0.0f);
    TEST_ASSERT_TRUE(result); // Expected: True, 0.0f is within [0.0f, 125.0f]
}

// Test case for temperature just below the minimum valid edge
void test_validate_temperature_range_min_edge_invalid(void) {
    bool result = validate_temperature_range(0.0f);
    TEST_ASSERT_FALSE(result); // Expected: False, 0.0f is outside [0.0f, 125.0f]
}

// Test case for temperature at the maximum valid edge
void test_validate_temperature_range_max_edge_valid(void) {
    bool result = validate_temperature_range(125.0f);
    TEST_ASSERT_TRUE(result); // Expected: True, 125.0f is within [0.0f, 125.0f]
}

// Test case for temperature just above the maximum valid edge
void test_validate_temperature_range_max_edge_invalid(void) {
    bool result = validate_temperature_range(125.1f);
    TEST_ASSERT_FALSE(result); // Expected: False, 125.1f is outside [0.0f, 125.0f]
}

// Test case for a nominal temperature within the valid range
void test_validate_temperature_range_nominal_valid(void) {
    bool result = validate_temperature_range(25.0f);
    TEST_ASSERT_TRUE(result); // Expected: True, 25.0f is within [0.0f, 125.0f]
}


// --- Tests for check_temperature_status() ---

// Test case for temperature in the CRITICAL_OVERHEAT zone (> 120.0f)
void test_check_temperature_status_critical_hot(void) {
    const char* status = check_temperature_status(120.1f);
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_HOT, status); // Expected: CRITICAL_OVERHEAT, as 120.1f > 120.0f
}

// Test case for temperature at the lower edge of CRITICAL_OVERHEAT
void test_check_temperature_status_critical_hot_edge(void) {
    const char* status = check_temperature_status(125.0f); // Max valid temperature
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_HOT, status); // Expected: CRITICAL_OVERHEAT, as 125.0f > 120.0f
}

// Test case for temperature in the WARNING_HOT zone (> 85.0f and <= 120.0f)
void test_check_temperature_status_warning_hot(void) {
    const char* status = check_temperature_status(85.1f);
    TEST_ASSERT_EQUAL_STRING(STATUS_HOT, status); // Expected: WARNING_HOT, as 85.1f > 85.0f and <= 120.0f
}

// Test case for temperature at the upper edge of WARNING_HOT
void test_check_temperature_status_warning_hot_upper_edge(void) {
    const char* status = check_temperature_status(120.0f);
    TEST_ASSERT_EQUAL_STRING(STATUS_HOT, status); // Expected: WARNING_HOT, as 120.0f > 85.0f and <= 120.0f
}

// Test case for temperature in the WARNING_COLD zone (< 0.0f)
void test_check_temperature_status_warning_cold(void) {
    const char* status = check_temperature_status(0.0f);
    TEST_ASSERT_EQUAL_STRING(STATUS_COLD, status); // Expected: WARNING_COLD, as 0.0f < 0.0f
}

// Test case for temperature at the lower edge of WARNING_COLD
void test_check_temperature_status_warning_cold_lower_edge(void) {
    const char* status = check_temperature_status(0.0f); // Min valid temperature
    TEST_ASSERT_EQUAL_STRING(STATUS_COLD, status); // Expected: WARNING_COLD, as 0.0f < 0.0f
}

// Test case for temperature in the NORMAL zone (0.0f <= temp_c <= 85.0f)
void test_check_temperature_status_normal_mid_range(void) {
    const char* status = check_temperature_status(25.0f);
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status); // Expected: NORMAL, as 25.0f is within [0.0f, 85.0f]
}

// Test case for temperature at the lower edge of NORMAL
void test_check_temperature_status_normal_lower_edge(void) {
    const char* status = check_temperature_status(0.0f);
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status); // Expected: NORMAL, as 0.0f is within [0.0f, 85.0f]
}

// Test case for temperature at the upper edge of NORMAL
void test_check_temperature_status_normal_upper_edge(void) {
    const char* status = check_temperature_status(85.0f);
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status); // Expected: NORMAL, as 85.0f is within [0.0f, 85.0f]
}


// --- Tests for get_temperature_celsius() ---

// Test case for a normal temperature scenario (mid-range raw to mid-range Celsius)
void test_get_temperature_celsius_normal_scenario(void) {
    stub_rand.return_value = 512; // Configure rand() for read_temperature_raw to return a mid-range value (512)
    stub_raw_to_celsius.return_value = 25.0f; // Configure raw_to_celsius to return a nominal temp

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count); // Expected: rand() called once by read_temperature_raw
    TEST_ASSERT_EQUAL_INT(512, stub_raw_to_celsius.last_raw_param); // Expected: raw_to_celsius received 512 from read_temperature_raw
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called); // Expected: raw_to_celsius was called
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count); // Expected: raw_to_celsius called once
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.0f, result); // Expected: 25.0f, as configured by stub_raw_to_celsius
}

// Test case for minimum raw value resulting in minimum valid Celsius temperature
void test_get_temperature_celsius_min_raw_to_min_celsius(void) {
    stub_rand.return_value = 0; // Configure rand() for read_temperature_raw to return 0
    stub_raw_to_celsius.return_value = 0.0f; // Configure raw_to_celsius to return min valid temp

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count); // Expected: rand() called once
    TEST_ASSERT_EQUAL_INT(0, stub_raw_to_celsius.last_raw_param); // Expected: raw_to_celsius received 0
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result); // Expected: 0.0f, as configured
}

// Test case for maximum raw value resulting in maximum valid Celsius temperature
void test_get_temperature_celsius_max_raw_to_max_celsius(void) {
    stub_rand.return_value = 1023; // Configure rand() for read_temperature_raw to return 1023
    stub_raw_to_celsius.return_value = 125.0f; // Configure raw_to_celsius to return max valid temp

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count); // Expected: rand() called once
    TEST_ASSERT_EQUAL_INT(1023, stub_raw_to_celsius.last_raw_param); // Expected: raw_to_celsius received 1023
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 125.0f, result); // Expected: 125.0f, as configured
}

// Test case where raw_to_celsius returns an internal error temperature (e.g., NaN or a specific error code)
// For this scenario, we assume the float can represent an error or out-of-range value as defined by the system.
void test_get_temperature_celsius_raw_to_celsius_returns_error_value(void) {
    stub_rand.return_value = 100; // Some raw value
    // Assuming 999.0f might be an indicator for an error or out-of-range conversion
    // This value is > 125.0f, simulating an output that is outside the normal physical range
    stub_raw_to_celsius.return_value = 999.0f; 

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_UINT32(1, stub_rand.call_count); // Expected: rand() called once
    TEST_ASSERT_EQUAL_INT(100, stub_raw_to_celsius.last_raw_param); // Expected: raw_to_celsius received 100
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 999.0f, result); // Expected: 999.0f, as configured
}


// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_min_value);
    RUN_TEST(test_read_temperature_raw_returns_mid_range_value);
    RUN_TEST(test_read_temperature_raw_returns_max_value);
    RUN_TEST(test_read_temperature_raw_returns_value_above_modulo);
    RUN_TEST(test_validate_temperature_range_min_edge_valid);
    RUN_TEST(test_validate_temperature_range_min_edge_invalid);
    RUN_TEST(test_validate_temperature_range_max_edge_valid);
    RUN_TEST(test_validate_temperature_range_max_edge_invalid);
    RUN_TEST(test_validate_temperature_range_nominal_valid);
    RUN_TEST(test_check_temperature_status_critical_hot);
    RUN_TEST(test_check_temperature_status_critical_hot_edge);
    RUN_TEST(test_check_temperature_status_warning_hot);
    RUN_TEST(test_check_temperature_status_warning_hot_upper_edge);
    RUN_TEST(test_check_temperature_status_warning_cold);
    RUN_TEST(test_check_temperature_status_warning_cold_lower_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_lower_edge);
    RUN_TEST(test_check_temperature_status_normal_upper_edge);
    RUN_TEST(test_get_temperature_celsius_normal_scenario);
    RUN_TEST(test_get_temperature_celsius_min_raw_to_min_celsius);
    RUN_TEST(test_get_temperature_celsius_max_raw_to_max_celsius);
    RUN_TEST(test_get_temperature_celsius_raw_to_celsius_returns_error_value);

    return UNITY_END();
}