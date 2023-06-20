set(DUMP_PACKET_SRCS
  dump-packet.hpp
  dump-packet.cpp
)

add_executable(dump-packet ${DUMP_PACKET_SRCS})
set_target_properties(dump-packet PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)
target_link_libraries(dump-packet
  msg4r
  comm-io
  ${Boost_LIBRARIES})

install(TARGETS
    dump-packet 
    CONFIGURATIONS Release
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    COMPONENT libraries)

