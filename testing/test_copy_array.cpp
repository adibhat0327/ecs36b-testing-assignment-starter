#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4, 5};
    int* copy = copy_array(ar, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(copy[i], ar[i]);
    }
    free(copy);
}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4, 5};
    int* copy = copy_array(ar, 5);
    copy[0] = 99;
    EXPECT_EQ(ar[0], 1);
    free(copy);
}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4, 5};
    int* copy = copy_array(ar, 5);
    EXPECT_NE(copy, ar);
    for (int i = 0; i < 5; ++i) {
        EXPECT_NE(&copy[i], &ar[i]);
    }
    free(copy);
}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    int* copy = copy_array(ar, (int)values.size());
    RC_ASSERT(elements_in_vector_and_array_are_same(values, copy));
    free(copy);
    delete[] ar;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>& values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    int* copy = copy_array(ar, (int)values.size());
    RC_ASSERT(elements_in_vector_and_array_are_same(values, ar));
    free(copy);
    delete[] ar;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>& values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */
    RC_PRE(!values.empty());
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    int* copy = copy_array(ar, (int)values.size());
    RC_ASSERT(copy != ar);
    free(copy);
    delete[] ar;
}



