include_directories(../src .)

set(TESTPROJECT test-${PROJECT_NAME})

add_executable(${TESTPROJECT}
    test_destination.cpp

    ../src/destination.cpp
)

target_link_libraries(${TESTPROJECT}
    PRIVATE
    Catch2::Catch2WithMain
)

set_property(TARGET ${TESTPROJECT} PROPERTY CXX_STANDARD 20)

catch_discover_tests(${TESTPROJECT})