CMAKE_MINIMUM_REQUIRED(VERSION 3.10.3)
cmake_policy(SET CMP0057 NEW)
cmake_policy(SET CMP0065 NEW)
cmake_policy(SET CMP0091 NEW)

PROJECT(openmq-wp)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)

find_program(GIT_COMMAND git)
if ("${GIT_COMMAND}" MATCHES "GIT_COMMAND-NOTFOUND")
  set(PROJECT_VERSION_PATCH 1)
else()
  EXECUTE_PROCESS( COMMAND git -C ${PROJECT_SOURCE_DIR} rev-list --count HEAD OUTPUT_VARIABLE REVISION_NO_RAW)
  string(REGEX REPLACE "[ \t\r\n]" "" PROJECT_VERSION_PATCH "${REVISION_NO_RAW}")
  EXECUTE_PROCESS( COMMAND git log --max-count=1 --pretty="[%ci] - %h %an %s" OUTPUT_VARIABLE REVISION_MSG_RAW)
  string(REGEX REPLACE "[\"\t\r\n]" "" PROJECT_REVISION_MSG "${REVISION_MSG_RAW}")
endif()

set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
message("${PROJECT_NAME}-${PROJECT_VERSION}")
message("${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")
message("PROJECT_REVISION_MSG=${PROJECT_REVISION_MSG}")

SET(CMAKE_CXX_STANDARD 11)

option(ENABLE_TESTS    "Enable building tests." ON)
option(ENABLE_VALGRIND "Enable the valgrind memory checker for the tests." OFF)

if(MSVC)
  if(CMAKE_CL_64)
    set(OS_BIT "win64")
  else()
    set(OS_BIT "win32")
  endif()
  SET(CMAKE_CXX_FLAGS "/MD /EHsc")
  #ADD_DEFINITIONS(-D_WIN32_WINNT=0x0502)
  #ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)
else()
  EXECUTE_PROCESS( COMMAND uname -s COMMAND tr -d '\n' OUTPUT_VARIABLE OSNAME )
  EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE OSARCH )
  set(OS_BIT "${OSNAME}-${OSARCH}")
endif()

INCLUDE_DIRECTORIES(
  msg4r
  comm-io
  ${CMAKE_INSTALL_PREFIX}/include
)

LINK_DIRECTORIES(
  ${LIBRARY_OUTPUT_PATH}
  ${CMAKE_INSTALL_PREFIX}/lib
)

include(CheckIncludeFile)
CHECK_INCLUDE_FILE(stdint.h  HAVE_CSTDINT)
if(HAVE_CSTDINT)
  ADD_DEFINITIONS(-DHAVE_CSTDINT=1)
  MESSAGE("-DHAVE_CSTDINT=1")
endif(HAVE_CSTDINT)

CHECK_INCLUDE_FILE(stdbool.h  HAVE_CSTDBOOL)
if(HAVE_CSTDBOOL)
  ADD_DEFINITIONS(-DHAVE_CSTDBOOL=1)
  MESSAGE("-DHAVE_CSTDBOOL=1")
endif(HAVE_CSTDBOOL)

if(MSVC)
set(Boost_USE_STATIC_LIBS       OFF) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(PThreads4W REQUIRED)
find_package(Boost 1.75.0 REQUIRED COMPONENTS
  date_time
  json
  program_options
  log
  unit_test_framework
  )
else(MSVC)
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Threads REQUIRED)
find_package(Boost 1.75.0 REQUIRED COMPONENTS
  date_time
  json
  program_options
  log
  unit_test_framework
  )
endif(MSVC)

if(Boost_FOUND)
  add_definitions(-DBOOST_CHRONO_VERSION=2)
  add_definitions(-DBOOST_LOG_USE_NATIVE_SYSLOG)
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

add_subdirectory(comm-io)
add_subdirectory(dump-packet)

set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME runtimes)

set(CPACK_PACKAGE_DESCRIPTION "OpenMQ components")
set(CPACK_PACKAGE_VENDOR "Wangxy")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenMQ Wiring Protocol C++ Implementation.")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")

set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}-${OS_BIT}")

if(MSVC)
  set(CMAKE_INSTALL_UCRT_LIBRARIES ON)
  #set(CMAKE_INSTALL_MFC_LIBRARIES ON)
  include (InstallRequiredSystemLibraries)

  set(CPACK_GENERATOR
    WIX
    ZIP
    )

  set(CPACK_WIX_UPGRADE_GUID "0CD5A527-5D82-4E4A-9422-8251DC28E093")
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_VENDOR}/${CPACK_PACKAGE_NAME}")
else()
  set(CPACK_GENERATOR
    TGZ
    )
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_VENDOR}/${CPACK_PACKAGE_NAME}")
endif()

INCLUDE(CPack)

  cpack_add_component(runtimes
    DISPLAY_NAME "Runtime Libraries"
    DESCRIPTION "Supported Runtime Libraries.")

  cpack_add_component(applications
    DEPENDS runtimes
    DISPLAY_NAME "Applications"
    DESCRIPTION "Applications and Utilities.")

  cpack_add_component(admin-tools
    DEPENDS runtimes
    DISPLAY_NAME "Administrative Tools"
    DESCRIPTION "Broker Administrative Tools.")

  cpack_add_component(openmq-broker
    DEPENDS runtimes
    DISPLAY_NAME "Message Broker"
    DESCRIPTION "Open Message Queue Broker.")

  cpack_add_component(openmq-rproxy
    DEPENDS runtimes
    DISPLAY_NAME "Reverse Proxy"
    DESCRIPTION "Reverse Proxy Server for Open Message Queue Broker.")

  cpack_add_component(libraries
    DISABLED
    DEPENDS runtimes
    DISPLAY_NAME "Development Libraries"
    DESCRIPTION "Development Libraries and C/C++ Headers.")

  cpack_add_component(unittests
    DISABLED
    DEPENDS runtimes
    DISPLAY_NAME "Unit Tests"
    DESCRIPTION "Unit Tests.")

