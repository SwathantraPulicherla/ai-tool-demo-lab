/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // For memset
#include <stdlib.h> // For rand(), used by read_temperature_raw()

// Derived constants from source logic
// These strings correspond to [STRING REDACTED] in the original source
static const char* const STATUS_CRITICAL_HOT = "CRITICAL_HOT";
static const char* const STATUS_HOT          = "HOT";
static const char* const STATUS_COLD         = "COLD";
static const char* const STATUS_NORMAL       = "NORMAL";

// --- External Function Declarations (from temp_sensor.c, not from a header) ---
// These are included here to allow direct calling in tests when not stubbed.
// For functions defined in the same .c file, do not stub.
extern int read_temperature_raw();
extern bool validate_temperature_range(float temp_c);
extern const char* check_temperature_status(float temp_c);
extern float get_temperature_celsius();

// --- External Dependencies to Stub ---
// Function signature inferred from usage: float raw_to_celsius(int raw_value)
typedef struct {
    float    return_value;
    bool     was_called;
    uint32_t call_count;
    int      last_raw_value;
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_value = raw_value;
    return stub_raw_to_celsius.return_value;
}

// --- Test Setup and Teardown ---
void setUp(void) {
    // Reset all stubs
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

void tearDown(void) {
    // Reset all stubs
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Test Cases for read_temperature_raw() ---

/**
 * @brief Tests that read_temperature_raw returns values within the expected range [0, 1023].
 * This function uses rand(), so we cannot assert a specific value, only its bounds.
 */
void test_read_temperature_raw_returns_in_range(void) {
    int raw_val;
    
    // Check multiple calls for robustness, as rand() is involved
    for (int i = 0; i < 10; i++) {
        raw_val = read_temperature_raw();
        // Expected: Raw value must be within 0 and 1023 (inclusive) based on rand() % 1024
        TEST_ASSERT_TRUE_MESSAGE(raw_val >= 0, "Raw value should not be negative.");
        TEST_ASSERT_TRUE_MESSAGE(raw_val < 1024, "Raw value should be less than 1024.");
    }
}

// --- Test Cases for validate_temperature_range() ---

/**
 * @brief Tests validate_temperature_range with the minimum valid temperature.
 * Expected: 0.0f is within range, so should return true.
 */
void test_validate_temperature_range_valid_min_edge(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 0.0f is >= 0.0f and <= 125.0f, so should be true
    TEST_ASSERT_TRUE(result);
}

/**
 * @brief Tests validate_temperature_range with a value just below the minimum valid temperature.
 * Expected: 0.0f is out of range, so should return false.
 */
void test_validate_temperature_range_invalid_below_min(void) {
    float temp_c = 0.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 0.0f is not >= 0.0f, so should be false
    TEST_ASSERT_FALSE(result);
}

/**
 * @brief Tests validate_temperature_range with the maximum valid temperature.
 * Expected: 125.0f is within range, so should return true.
 */
void test_validate_temperature_range_valid_max_edge(void) {
    float temp_c = 125.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 125.0f is >= 0.0f and <= 125.0f, so should be true
    TEST_ASSERT_TRUE(result);
}

/**
 * @brief Tests validate_temperature_range with a value just above the maximum valid temperature.
 * Expected: 125.1f is out of range, so should return false.
 */
void test_validate_temperature_range_invalid_above_max(void) {
    float temp_c = 125.1f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 125.1f is not <= 125.0f, so should be false
    TEST_ASSERT_FALSE(result);
}

/**
 * @brief Tests validate_temperature_range with a nominal, mid-range valid temperature.
 * Expected: 25.0f is within range, so should return true.
 */
void test_validate_temperature_range_valid_mid_range(void) {
    float temp_c = 25.0f;
    bool result = validate_temperature_range(temp_c);
    // Expected: 25.0f is >= 0.0f and <= 125.0f, so should be true
    TEST_ASSERT_TRUE(result);
}

// --- Test Cases for check_temperature_status() ---

/**
 * @brief Tests check_temperature_status with a temperature just above the CRITICAL_HOT threshold.
 * Expected: 120.1f is > 120.0f, so should return "CRITICAL_HOT".
 */
void test_check_temperature_status_critical_hot_above_edge(void) {
    float temp_c = 120.1f;
    const char* status = check_temperature_status(temp_c);
    // Expected: temp_c > 120.0f condition met
    TEST_ASSERT_EQUAL_STRING(STATUS_CRITICAL_HOT, status);
}

/**
 * @brief Tests check_temperature_status with a temperature at the CRITICAL_HOT threshold, falling into HOT.
 * Expected: 120.0f is not > 120.0f, but is > 85.0f, so should return "HOT".
 */
void test_check_temperature_status_hot_at_critical_edge(void) {
    float temp_c = 120.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: temp_c is not > 120.0f, but is > 85.0f
    TEST_ASSERT_EQUAL_STRING(STATUS_HOT, status);
}

/**
 * @brief Tests check_temperature_status with a temperature just above the HOT threshold.
 * Expected: 85.1f is > 85.0f, so should return "HOT".
 */
void test_check_temperature_status_hot_above_edge(void) {
    float temp_c = 85.1f;
    const char* status = check_temperature_status(temp_c);
    // Expected: temp_c is not > 120.0f, but is > 85.0f
    TEST_ASSERT_EQUAL_STRING(STATUS_HOT, status);
}

/**
 * @brief Tests check_temperature_status with a temperature at the HOT threshold, falling into NORMAL.
 * Expected: 85.0f is not > 85.0f, but is not < 0.0f, so should return "NORMAL".
 */
void test_check_temperature_status_normal_at_hot_edge(void) {
    float temp_c = 85.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: temp_c is not > 120.0f, not > 85.0f, not < 0.0f
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status);
}

/**
 * @brief Tests check_temperature_status with a temperature just below the COLD threshold.
 * Expected: 0.0f is < 0.0f, so should return "COLD".
 */
void test_check_temperature_status_cold_below_edge(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: temp_c is not > 120.0f, not > 85.0f, but is < 0.0f
    TEST_ASSERT_EQUAL_STRING(STATUS_COLD, status);
}

/**
 * @brief Tests check_temperature_status with a temperature at the COLD threshold, falling into NORMAL.
 * Expected: 0.0f is not < 0.0f, so should return "NORMAL".
 */
void test_check_temperature_status_normal_at_cold_edge(void) {
    float temp_c = 0.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: temp_c is not > 120.0f, not > 85.0f, not < 0.0f
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status);
}

/**
 * @brief Tests check_temperature_status with a nominal, mid-range temperature, resulting in NORMAL.
 * Expected: 25.0f falls into the final else branch, returning "NORMAL".
 */
void test_check_temperature_status_normal_mid_range(void) {
    float temp_c = 25.0f;
    const char* status = check_temperature_status(temp_c);
    // Expected: temp_c is not > 120.0f, not > 85.0f, not < 0.0f
    TEST_ASSERT_EQUAL_STRING(STATUS_NORMAL, status);
}

// --- Test Cases for get_temperature_celsius() ---

/**
 * @brief Tests get_temperature_celsius when raw_to_celsius converts to a nominal temperature.
 * Verifies dependencies are called and the final converted value is returned.
 */
void test_get_temperature_celsius_nominal_conversion(void) {
    float expected_celsius = 25.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    
    // Expected: The raw value passed to raw_to_celsius should be in the range [0, 1023]
    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.last_raw_value >= 0, "Raw value to stub should be non-negative.");
    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.last_raw_value < 1024, "Raw value to stub should be less than 1024.");

    // Expected: The function should return the value provided by the raw_to_celsius stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

/**
 * @brief Tests get_temperature_celsius when raw_to_celsius converts to a low temperature.
 * Ensures the flow is correct even with different return values from the stub.
 */
void test_get_temperature_celsius_low_temp_conversion(void) {
    float expected_celsius = 0.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    
    // Expected: The raw value passed to raw_to_celsius should be in the range [0, 1023]
    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.last_raw_value >= 0, "Raw value to stub should be non-negative.");
    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.last_raw_value < 1024, "Raw value to stub should be less than 1024.");

    // Expected: The function should return the value provided by the raw_to_celsius stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

/**
 * @brief Tests get_temperature_celsius when raw_to_celsius converts to a high temperature.
 * Ensures the flow is correct even with different return values from the stub.
 */
void test_get_temperature_celsius_high_temp_conversion(void) {
    float expected_celsius = 100.0f;
    stub_raw_to_celsius.return_value = expected_celsius;

    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once
    TEST_ASSERT_TRUE(stub_raw_to_celsius.was_called);
    TEST_ASSERT_EQUAL_UINT32(1, stub_raw_to_celsius.call_count);
    
    // Expected: The raw value passed to raw_to_celsius should be in the range [0, 1023]
    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.last_raw_value >= 0, "Raw value to stub should be non-negative.");
    TEST_ASSERT_TRUE_MESSAGE(stub_raw_to_celsius.last_raw_value < 1024, "Raw value to stub should be less than 1024.");

    // Expected: The function should return the value provided by the raw_to_celsius stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}


// --- Main Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_returns_in_range);
    RUN_TEST(test_validate_temperature_range_valid_min_edge);
    RUN_TEST(test_validate_temperature_range_invalid_below_min);
    RUN_TEST(test_validate_temperature_range_valid_max_edge);
    RUN_TEST(test_validate_temperature_range_invalid_above_max);
    RUN_TEST(test_validate_temperature_range_valid_mid_range);
    RUN_TEST(test_check_temperature_status_critical_hot_above_edge);
    RUN_TEST(test_check_temperature_status_hot_at_critical_edge);
    RUN_TEST(test_check_temperature_status_hot_above_edge);
    RUN_TEST(test_check_temperature_status_normal_at_hot_edge);
    RUN_TEST(test_check_temperature_status_cold_below_edge);
    RUN_TEST(test_check_temperature_status_normal_at_cold_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_get_temperature_celsius_nominal_conversion);
    RUN_TEST(test_get_temperature_celsius_low_temp_conversion);
    RUN_TEST(test_get_temperature_celsius_high_temp_conversion);

    return UNITY_END();
}