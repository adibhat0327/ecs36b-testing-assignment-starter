cmake_minimum_required(VERSION 3.28)
project(SortingTesting)

set(CMAKE_CXX_STANDARD 20)



find_package(Threads REQUIRED) #needed to find google test
include(FetchContent) #so we can pull in google test
FetchContent_Declare( #declare information about google test
        googletest #its variable name
        #its location on the internet
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main #what branch we want
)

set(RC_ENABLE_GTEST ON) # enable Rapid Check's integration with Google Test
FetchContent_Declare( #declare information about where to find rapid check
        rapidcheck #its variable name
        #its location on the internet
        GIT_REPOSITORY https://github.com/emil-e/rapidcheck.git
        GIT_TAG master #what branch we want
)


#download google test if we don't have it
FetchContent_MakeAvailable(googletest)

FetchContent_MakeAvailable(rapidcheck)


add_executable(SortingTesting
        test_swap.cpp
        test_min_index_of_array.cpp
        test_copy_array.cpp test_make_sorted.cpp test_get_sorted.cpp test_parse_args.cpp test_helpers.cpp test_helpers.h)


target_link_libraries(SortingTesting
        PRIVATE
        SortingSrc # our src code we want to test
        rapidcheck_gtest # link in rapid test with the google test integrations
        gtest #link in google test
        gmock #link in google mock
        gtest_main #add this one if you want to use google's basic main
)

target_compile_options(SortingTesting PRIVATE ${CXX_WARNINGS})
