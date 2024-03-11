cmake_minimum_required(VERSION 3.15)
project(sudoku VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(projectTarget sudoku)
set(testTarget sudoku_test)

find_package(Qt5 REQUIRED COMPONENTS Core Quick)

add_executable(
    ${projectTarget}
    WIN32

    src/qml.qrc
    src/main.cpp

    src/matrix.cpp
    src/matrix.h

    src/matrix_shuffler.cpp
    src/matrix_shuffler.h

    src/matrix_storage.h
    src/matrix_storage.cpp

    src/matrix_item.cpp
    src/matrix_item.h

    src/game_model.h
    src/game_model.cpp
)

target_link_libraries(${projectTarget} PRIVATE Qt5::Core Qt5::Quick)

install(TARGETS ${projectTarget}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
if (WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

add_executable(
    ${testTarget}

    src/matrix.cpp
    src/matrix.h

    src/matrix_item.cpp
    src/matrix_item.h

    src/matrix_shuffler.cpp
    src/matrix_shuffler.h

    src/matrix_storage.h
    src/matrix_storage.cpp

    test/matrix_item_test.cpp
    test/matrix_test.cpp
    test/matrix_storage_test.cpp
)
target_link_libraries(${testTarget} gtest gtest_main)
target_include_directories(${testTarget} PUBLIC src)

if (MSVC)
#    target_compile_options(${projectTarget} PUBLIC /W4 /WX)
#    target_compile_options(${testTarget} PUBLIC /W4 /WX)
else()
    target_compile_options(${projectTarget} PUBLIC -Wall -Wextra -Werror -pedantic)
    target_compile_options(${testTarget} PUBLIC -Wall -Wextra -Werror -pedantic)
endif()
