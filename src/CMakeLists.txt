add_executable(${PROJECT_NAME}
    configparser.cpp
    destination.cpp
        missingfileclosure.cpp
        filedestinationclosure.cpp
    token.cpp
    main.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} Qt6::Core)