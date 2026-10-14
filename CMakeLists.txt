# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.10)

# Название вашего проекта
project(Dungeon_Hero)

# Указываем стандарт C++ (C++11 или выше)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем папку с заголовочными файлами (.h)
include_directories(include)

# Собираем все .cpp файлы из папки src в список
file(GLOB SOURCES "src/*.cpp")

# Создаем исполняемый файл с именем dungeon_hero из найденных исходников
add_executable(dungeon_hero ${SOURCES})