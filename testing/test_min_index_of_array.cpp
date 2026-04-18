#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"
#include "test_helpers.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */
    int ar[] = {1, 3, 5, 7, 9};
    EXPECT_EQ(min_index_of_array(ar, 5), 0);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */
    int ar[] = {9, 7, 5, 3, 1};
    EXPECT_EQ(min_index_of_array(ar, 5), 4);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */
    int ar[] = {9, 3, 1, 7, 5};
    EXPECT_EQ(min_index_of_array(ar, 5), 2);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */
    int ar[] = {5, 1, 9, 1, 7};
    EXPECT_EQ(min_index_of_array(ar, 5), 1);
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int ar[] = {4, 2, 8, 1, 6};
    int ar_copy[] = {4, 2, 8, 1, 6};
    min_index_of_array(ar, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(ar[i], ar_copy[i]);
    }
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              ()) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
    auto values = *rc::gen::nonEmpty(rc::gen::arbitrary<std::vector<int>>());
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    int idx = min_index_of_array(ar, (int)values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(ar[idx] <= ar[i]);
    }
    delete[] ar;
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              ()) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    auto values = *rc::gen::nonEmpty(rc::gen::arbitrary<std::vector<int>>());
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    min_index_of_array(ar, (int)values.size());
    RC_ASSERT(elements_in_vector_and_array_are_same(values, ar));
    delete[] ar;
}
