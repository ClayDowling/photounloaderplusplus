include_directories(../src .)

set(TESTPROJECT test-${PROJECT_NAME})

add_executable(${TESTPROJECT}
    test_destination.cpp
    test_token.cpp
    test_tokenstream.cpp
    test_parser.cpp

    ../src/destination.cpp
    ../src/token.cpp
    ../src/configparser.cpp
)

target_link_libraries(${TESTPROJECT}
    PRIVATE
    Catch2::Catch2WithMain
)

set_property(TARGET ${TESTPROJECT} PROPERTY CXX_STANDARD 20)

catch_discover_tests(${TESTPROJECT})