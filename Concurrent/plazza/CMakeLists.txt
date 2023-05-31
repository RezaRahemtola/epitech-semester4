cmake_minimum_required(VERSION 3.10)

project(plazza)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_options(-Wall -Wextra -Wpedantic -g3)
else()
    add_compile_options(-O3)
endif()

add_executable(plazza
    include/Pizza.hpp
    include/ISerializable.hpp
    include/PizzaFactory.hpp
    include/MessageQueue.hpp
    include/ThreadPool.hpp
    include/Fork.hpp
    src/main.cpp
    src/Kitchen.cpp src/Kitchen.hpp
    src/configuration/Configuration.cpp src/configuration/Configuration.hpp
    src/reception/Reception.cpp src/reception/Reception.hpp
    src/reception/Shell.cpp src/reception/Shell.hpp
    src/reception/commands/ShellCommand.cpp src/reception/commands/ShellCommand.hpp
    src/reception/commands/StatusCommand.cpp src/reception/commands/StatusCommand.hpp
    src/reception/commands/ExitCommand.cpp src/reception/commands/ExitCommand.hpp
    src/Utils.cpp src/Utils.hpp)
target_link_libraries(plazza PRIVATE pthread rt)
target_include_directories(plazza PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(plazza PRIVATE cxx_std_20)

if (DEFINED ENABLE_TESTS)
    add_executable(tests_plazza
                tests/tests_main.cpp
                include/Pizza.hpp
                include/Kitchen.hpp src/Kitchen.cpp
                include/Thread.hpp include/ThreadPool.hpp
                include/Fork.hpp
                src/configuration/Configuration.cpp src/configuration/Configuration.hpp
                src/reception/Reception.cpp src/reception/Reception.hpp
                src/reception/Shell.cpp src/reception/Shell.hpp
                src/reception/commands/ShellCommand.cpp src/reception/commands/ShellCommand.hpp
                src/reception/commands/StatusCommand.cpp src/reception/commands/StatusCommand.hpp
                src/reception/commands/ExitCommand.cpp src/reception/commands/ExitCommand.hpp
                src/reception/PizzaFactory.hpp
            )
    find_package(Catch2 REQUIRED)
    enable_testing()
    target_link_libraries(tests_plazza PRIVATE Catch2::Catch2)
    target_include_directories(tests_plazza PRIVATE ${Catch2_INCLUDE_DIRS})
    target_include_directories(tests_plazza PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_compile_features(tests_plazza PRIVATE cxx_std_20)
endif ()