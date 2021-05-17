project(node_manager)
cmake_minimum_required(VERSION 2.6)

# Target operating system name.
set(CMAKE_SYSTEM_NAME Linux)

#该语句中的VERSION文件不能有换行符
execute_process(COMMAND cat ${PROJECT_SOURCE_DIR}/../VERSION
                OUTPUT_VARIABLE VERSION)

execute_process(COMMAND sh -c "git rev-parse --short HEAD | tr -d '\n'"
                OUTPUT_VARIABLE GIT_BRANCH)
#execute_process(COMMAND git rev-parse --short HEAD
#                COMMAND tr -d '\n'
#                OUTPUT_VARIABLE GIT_BRANCH)

string(TIMESTAMP TIME %y%m%d%H%M%S)
set(VERSION ${VERSION}_${GIT_BRANCH}_${TIME})
set(VERSION_STRING "\"${VERSION}\"")

message(STATUS "VERSION=${VERSION}")

set(IMAGE ${PROJECT_NAME}_v${VERSION})

include (buildEnv.cmake)

set(SDK_LINUX_APP_DIR "${PROJECT_SOURCE_DIR}/../sdk_linux_app")
set(LIB_DIR "${PROJECT_SOURCE_DIR}/../libs/sama5")

aux_source_directory(${PROJECT_SOURCE_DIR}/../src SRC_DIR)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_DIR)
aux_source_directory(${SDK_LINUX_APP_DIR}/util SRC_DIR)

set(SRC_FILES
    ${SRC_DIR}
#    ${SDK_LINUX_APP_DIR}/parson/parson.c
)

include_directories(
    ${PROJECT_SOURCE_DIR}/../inc
    ${PROJECT_SOURCE_DIR}/inc
    ${LIB_DIR}/zlog/include
#    ${SDK_LINUX_APP_DIR}/parson
    ${SDK_LINUX_APP_DIR}/util
)

set(LDFLAGS "-L${LIB_DIR}/zlog")

set(DEFS "-D_GNU_SOURCE")
set(DEFS "-DTARGET_SAMA5")

set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic-errors -Woverlength-strings -g -O2 -std=gnu99")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LDFLAGS} ${DEFS}")

add_executable(node_manager ${SRC_FILES})

target_compile_definitions(node_manager PRIVATE VERSION_STRING=${VERSION_STRING})

target_link_libraries(node_manager zlog)
target_link_libraries(node_manager pthread)

add_custom_target(createImage ALL cp ${PROJECT_NAME} ${IMAGE}
    DEPENDS ${PROJECT_NAME}
    COMMENT "create image"
)
