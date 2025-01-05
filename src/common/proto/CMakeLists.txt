cmake_minimum_required(VERSION 3.12)

find_package(Protobuf REQUIRED)

set(PROTO_FILES messenger.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

add_library(proto ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(proto PRIVATE ${Protobuf_LIBRARIES})

target_include_directories(proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})