cmake_minimum_required(VERSION 3.2)
project(docker_fw)

# Version number
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
string(TIMESTAMP BUILD_ID "%Y%m%d" UTC)

# Directories configuration

# Mesos installation directory
set(MESOS_INSTALL_DIR $ENV{MESOS_INSTALL})
if(NOT MESOS_INSTALL_DIR)
    set(MESOS_INSTALL_DIR /usr/local)
endif(NOT MESOS_INSTALL_DIR)

include_directories(SYSTEM ${MESOS_INSTALL_DIR}/include)
link_directories(${MESOS_INSTALL_DIR}/lib)

set(GEN_DIR ${PROJECT_SOURCE_DIR}/gen)
set(INCLUDES_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROTO_DIR ${PROJECT_SOURCE_DIR}/proto)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

set(CMAKE_PREFIX_PATH /usr/local)

message("Building project `${PROJECT_NAME}`
         from: ${PROJECT_SOURCE_DIR}
         to: ${PROJECT_BINARY_DIR}")

# Configure a header file to pass settings into source code
configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${GEN_DIR}/config.h
)

include_directories(${INCLUDES_DIR}
                    ${GEN_DIR}
                    ${SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Build protocol buffers
#add_custom_command(
#    OUTPUT ${GEN_DIR}/mongo.pb.cc ${GEN_DIR}/mongo.pb.h
#    COMMAND protoc -I=${PROTO_DIR} --cpp_out=${GEN_DIR} ${PROTO_DIR}/mongo.proto
#    DEPENDS ${PROTO_DIR}/mongo.proto
#)

set(SOURCE_FILES ${SOURCE_DIR}/main.cpp
                 ${SOURCE_DIR}/container_scheduler.cpp
)

add_executable(docker_fw ${SOURCE_FILES})
target_link_libraries(docker_fw mesos gtest -lpthread -lm)
