cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(client VERSION ${PROJECT_VERSION})

add_executable(client main.cpp)

file(GLOB_RECURSE ENDF6_SRC ${PROJECT_SOURCE_DIR} 
    ui/*.h ui/*.cpp 
    app/*.h app/*.cpp 
    infrastructure/*.h infrastructure/*.cpp 
    Messenger.h Messenger.cpp 
    pch.h 
    ../Common/**/*.h ../Common/**/*.cpp)

add_library(client_lib ${ENDF6_SRC})
find_package(Boost 1.74.0 COMPONENTS program_options regex filesystem REQUIRED )
include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(client client_lib
    ${Boost_LIBRARIES}
)

set_target_properties(client client_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(client
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(client PRIVATE
    -Wall -Wextra -pedantic -Werror
)

target_compile_options(client_lib PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS client RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)