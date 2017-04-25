cmake_minimum_required(VERSION 3.4)

#Configuration parameters of cmake
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set debug profile, also maximum level of debug info g3 and format of debug info to dwarf-4 (requires gdb in version 7)
set(CMAKE_BUILD_TYPE Debug)
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
endif()
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")
endif()

enable_language(CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)


project(Battleships)



set(SOURCE_FILES
   	include/ChoiceStrategy.h
    	include/Computer.h
	include/Coordinates.h
	include/GameLogic.h
	include/GameLogicUserInterface.h
	include/GreedyStrategy.h
	include/Grid.h
	include/GridField.h
	include/Human.h
	include/HumanUserInterface.h
	include/MultiFunnelShip.h
	include/OneFunnelShip.h
	include/Player.h
	include/RandomStrategy.h
	include/Ship.h
	include/ConsoleDisplaying.h
	include/ConsoleInput.h
   	src/ChoiceStrategy.cpp
    	src/Computer.cpp
	src/Coordinates.cpp
	src/GameLogic.cpp
	src/GameLogicUserInterface.cpp
	src/GreedyStrategy.cpp
	src/Grid.cpp
	src/GridField.cpp
	src/Human.cpp
	src/HumanUserInterface.cpp
	src/MultiFunnelShip.cpp
	src/OneFunnelShip.cpp
	src/Player.cpp
	src/RandomStrategy.cpp
	src/Ship.cpp
	src/ConsoleDisplaying.cpp
	src/ConsoleInput.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(Battleships src/main.cpp)
add_library(BattleshipsLib ${SOURCE_FILES})
target_link_libraries(Battleships BattleshipsLib)
#Unit Tests section

# Check if generating Visual Studio 14 2015 project
if(MSVC)
    if(NOT BOOST_ROOT)
        set(BOOST_ROOT "C:/local/boost_1_60_0")
    endif()
    set(Boost_INCLUDE_DIR "${BOOST_ROOT}")
    set(Boost_LIBRARY_DIR "${BOOST_ROOT}/lib32-msvc-14.0")
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)


    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})

else()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
endif()

set(SOURCE_TEST_FILES
    test/master.cpp
    test/BattleshipsTest.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

add_executable (BattleshipsTest ${SOURCE_TEST_FILES})


#link to Boost libraries and targets and dependencies
target_link_libraries (
	BattleshipsTest
	BattleshipsLib
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

	add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
    ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
enable_testing()
add_test(Test BattleshipsTest)
