project(smartmouse)
cmake_minimum_required(VERSION 3.1)


option(BUILD_SIM "build gazebo simulations" OFF)

if (BUILD_SIM)
  find_package(gazebo REQUIRED)
endif()

list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

if (MSVC)
  set(CMAKE_CXX_FLAGS "/DEBUG /EHsc")
else()
  set(CMAKE_CXX_FLAGS "-g -Winvalid-pch")
endif()

file(GLOB_RECURSE COM_SRC lib/common/*.cpp lib/commanduino/*.cpp)
file(GLOB SIM_SRC sim/*.cpp sim/commands/*.cpp)
file(GLOB CONSOLE_SRC console/*.cpp console/commands/*.cpp)
file(GLOB REAL_SRC lib/real/*.cpp lib/real/commands/*.cpp)

include_directories(build
  lib/commanduino
  lib/common
  lib/common/commands
  ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

SET(SIMS SimSolve
  SimStepSolve)

SET(CONSOLES Solve
  StepSolve
  Animate
  ReadAndPrint)

foreach(MAIN ${CONSOLES})
  add_executable(${MAIN} "console/main/${MAIN}.cpp" ${COM_SRC} ${CONSOLE_SRC})
  target_compile_features(${MAIN} PRIVATE cxx_strong_enums)
  set_target_properties(${MAIN} PROPERTIES COMPILE_FLAGS "-DCONSOLE")
  target_include_directories(${MAIN} PRIVATE console/ console/commands)
endforeach()

if (BUILD_SIM)
  foreach(MAIN ${SIMS})
    add_executable(${MAIN} "sim/main/${MAIN}.cpp" ${COM_SRC} ${SIM_SRC})
    target_compile_features(${MAIN} PRIVATE cxx_strong_enums)
    target_link_libraries(${MAIN} ${GAZEBO_LIBRARIES})
    set_target_properties(${MAIN} PROPERTIES COMPILE_FLAGS "-DSIM -include gazebo_pch.hh")
    target_include_directories(${MAIN} PRIVATE sim/ sim/commands)
  endforeach()
endif()


add_custom_target(serial COMMAND cd ../ && platformio serialports monitor -b 115200)
add_custom_target(upload COMMAND cd ../ && platformio run -v --target upload)

add_custom_target(due COMMAND cd ../ && platformio run -v)

################################
# Testing
################################
if (test)
  add_subdirectory(gtest)

  enable_testing()

  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  add_executable(runConsoleTests test/Test.cpp ${COM_SRC} ${CONSOLE_SRC})
	target_compile_features(runConsoleTests PRIVATE cxx_strong_enums)
  target_include_directories(runConsoleTests PRIVATE console/ console/commands)

  target_link_libraries(runConsoleTests gtest gtest_main)
  set_target_properties(runConsoleTests PROPERTIES COMPILE_FLAGS "-DCONSOLE")

  add_test(all-tests runConsoleTests)
endif()
