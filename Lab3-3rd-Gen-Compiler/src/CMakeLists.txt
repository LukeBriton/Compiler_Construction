cmake_minimum_required(VERSION 3.16)
project(lab02)
set(CMAKE_CXX_STANDARD 17)

include(FindFLEX)
include(FindBISON)
if(FLEX_FOUND)
    message("Info: flex found!")
else()
    message("Error: flex not found!")
endif()
if(BISON_FOUND)
    message("Info: bison found!")
else()
    message("Error: bison not found!")
endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

FLEX_TARGET(MyLexer lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
BISON_TARGET(MyParser grammar.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyLexer MyParser)

set(Options
    -pedantic 
    -Wall -Wextra -Wpedantic -Weverything -Werror
    -Wimplicit-fallthrough
    -Wno-c++98-compat -Wno-weak-vtables -Wno-padded -Wno-shadow-field-in-constructor
    -Wno-shadow-uncaptured-local -Wno-shadow -Wno-global-constructors -Wno-exit-time-destructors
    -Wno-switch-default
    -Wno-shadow-field
    -Wno-error=unused-parameter
    -Wno-error=unused-private-field
    -Wno-error=unreachable-code-break
    -Wno-unsafe-buffer-usage

    -Wno-unused-value
    -Wno-unused-parameter

    -Wno-switch-enum
    -Wno-signed-enum-bitfield
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-c++98-c++11-compat-pedantic
    -Wno-c++20-compat
    -Wno-nested-anon-types
    -Wno-gnu-anonymous-struct
    -Wno-missing-prototypes
    -Wno-documentation
    -Wno-documentation-unknown-command
    -Wno-weak-vtables
    -Wno-unused-const-variable
    -Wno-format-nonliteral
    -Wno-global-constructors
    -Wno-exit-time-destructors
    -Wno-padded
)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)
add_library(parserlib # no Werror for ${FLEX_MyLexer_OUTPUTS} ${BISON_MyParser_OUTPUTS}\
    ${FLEX_MyLexer_OUTPUTS} ${BISON_MyParser_OUTPUTS}
)
target_compile_features(parserlib PRIVATE cxx_std_17)
target_compile_options(parserlib PRIVATE -Wall -Wpedantic)
add_executable(Compilerlab3
    main.cpp
    utils.cpp
    CodeGen.cpp
)
target_compile_features(Compilerlab3 PRIVATE cxx_std_17)
target_compile_options(Compilerlab3 PRIVATE ${Options})
target_link_libraries(Compilerlab3 parserlib)
