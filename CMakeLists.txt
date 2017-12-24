cmake_minimum_required(VERSION 3.8)
project(client)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(lib/googletest-master) #
#include_directories(lib/googletest-master/googletest/include) #
include_directories(lib/googletest-master/googlemock/include) #

set(SOURCE_FILES src/main.cpp src/Board.cpp include/Board.h src/Cell.cpp include/Cell.h include/Player.h src/HumanPlayer.cpp include/HumanPlayer.h src/GameLogic.cpp include/GameLogic.h src/RegularLogic.cpp include/RegularLogic.h src/Game.cpp include/Game.h src/IOEPlayer.cpp include/IOEPlayer.h Tests/BoardClassTest.cpp Tests/RegularLogicTest.cpp Tests/gtest_main.cpp Tests/AIPlayerTest.cpp Tests/CellTest.cpp include/Painter.h src/ConsolePainter.cpp include/ConsolePainter.h  src/Client.cpp include/Client.h src/RemotePlayer.cpp include/RemotePlayer.h)
add_executable(client ${SOURCE_FILES} Tests/BoardClassTest.cpp Tests/RegularLogicTest.cpp Tests/gtest_main.cpp Tests/AIPlayerTest.cpp Tests/CellTest.cpp include/Painter.h)
target_link_libraries(client gtest gtest_main) #