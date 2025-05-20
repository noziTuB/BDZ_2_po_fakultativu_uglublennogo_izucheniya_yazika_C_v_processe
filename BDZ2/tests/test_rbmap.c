#include "unity.h"
#include "rbmap.h"
#include <stdlib.h>
#include <string.h>

int int_cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void setUp(void) {}
void tearDown(void) {}

void test_create_map(void) {
    RBMap *map = rbmap_create(int_cmp);
    TEST_ASSERT_NOT_NULL(map);
    rbmap_destroy(map, free);
}

void test_insert_and_get(void) {
    RBMap *map = rbmap_create(int_cmp);
    int *key = malloc(sizeof(int));
    int *val = malloc(sizeof(int));
    *key = 42;
    *val = 100;
    rbmap_insert(map, key, val);

    int query = 42;
    int *found = (int *)rbmap_get(map, &query);
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_INT(100, *found);

    rbmap_destroy(map, free);
}

void test_not_found(void) {
    RBMap *map = rbmap_create(int_cmp);
    int key = 123;
    void *res = rbmap_get(map, &key);
    TEST_ASSERT_NULL(res);
    rbmap_destroy(map, free);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_map);
    RUN_TEST(test_insert_and_get);
    RUN_TEST(test_not_found);
    return UNITY_END();
}
