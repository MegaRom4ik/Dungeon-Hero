# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.14)

# Название вашего проекта
project(Dungeon_Hero CXX)

# Указываем стандарт C++ (C++14 для совместимости с GoogleTest)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем папку с заголовочными файлами (.h)
include_directories(include)

# Исходные файлы логики игры (без main.cpp)
set(CORE_SOURCES
    src/Player.cpp
    src/Monster.cpp
    src/Battle.cpp
)

# Создаем библиотеку игровой логики
add_library(dungeon_core STATIC ${CORE_SOURCES})
target_include_directories(dungeon_core PUBLIC include)

# Основной исполняемый файл игры (игра собирается и работает как и раньше)
add_executable(dungeon_hero src/main.cpp)
target_link_libraries(dungeon_hero PRIVATE dungeon_core)

# --- Настройка Google Test и модульных тестов ---
# Для Windows: предотвращаем конфликт настроек рантайма MSVC/MinGW
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest/CMakeLists.txt")
    # Используем локальную копию Google Test (работает автономно без интернета)
    add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)
else()
    # Если локальной копии нет, скачиваем из репозитория
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(googletest)
endif()

enable_testing()

# Исходные файлы модульных тестов
set(TEST_SOURCES
    tests/test_Player.cpp
    tests/test_Monster.cpp
    tests/test_Battle.cpp
)

add_executable(dungeon_tests ${TEST_SOURCES})
target_include_directories(dungeon_tests PRIVATE include)
target_link_libraries(dungeon_tests PRIVATE dungeon_core GTest::gtest_main)

# Опция для сбора покрытия кода (Code Coverage)
option(ENABLE_COVERAGE "Enable code coverage testing" ON)
if(ENABLE_COVERAGE AND (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang"))
    target_compile_options(dungeon_core PUBLIC --coverage -O0 -g)
    target_link_options(dungeon_core PUBLIC --coverage)
    target_compile_options(dungeon_tests PRIVATE --coverage -O0 -g)
    target_link_options(dungeon_tests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(dungeon_tests)
