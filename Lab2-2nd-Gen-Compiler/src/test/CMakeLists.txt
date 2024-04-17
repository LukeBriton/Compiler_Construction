cmake_minimum_required(VERSION 3.16)
project(lab02)
set(CMAKE_CXX_STANDARD 17)

find_package(FLEX REQUIRED)
if(FLEX_FOUND)
    message("Info: flex found!")
else()
    message("Error: flex not found!")
endif()

# 添加多个包含目录
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include  # 假设你有一个名为 'include' 的目录
    /usr/local/include          # 另一个常用的包含目录
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 设置 Flex 目标，根据你的 Flex 文件名
# FLEX_TARGET(MyScanner lab2-fl.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cpp)

add_compile_options(-pedantic)
# 可选择的 Sanitize 检查（如果需要开启内存检查，取消注释以下两行）
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

# 生成可执行文件，只包括你的 test.cpp 和 Flex 生成的 lex.yy.cpp
add_executable(Compilerlab2
    lex.yy.cpp
    test.cpp
    # ${FLEX_MyScanner_OUTPUTS}
)

# 如果 Flex 使用了特定的库，取消注释并链接 Flex 库
# target_link_libraries(Compilerlab2 ${FLEX_LIBRARIES})
