/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h> // Required for rand() if testing read_temperature_raw directly

// Declare functions from temp_sensor.c as extern to make them visible to the test runner.
// This assumes temp_sensor.c will be compiled and linked with this test file.
extern int read_temperature_raw();
extern bool validate_temperature_range(float temp_c);
extern const char* check_temperature_status(float temp_c);
extern float get_temperature_celsius();

// --- External Stub Definitions ---
// EXTERNAL FUNCTIONS TO STUB: raw_to_celsius
// Inferred signature: float raw_to_celsius(int raw_val)
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_val; // Captured parameter for verification
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw_val) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_val = raw_val;
    return stub_raw_to_celsius.return_value;
}

// --- Constants for Redacted Strings ---
// These are assumed descriptive string literals for the "[STRING REDACTED]" in the source.
// This provides realistic values for testing string comparisons.
static const char* const STATUS_CRITICAL_HOT = "CRITICAL_HOT";
static const char* const STATUS_WARNING_HOT = "WARNING_HOT";
static const char* const STATUS_WARNING_COLD = "WARNING_COLD";
static const char* const STATUS_NORMAL = "NORMAL";

// --- SetUp and TearDown ---
void setUp(void) {
    // Reset all stub control structures before each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

void tearDown(void) {
    // Ensure all stub control structures are reset after each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Test Cases for read_temperature_raw ---

// Test: read_temperature_raw should return a value within the expected range [0, 1023].
// Since `rand()` is an external dependency not specified for stubbing, its behavior is non-deterministic.
// We test its output range over multiple calls for probabilistic validation.
void test_read_temperature_raw_returns_in_range(void) {
    int raw_val;
    // Call multiple times to increase confidence that results are within the specified range.
    for (int i = 0; i < 100; i++) {
        raw_val = read_temperature_raw();
        // Expected: Raw value must be within 0 and 1023 based on `rand() % 1024` logic.
        TEST_ASSERT_TRUE(raw_val >= 0);
        TEST_ASSERT_TRUE(raw_val <= 1023);
    }
}

// --- Test Cases for validate_temperature_range ---

// Test: Nominal temperature (25.0f) should be considered valid.
void test_validate_temperature_range_nominal_valid(void) {
    float temp = 25.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 25.0f is between 0.0f and 125.0f (inclusive), so should be true.
    TEST_ASSERT_TRUE(result);
}

// Test: Minimum valid temperature (0.0f) should be considered valid.
void test_validate_temperature_range_min_edge_valid(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is inclusive in the valid range, so should be true.
    TEST_ASSERT_TRUE(result);
}

// Test: Temperature just below minimum valid (0.0f) should be considered invalid.
void test_validate_temperature_range_below_min_invalid(void) {
    float temp = 0.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 0.0f is strictly less than 0.0f, so should be false.
    TEST_ASSERT_FALSE(result);
}

// Test: Maximum valid temperature (125.0f) should be considered valid.
void test_validate_temperature_range_max_edge_valid(void) {
    float temp = 125.0f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.0f is inclusive in the valid range, so should be true.
    TEST_ASSERT_TRUE(result);
}

// Test: Temperature just above maximum valid (125.1f) should be considered invalid.
void test_validate_temperature_range_above_max_invalid(void) {
    float temp = 125.1f;
    bool result = validate_temperature_range(temp);
    // Expected: 125.1f is strictly greater than 125.0f, so should be false.
    TEST_ASSERT_FALSE(result);
}

// --- Test Cases for check_temperature_status ---

// Test: Temperature slightly above 120.0f should return CRITICAL_HOT.
void test_check_temperature_status_critical_hot_above_threshold(void) {
    float temp = 120.1f; // Just above the critical hot threshold
    const char* status = check_temperature_status(temp);
    // Expected: 120.1f > 120.0f, triggering the CRITICAL_HOT branch.
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_HOT, status);
}

// Test: Maximum valid temperature (125.0f) should return CRITICAL_HOT.
void test_check_temperature_status_critical_hot_max_valid(void) {
    float temp = 125.0f; // Max valid temp, also critical hot
    const char* status = check_temperature_status(temp);
    // Expected: 125.0f > 120.0f, triggering the CRITICAL_HOT branch.
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_HOT, status);
}

// Test: Temperature exactly at 120.0f should return WARNING_HOT (not critical).
void test_check_temperature_status_at_critical_hot_threshold(void) {
    float temp = 120.0f; // Exactly at the critical hot threshold
    const char* status = check_temperature_status(temp);
    // Expected: 120.0f is not > 120.0f, but it is > 85.0f, triggering the WARNING_HOT branch.
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_HOT, status);
}

// Test: Temperature slightly above 85.0f should return WARNING_HOT.
void test_check_temperature_status_warning_hot_above_threshold(void) {
    float temp = 85.1f; // Just above the warning hot threshold
    const char* status = check_temperature_status(temp);
    // Expected: 85.1f is not > 120.0f, but is > 85.0f, triggering the WARNING_HOT branch.
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_HOT, status);
}

// Test: Temperature exactly at 85.0f should return NORMAL (not warning hot).
void test_check_temperature_status_at_warning_hot_threshold(void) {
    float temp = 85.0f; // Exactly at the warning hot threshold
    const char* status = check_temperature_status(temp);
    // Expected: 85.0f is not > 120.0f and not > 85.0f, thus falling into the NORMAL else branch.
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status);
}

// Test: Nominal temperature (25.0f) should return NORMAL.
void test_check_temperature_status_nominal_normal(void) {
    float temp = 25.0f;
    const char* status = check_temperature_status(temp);
    // Expected: 25.0f is not > 120.0f, not > 85.0f, and not < 0.0f, thus NORMAL.
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status);
}

// Test: Temperature exactly at 0.0f should return NORMAL (not warning cold).
void test_check_temperature_status_at_warning_cold_threshold(void) {
    float temp = 0.0f; // Exactly at the warning cold threshold
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f is not < 0.0f, thus falling into the NORMAL else branch.
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status);
}

// Test: Temperature slightly below 0.0f should return WARNING_COLD.
void test_check_temperature_status_warning_cold_below_threshold(void) {
    float temp = 0.0f; // Just below the warning cold threshold
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f < 0.0f, triggering the WARNING_COLD branch.
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_COLD, status);
}

// Test: Minimum valid temperature (0.0f) should return WARNING_COLD.
void test_check_temperature_status_warning_cold_min_valid(void) {
    float temp = 0.0f; // Min valid temp, also warning cold
    const char* status = check_temperature_status(temp);
    // Expected: 0.0f < 0.0f, triggering the WARNING_COLD branch.
    TEST_ASSERT_EQUAL_STRING(STATUS_WARNING_COLD, status);
}

// --- Test Cases for get_temperature_celsius ---

// Test: Get temperature in Celsius for a nominal raw conversion.
void test_get_temperature_celsius_nominal(void) {
    // Configure stub for `raw_to_celsius` to return a nominal Celsius value.
    stub_raw_to_celsius.return_value = 25.5f;

    float result = get_temperature_celsius();

    // Expected: `raw_to_celsius` should have been called exactly once.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to `raw_to_celsius` (from `read_temperature_raw`)
    // should be within the 00.0f range.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val <= 1023);
    // Expected: `get_temperature_celsius` should return the stubbed value from `raw_to_celsius`.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 25.5f, result);
}

// Test: Get temperature in Celsius for a cold range raw conversion.
void test_get_temperature_celsius_cold(void) {
    // Configure stub for `raw_to_celsius` to return a cold Celsius value.
    stub_raw_to_celsius.return_value = 0.0f;

    float result = get_temperature_celsius();

    // Expected: `raw_to_celsius` should have been called exactly once.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to `raw_to_celsius` should be in the 00.0f range.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val <= 1023);
    // Expected: `get_temperature_celsius` should return the stubbed value from `raw_to_celsius`.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, result);
}

// Test: Get temperature in Celsius for a hot range raw conversion.
void test_get_temperature_celsius_hot(void) {
    // Configure stub for `raw_to_celsius` to return a hot Celsius value.
    stub_raw_to_celsius.return_value = 110.0f;

    float result = get_temperature_celsius();

    // Expected: `raw_to_celsius` should have been called exactly once.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to `raw_to_celsius` should be in the 00.0f range.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val <= 1023);
    // Expected: `get_temperature_celsius` should return the stubbed value from `raw_to_celsius`.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 110.0f, result);
}


// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_in_range);
    RUN_TEST(test_validate_temperature_range_nominal_valid);
    RUN_TEST(test_validate_temperature_range_min_edge_valid);
    RUN_TEST(test_validate_temperature_range_below_min_invalid);
    RUN_TEST(test_validate_temperature_range_max_edge_valid);
    RUN_TEST(test_validate_temperature_range_above_max_invalid);
    RUN_TEST(test_check_temperature_status_critical_hot_above_threshold);
    RUN_TEST(test_check_temperature_status_critical_hot_max_valid);
    RUN_TEST(test_check_temperature_status_at_critical_hot_threshold);
    RUN_TEST(test_check_temperature_status_warning_hot_above_threshold);
    RUN_TEST(test_check_temperature_status_at_warning_hot_threshold);
    RUN_TEST(test_check_temperature_status_nominal_normal);
    RUN_TEST(test_check_temperature_status_at_warning_cold_threshold);
    RUN_TEST(test_check_temperature_status_warning_cold_below_threshold);
    RUN_TEST(test_check_temperature_status_warning_cold_min_valid);
    RUN_TEST(test_get_temperature_celsius_nominal);
    RUN_TEST(test_get_temperature_celsius_cold);
    RUN_TEST(test_get_temperature_celsius_hot);

    return UNITY_END();
}