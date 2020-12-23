macro(bmllib_add_test TESTNAME)
    # create an exectuable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN})
    # link the Google test infrastructure, mocking library, and a default main fuction to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
endmacro()

bmllib_add_test(firstTest bmlbitutilstests.cc)
add_test(NAME firstTest COMMAND first)