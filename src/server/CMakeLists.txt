cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(server VERSION ${PROJECT_VERSION})

add_executable(server main.cpp)

file(GLOB_RECURSE ENDF6_SRC ${PROJECT_SOURCE_DIR} 
    ../common/**/*.h ../common/**/*.cpp)

add_library(server_lib ${ENDF6_SRC})

find_package(Boost 1.74.0 COMPONENTS program_options regex filesystem REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(server server_lib proto
    ${Boost_LIBRARIES}
)

set_target_properties(server server_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(server
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(server PRIVATE
    -Wall -Wextra -pedantic -Werror
)

target_compile_options(server_lib PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)