#include <cstdlib>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */
    return rc::gen::nonEmpty(rc::gen::container<std::string>(
        rc::gen::map(rc::gen::inRange(0, 26), [](int i) { return (char)('a' + i); })
    ));
}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
    std::vector<std::string> strings;
    for (int n : numbers) {
        strings.push_back(std::to_string(n));
    }
    return strings;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
    int argc = 4;
    char* argv[] = {(char*)"./prog", (char*)"25", (char*)"83", (char*)"17"};
    int* ar_out = nullptr;
    int len_out = 0;
    parse_args(argc, argv, &ar_out, &len_out);
    ASSERT_EQ(len_out, 3);
    ASSERT_NE(ar_out, nullptr);
    EXPECT_EQ(ar_out[0], 25);
    EXPECT_EQ(ar_out[1], 83);
    EXPECT_EQ(ar_out[2], 17);
    free(ar_out);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    int argc = 1;
    char* argv[] = {(char*)"./prog"};
    int* ar_out = nullptr;
    int len_out = 0;
    parse_args(argc, argv, &ar_out, &len_out);
    EXPECT_EQ(len_out, 0);
    EXPECT_EQ(ar_out, nullptr);
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              ()
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    auto numbers = *rc::gen::nonEmpty(rc::gen::arbitrary<std::vector<int>>());
    std::vector<std::string> str_numbers = vector_of_ints_to_vector_of_strings(numbers);

    std::vector<char*> argv;
    argv.push_back((char*)"./prog");
    for (auto& s : str_numbers) {
        argv.push_back(const_cast<char*>(s.c_str()));
    }
    int argc = (int)argv.size();

    int* ar_out = nullptr;
    int len_out = 0;
    parse_args(argc, argv.data(), &ar_out, &len_out);

    RC_ASSERT(len_out == (int)numbers.size());
    RC_ASSERT(ar_out != nullptr);
    for (int i = 0; i < len_out; ++i) {
        RC_ASSERT(ar_out[i] == numbers[i]);
    }
    free(ar_out);
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    int argc = 1;
    char* argv[] = {(char*)"./prog"};
    int* ar_out = nullptr;
    int len_out = 0;
    parse_args(argc, argv, &ar_out, &len_out);
    RC_ASSERT(len_out == 0);
    RC_ASSERT(ar_out == nullptr);
}
