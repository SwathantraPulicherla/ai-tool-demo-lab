/* test_temp_sensor.c – Auto-generated Expert Unity Tests */
#include "unity.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // Required for srand and rand, used in source and for deterministic testing

// Define string constants as they were "[STRING REDACTED]" in source
// Assuming standard status strings for temperature monitoring
#define CRITICAL_STATUS_STR "CRITICAL"
#define HOT_STATUS_STR "HOT"
#define COLD_STATUS_STR "COLD"
#define NORMAL_STATUS_STR "NORMAL"

// --- Source under test (forward declarations for internal functions) ---
// These are declared here to ensure Unity can find them,
// but they are NOT redefined or stubbed.
// In a real project, these would typically be in a header file (temp_sensor.h)
// that would be included here. Since no header was provided,
// we forward declare the internal functions.

int read_temperature_raw();
bool validate_temperature_range(float temp_c);
const char* check_temperature_status(float temp_c);
float get_temperature_celsius();

// --- External Function Stubs ---
// raw_to_celsius is the only listed external dependency to stub.
typedef struct {
    float return_value;
    bool was_called;
    uint32_t call_count;
    int last_raw_value; // Capture last parameter passed
} stub_raw_to_celsius_t;

static stub_raw_to_celsius_t stub_raw_to_celsius = {0};

float raw_to_celsius(int raw_value) {
    stub_raw_to_celsius.was_called = true;
    stub_raw_to_celsius.call_count++;
    stub_raw_to_celsius.last_raw_value = raw_value;
    return stub_raw_to_celsius.return_value;
}

// --- Unity Setup and Teardown ---
void setUp(void) {
    // Reset all stub control structures
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
    // No global srand() here; rand() determinism handled per test function.
}

void tearDown(void) {
    // Ensure all stubs are reset after each test
    memset(&stub_raw_to_celsius, 0, sizeof(stub_raw_to_celsius));
}

// --- Tests for read_temperature_raw() ---
// This function internally uses rand(). To make it deterministic for testing,
// we will seed rand() with a known value (srand(1)) within the test function.
// We will then predict the sequence of rand() calls.

void test_read_temperature_raw_deterministic_sequence(void) {
    srand(1); // Seed rand() for a predictable sequence
    // Predict the first output of rand()
    int expected_first_rand_val = rand();
    int expected_first_raw = expected_first_rand_val % 1024;

    // Call the function under test
    int actual_first_raw = read_temperature_raw();

    // Expected: The raw value should match the predicted deterministic sequence
    TEST_ASSERT_EQUAL_INT(expected_first_raw, actual_first_raw);

    // Predict the second output of rand()
    int expected_second_rand_val = rand();
    int expected_second_raw = expected_second_rand_val % 1024;

    // Call the function again
    int actual_second_raw = read_temperature_raw();

    // Expected: The second raw value should also match the predicted sequence
    TEST_ASSERT_EQUAL_INT(expected_second_raw, actual_second_raw);
}

void test_read_temperature_raw_range_check(void) {
    // Even with a deterministic sequence, we should ensure the range is correct.
    // Call several times to cover various potential outputs.
    srand(2); // Use a different seed for variety, still deterministic for this test

    for (int i = 0; i < 100; i++) { // Check 100 different raw values
        int result = read_temperature_raw();
        // Expected: Raw value must be within 0 and 1023 (inclusive)
        TEST_ASSERT_GREATER_OR_EQUAL_INT(0, result);
        TEST_ASSERT_LESS_OR_EQUAL_INT(1023, result);
    }
}

// --- Tests for validate_temperature_range(float temp_c) ---

void test_validate_temperature_range_min_edge_valid(void) {
    // Expected: Temperature exactly at the minimum valid limit (0.0f) should be true
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_min_edge_invalid(void) {
    // Expected: Temperature just below the minimum valid limit (0.0f) should be false
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_max_edge_valid(void) {
    // Expected: Temperature exactly at the maximum valid limit (125.0f) should be true
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_max_edge_invalid(void) {
    // Expected: Temperature just above the maximum valid limit (125.1f) should be false
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_validate_temperature_range_nominal_valid(void) {
    // Expected: A nominal operating temperature (25.0f) should be true
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_extreme_low_invalid(void) {
    // Expected: A very low temperature outside the valid range (0.0f) should be false
    TEST_ASSERT_FALSE(validate_temperature_range(0.0f));
}

void test_validate_temperature_range_extreme_high_invalid(void) {
    // Expected: A very high temperature outside the valid range (200.0f) should be false
    TEST_ASSERT_FALSE(validate_temperature_range(200.0f));
}

// --- Tests for check_temperature_status(float temp_c) ---

void test_check_temperature_status_critical_above_120(void) {
    // Expected: Temperature slightly above 120.0f should return CRITICAL
    TEST_ASSERT_EQUAL_STRING(CRITICAL_STATUS_STR, check_temperature_status(120.1f));
}

void test_check_temperature_status_hot_at_120_edge(void) {
    // Expected: Temperature exactly at 120.0f should be HOT (not CRITICAL, as condition is > 120.0f)
    TEST_ASSERT_EQUAL_STRING(HOT_STATUS_STR, check_temperature_status(120.0f));
}

void test_check_temperature_status_hot_above_85(void) {
    // Expected: Temperature slightly above 85.0f should return HOT
    TEST_ASSERT_EQUAL_STRING(HOT_STATUS_STR, check_temperature_status(85.1f));
}

void test_check_temperature_status_normal_at_85_edge(void) {
    // Expected: Temperature exactly at 85.0f should be NORMAL (not HOT, as condition is > 85.0f)
    TEST_ASSERT_EQUAL_STRING(NORMAL_STATUS_STR, check_temperature_status(85.0f));
}

void test_check_temperature_status_cold_below_neg_10(void) {
    // Expected: Temperature slightly below 0.0f should return COLD
    TEST_ASSERT_EQUAL_STRING(COLD_STATUS_STR, check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_at_neg_10_edge(void) {
    // Expected: Temperature exactly at 0.0f should be NORMAL (not COLD, as condition is < 0.0f)
    TEST_ASSERT_EQUAL_STRING(NORMAL_STATUS_STR, check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_mid_range(void) {
    // Expected: A typical room temperature (25.0f) should return NORMAL
    TEST_ASSERT_EQUAL_STRING(NORMAL_STATUS_STR, check_temperature_status(25.0f));
}

void test_check_temperature_status_normal_low_range(void) {
    // Expected: Temperature at 0.0f, within the normal range, should return NORMAL
    TEST_ASSERT_EQUAL_STRING(NORMAL_STATUS_STR, check_temperature_status(0.0f));
}

void test_check_temperature_status_normal_high_range(void) {
    // Expected: Temperature at 80.0f, within the normal range, should return NORMAL
    TEST_ASSERT_EQUAL_STRING(NORMAL_STATUS_STR, check_temperature_status(80.0f));
}

// --- Tests for get_temperature_celsius() ---
// This function calls read_temperature_raw() (internal) and raw_to_celsius() (external stub).
// To ensure determinism, we control the rand() sequence and stub raw_to_celsius().

void test_get_temperature_celsius_low_raw_conversion(void) {
    srand(1); // Reset rand sequence for predictability
    // Predict the raw value that read_temperature_raw() will return.
    int predicted_raw = rand() % 1024;
    // Configure the stub for raw_to_celsius.
    stub_raw_to_celsius.return_value = 0.0f; // Expect a low Celsius value
    float expected_celsius = stub_raw_to_celsius.return_value;

    // Call the function under test
    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once with the predicted raw value
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(predicted_raw, stub_raw_to_celsius.last_raw_value);
    // Expected: The function should return the value configured in the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_mid_raw_conversion(void) {
    srand(2); // Reset rand sequence with a different seed
    // Predict the raw value. Call rand() once to consume the first value in sequence.
    (void)rand(); // Consume the first random number
    int predicted_raw = rand() % 1024; // This will be the second number in the sequence
    // Configure the stub
    stub_raw_to_celsius.return_value = 25.5f; // Expect a mid-range Celsius value
    float expected_celsius = stub_raw_to_celsius.return_value;

    // Call the function under test
    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once with the predicted raw value
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(predicted_raw, stub_raw_to_celsius.last_raw_value);
    // Expected: The function should return the value configured in the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

void test_get_temperature_celsius_high_raw_conversion(void) {
    srand(3); // Reset rand sequence with yet another seed
    // Predict the raw value. Call rand() twice to consume first two values in sequence.
    (void)rand(); (void)rand();
    int predicted_raw = rand() % 1024; // This will be the third number in the sequence
    // Configure the stub
    stub_raw_to_celsius.return_value = 115.2f; // Expect a high Celsius value
    float expected_celsius = stub_raw_to_celsius.return_value;

    // Call the function under test
    float actual_celsius = get_temperature_celsius();

    // Expected: raw_to_celsius should have been called once with the predicted raw value
    TEST_ASSERT_EQUAL_INT(1, stub_raw_to_celsius.call_count);
    TEST_ASSERT_EQUAL_INT(predicted_raw, stub_raw_to_celsius.last_raw_value);
    // Expected: The function should return the value configured in the stub
    TEST_ASSERT_FLOAT_WITHIN(0.1f, expected_celsius, actual_celsius);
}

// --- Main for Unity Test Runner ---


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_temperature_raw_deterministic_sequence);
    RUN_TEST(test_read_temperature_raw_range_check);
    RUN_TEST(test_validate_temperature_range_min_edge_valid);
    RUN_TEST(test_validate_temperature_range_min_edge_invalid);
    RUN_TEST(test_validate_temperature_range_max_edge_valid);
    RUN_TEST(test_validate_temperature_range_max_edge_invalid);
    RUN_TEST(test_validate_temperature_range_nominal_valid);
    RUN_TEST(test_validate_temperature_range_extreme_low_invalid);
    RUN_TEST(test_validate_temperature_range_extreme_high_invalid);
    RUN_TEST(test_check_temperature_status_critical_above_120);
    RUN_TEST(test_check_temperature_status_hot_at_120_edge);
    RUN_TEST(test_check_temperature_status_hot_above_85);
    RUN_TEST(test_check_temperature_status_normal_at_85_edge);
    RUN_TEST(test_check_temperature_status_cold_below_neg_10);
    RUN_TEST(test_check_temperature_status_normal_at_neg_10_edge);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_low_range);
    RUN_TEST(test_check_temperature_status_normal_high_range);
    RUN_TEST(test_get_temperature_celsius_low_raw_conversion);
    RUN_TEST(test_get_temperature_celsius_mid_raw_conversion);
    RUN_TEST(test_get_temperature_celsius_high_raw_conversion);

    return UNITY_END();
}