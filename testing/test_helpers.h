#ifndef TESTINGANDDEBUGGING_TEST_HELPERS_H
#define TESTINGANDDEBUGGING_TEST_HELPERS_H
/* Put any extra functions you use to help you out with testing here.
 *
 */
#include <vector>
#include <algorithm>


template <typename T>
void copy_vector_to_array(const std::vector<T>& vector_values, T* array_values) {
    /* Copy the elements from vector_values into array values
     * space for array_values needs to already be allocated
     */
    std::copy(vector_values.cbegin(), vector_values.cend(), array_values);
}

template <typename T>
bool elements_in_vector_and_array_are_same(const std::vector<T>& vector_values, const T* array_values) {
    /* check that the elements in vector_values are the same as those in array_values
     * array_values needs to have the same length as vector_values
     */

    return std::equal(vector_values.cbegin(), vector_values.cend(), array_values);
}



#endif //TESTINGANDDEBUGGING_TEST_HELPERS_H
