macro(itmflib_add_test FILENAME SRC)
    # create an exectuable in which the tests will be stored
    add_executable(${FILENAME} ${SRC})
    # link the Google test infrastructure, mocking library, and a default main fuction to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_link_libraries(${FILENAME} gtest gmock gtest_main)
    gtest_discover_tests(${FILENAME})
endmacro()

itmflib_add_test(bmlbitutilstests bmlbitutilstests.cc)