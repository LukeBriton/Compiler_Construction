cmake_minimum_required(VERSION 3.16)
project(lab02)
set(CMAKE_CXX_STANDARD 17)
include(FindFLEX)
if(FLEX_FOUND)
    message("Info: flex found!")
else()
    message("Error: flex not found!")
endif()

include_directories(${CMAKE_SOURCE_DIR})

FLEX_TARGET(MyScanner lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
add_compile_options(-pedantic)
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)
add_executable(Compilerlab2
    main.cpp
    parser.cpp
    utils.cpp
    asm_writer.cpp
    ${FLEX_MyScanner_OUTPUTS}
)
# target_link_libraries(Compilerlab2 ${FLEX_LIBRARIES})
target_compile_features(Compilerlab2 PRIVATE cxx_std_14)
