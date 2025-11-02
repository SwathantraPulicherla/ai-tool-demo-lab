/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // For memset

// Forward declarations of functions under test (from src/temp_sensor.c)
// These are assumed to be in another compilation unit, hence extern.
extern int read_temperature_raw();
extern bool validate_temperature_range(float temp_c);
extern const char* check_temperature_status(float temp_c);
extern float get_temperature_celsius();

// EXTERNAL FUNCTIONS TO STUB: raw_to_celsius
// Inferring signature from get_temperature_celsius(): float raw_to_celsius(int raw);
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_val;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius;

// Stub implementation for raw_to_celsius
float raw_to_celsius(int raw_val) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_val = raw_val;
    return stub_raw_to_celsius.return_value;
}

void setUp(void) {
    // Reset all stubs to their default, uncalled state for test isolation.
    // This ensures each test starts with a clean slate.
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

void tearDown(void) {
    // Reset all stubs again after each test, as a defensive measure.
    // This ensures no state leaks into subsequent tests, even if setUp failed or was skipped.
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// =========================================================================
// TESTS FOR read_temperature_raw()
// This function relies on rand() which is not listed as an external dependency to stub.
// Therefore, tests can only assert that the return value falls within the expected range.
// =========================================================================

void test_read_temperature_raw_returns_within_valid_range_single_call(void) {
    // Expected: The raw temperature should be between 0 and 1023 (inclusive), as per rand() % 1024.
    int result = read_temperature_raw();
    TEST_ASSERT_TRUE(result >= 0);    // Expected: Raw value is non-negative.
    TEST_ASSERT_TRUE(result <= 1023); // Expected: Raw value is less than 1024.
}

void test_read_temperature_raw_returns_within_valid_range_multiple_calls(void) {
    // Expected: Multiple calls should consistently return values within the 00.0f range.
    for (int i = 0; i < 10; i++) { // Test multiple times to ensure consistent range behavior
        int result = read_temperature_raw();
        TEST_ASSERT_TRUE(result >= 0);    // Expected: Raw value is non-negative for each call.
        TEST_ASSERT_TRUE(result <= 1023); // Expected: Raw value is less than 1024 for each call.
    }
}

// =========================================================================
// TESTS FOR validate_temperature_range(float temp_c)
// =========================================================================

void test_validate_temperature_range_valid_mid_range(void) {
    // Expected: 25.0f is within [0.0f, 125.0f], so should return true.
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_valid_min_edge(void) {
    // Expected: 0.0f is the minimum valid temperature, so should return true.
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_valid_max_edge(void) {
    // Expected: 125.0f is the maximum valid temperature, so should return true.
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_invalid_below_min(void) {
    // Expected: 0.0f is below the minimum valid temperature, so should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_invalid_above_max(void) {
    // Expected: 125.1f is above the maximum valid temperature, so should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_invalid_extreme_low(void) {
    // Expected: 0.0f is far below the minimum valid temperature, so should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_invalid_extreme_high(void) {
    // Expected: 200.0f is far above the maximum valid temperature, so should return false.
    TEST_ASSERT_FALSE(validate_temperature_range(200.0f));
}

// =========================================================================
// TESTS FOR check_temperature_status(float temp_c)
// Assuming "[STRING REDACTED]" correspond to "CRITICAL_HIGH_TEMP", "HIGH_TEMP", "LOW_TEMP", "NORMAL".
// =========================================================================

void test_check_temperature_status_critical_high_just_above_threshold(void) {
    // Expected: 120.1f is > 120.0f, triggering the critical high branch.
    TEST_ASSERT_EQUAL_STRING("CRITICAL_HIGH_TEMP", check_temperature_status(120.1f));
}

void test_check_temperature_status_critical_high_far_above_threshold(void) {
    // Expected: 150.0f is > 120.0f, triggering the critical high branch.
    TEST_ASSERT_EQUAL_STRING("CRITICAL_HIGH_TEMP", check_temperature_status(150.0f));
}

void test_check_temperature_status_high_just_above_threshold(void) {
    // Expected: 85.1f is > 85.0f but not > 120.0f, triggering the high temp branch.
    TEST_ASSERT_EQUAL_STRING("HIGH_TEMP", check_temperature_status(85.1f));
}

void test_check_temperature_status_high_at_critical_boundary(void) {
    // Expected: 120.0f is not > 120.0f, but is > 85.0f, triggering the high temp branch.
    TEST_ASSERT_EQUAL_STRING("HIGH_TEMP", check_temperature_status(120.0f));
}

void test_check_temperature_status_normal_high_boundary(void) {
    // Expected: 85.0f is not > 85.0f, falling into the normal range.
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: 25.0f is within [0.0f, 85.0f] (and <=120), falling into the normal range.
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_low_boundary(void) {
    // Expected: 0.0f is not < 0.0f, falling into the normal range.
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
}

void test_check_temperature_status_low_just_below_threshold(void) {
    // Expected: 0.0f is < 0.0f, triggering the low temp branch.
    TEST_ASSERT_EQUAL_STRING("LOW_TEMP", check_temperature_status(0.0f));
}

void test_check_temperature_status_low_far_below_threshold(void) {
    // Expected: 0.0f is < 0.0f, triggering the low temp branch.
    TEST_ASSERT_EQUAL_STRING("LOW_TEMP", check_temperature_status(0.0f));
}

// =========================================================================
// TESTS FOR get_temperature_celsius()
// This function calls read_temperature_raw() (non-deterministic) and raw_to_celsius() (stubbed).
// =========================================================================

void test_get_temperature_celsius_calls_dependencies_and_returns_converted_value(void) {
    // Setup: Configure raw_to_celsius stub to return a specific value.
    float expected_celsius = 25.5f;
    stub_raw_to_celsius.return_value = expected_celsius;

    // Action: Call the function under test.
    float actual_celsius = get_temperature_celsius();

    // Assertions:
    // Expected: raw_to_celsius should have been called once.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be within 00.0f (from read_temperature_raw).
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val <= 1023);
    // Expected: The function should return the value provided by the stub for raw_to_celsius.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_with_different_stub_return_value_high(void) {
    // Setup: Configure raw_to_celsius stub for a different value (e.g., high temp).
    float expected_celsius = 100.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    // Action: Call the function under test.
    float actual_celsius = get_temperature_celsius();

    // Assertions:
    // Expected: raw_to_celsius should have been called once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be within 00.0f.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val <= 1023);
    // Expected: The function should return the value provided by the stub.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_with_another_stub_return_value_low(void) {
    // Setup: Configure raw_to_celsius stub for a different value (e.g., low temp).
    float expected_celsius = 0.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    // Action: Call the function under test.
    float actual_celsius = get_temperature_celsius();

    // Assertions:
    // Expected: raw_to_celsius should have been called once.
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    // Expected: The raw value passed to raw_to_celsius should be within 00.0f.
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val >= 0);
    TEST_ASSERT_TRUE(stub_raw_to_celsius.last_raw_val <= 1023);
    // Expected: The function should return the value provided by the stub.
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}


// =========================================================================
// Main test runner
// =========================================================================


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_within_valid_range_single_call);
    RUN_TEST(test_read_temperature_raw_returns_within_valid_range_multiple_calls);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_validate_temperature_range_invalid_extreme_low);
    RUN_TEST(test_validate_temperature_range_invalid_extreme_high);
    RUN_TEST(test_check_temperature_status_critical_high_just_above_threshold);
    RUN_TEST(test_check_temperature_status_critical_high_far_above_threshold);
    RUN_TEST(test_check_temperature_status_high_just_above_threshold);
    RUN_TEST(test_check_temperature_status_high_at_critical_boundary);
    RUN_TEST(test_check_temperature_status_normal_high_boundary);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_low_boundary);
    RUN_TEST(test_check_temperature_status_low_just_below_threshold);
    RUN_TEST(test_check_temperature_status_low_far_below_threshold);
    RUN_TEST(test_get_temperature_celsius_calls_dependencies_and_returns_converted_value);
    RUN_TEST(test_get_temperature_celsius_with_different_stub_return_value_high);
    RUN_TEST(test_get_temperature_celsius_with_another_stub_return_value_low);

    return UNITY_END();
}