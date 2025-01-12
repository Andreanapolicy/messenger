cmake_minimum_required(VERSION 3.12)

find_package(Protobuf REQUIRED)

set(PROTO_FILES messenger.proto)
set(PROTO_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(proto ${PROTO_SRCS} ${PROTO_HDRS})

execute_process (
    COMMAND bash -c "mkdir -p ${CMAKE_CURRENT_LIST_DIR}/generated"
)

protobuf_generate(
    TARGET 
        proto
    PROTOS
        ${PROTO_FILES}
    LANGUAGE
        cpp
	OUT_VAR
		PROTOBUF_GENERATED_FILES
    PROTOC_OUT_DIR
	    ${CMAKE_CURRENT_LIST_DIR}/generated
)

target_link_libraries(proto PRIVATE ${Protobuf_LIBRARIES})

target_include_directories(proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})