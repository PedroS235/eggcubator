#include <Arduino.h>
#include <unity.h>
#include <utils/time_conversions.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_hour_to_millis(void) {
    TEST_ASSERT_EQUAL(3600000, hour_to_millis(1));
    TEST_ASSERT_EQUAL(18000000, hour_to_millis(5));
}

void test_sec_to_millis(void) {
    TEST_ASSERT_EQUAL(1000, sec_to_millis(1));
    TEST_ASSERT_EQUAL(10000, sec_to_millis(10));
}

void setup() {
    delay(2000);

    UNITY_BEGIN();  // IMPORTANT LINE!
    RUN_TEST(test_hour_to_millis);
    RUN_TEST(test_sec_to_millis);
}

uint8_t i = 0;
uint8_t max_blinks = 5;

void loop() {
    delay(500);
    UNITY_END();  // stop unit testing
}
