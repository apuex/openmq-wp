CMAKE_MINIMUM_REQUIRED(VERSION 3.10.3)
cmake_policy(SET CMP0057 NEW)
cmake_policy(SET CMP0065 NEW)
cmake_policy(SET CMP0091 NEW)

PROJECT(openmq-wp)

SET(CMAKE_CXX_STANDARD 11)

option(ENABLE_TESTS    "Enable building tests." ON)
option(ENABLE_VALGRIND "Enable the valgrind memory checker for the tests." OFF)

if(MSVC)
  SET(CMAKE_CXX_FLAGS "/MD /EHsc")
  ADD_DEFINITIONS(-D_WIN32_WINNT=0x0502)
  ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)
endif()

ADD_DEFINITIONS(-DMSG4R_BIG_ENDIAN)
ADD_DEFINITIONS(-DMSG4R_SIZE_T=uint16_t)

INCLUDE_DIRECTORIES(
  msg4r
  comm-io
  ${CMAKE_INSTALL_PREFIX}/include
)

LINK_DIRECTORIES(
  ${LIBRARY_OUTPUT_PATH}
  ${CMAKE_INSTALL_PREFIX}/lib
)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Threads REQUIRED)
find_package(Boost 1.75.0 REQUIRED COMPONENTS
  date_time
  json
  serialization
  program_options
  log
  unit_test_framework
  )
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif()

if(ENABLE_TESTS)
  include(CTest)
  enable_testing()

  if(ENABLE_VALGRIND)
    find_program(MEMORYCHECK_COMMAND valgrind)
    if("${MEMORYCHECK_COMMAND}" MATCHES "MEMORYCHECK_COMMAND-NOTFOUND")
      message(WARNING "Valgrind couldn't be found.")
      unset(MEMORYCHECK_COMMAND)
    else()
      set(MEMORYCHECK_COMMAND_OPTIONS
        --trace-children=yes
       	--leak-check=full
       	--error-exitcode=1
       	--suppressions=${CMAKE_CURRENT_SOURCE_DIR}/valgrind.supp
      )
    endif()
  endif(ENABLE_VALGRIND)

endif(ENABLE_TESTS)

add_subdirectory(msg4r)
add_subdirectory(comm-io)


