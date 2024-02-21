cmake_minimum_required(VERSION 3.15)
project(sudoku)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(projectTarget sudoku)
set(testTarget sudoku_test)

add_executable(
    ${projectTarget}
    src/main.cpp 
    src/matrix.cpp 
    src/matrix_item.cpp 
    src/matrix_shuffler.cpp
)

add_executable(
    ${testTarget}
    src/matrix.cpp 
    src/matrix_item.cpp 
    src/matrix_shuffler.cpp
    
    test/matrix_item_test.cpp
    test/matrix_test.cpp
)
target_link_libraries(${testTarget} gtest gtest_main)
target_include_directories(${testTarget} PUBLIC src)

if(MSVC)
    target_compile_options(${projectTarget} PUBLIC /W4 /WX)
    target_compile_options(${testTarget} PUBLIC /W4 /WX)
else()
    target_compile_options(${projectTarget} PUBLIC -Wall -Wextra -Werror -pedantic)
    target_compile_options(${testTarget} PUBLIC -Wall -Wextra -Werror -pedantic)
endif()