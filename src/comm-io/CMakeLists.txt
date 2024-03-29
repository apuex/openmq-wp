SET(COMM_IO_SRCS
  comm-io.hpp
  comm-io.cpp
  comm-io-codec.hpp
  comm-io-codec.cpp
)

ADD_LIBRARY(comm-io STATIC ${COMM_IO_SRCS})
set_target_properties(comm-io PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install(FILES
  comm-io.hpp
  comm-io-codec.hpp
  DESTINATION include
  CONFIGURATIONS Release
  COMPONENT libraries)

INSTALL(TARGETS
    comm-io
    CONFIGURATIONS Release
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    COMPONENT libraries)

if(ENABLE_TESTS)
  set(unit_tests
    comm-io-fail-test
    comm-io-ipaddress-test
    comm-io-sysmessageid-test
    comm-io-packetheader-test
    comm-io-variant-test
    comm-io-variant-struct-test
  )

foreach(unit_test ${unit_tests})
  add_executable("${unit_test}" "tests/${unit_test}.cpp")
  target_include_directories(${unit_test} PRIVATE ${Boost_INCLUDE_DIRS})
  target_link_libraries(${unit_test}
    comm-io
    ${Boost_LIBRARIES}
    ${Boost_unit_test_framework})
  if(UNIX)
    set_target_properties("${unit_test}" PROPERTIES LINK_FLAGS_RELEASE -s)
  else(UNIX)
  endif(UNIX)

  INSTALL(TARGETS
    "${unit_test}"
    CONFIGURATIONS Release
    RUNTIME DESTINATION bin
    COMPONENT unittests)

  if(ENABLE_VALGRIND)
    if(MEMORYCHECK_COMMAND)
      add_test(NAME "${unit_test}"
        COMMAND "${MEMORYCHECK_COMMAND}"
       	        "${MEMORYCHECK_COMMAND_OPTIONS}"
                "${CMAKE_CURRENT_BINARY_DIR}/${unit_test}"
      )
    else(MEMORYCHECK_COMMAND)
      add_test(NAME "${unit_test}"
        COMMAND "./${unit_test}"
      )
    endif(MEMORYCHECK_COMMAND)
  else(ENABLE_VALGRIND)
    add_test(NAME "${unit_test}"
      COMMAND "./${unit_test}"
    )
  endif(ENABLE_VALGRIND)
endforeach()

endif(ENABLE_TESTS)

