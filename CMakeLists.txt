cmake_minimum_required(VERSION 2.8.9)

project(server)

include_directories(include)
include_directories(/usr/include/libxml2)

add_executable(${CMAKE_PROJECT_NAME} "server.c" server.c src/request.c include/request.h src/matan.c include/matan.h include/fileWork.h src/fileWork.c include/fileWork.h)
target_link_libraries(${CMAKE_PROJECT_NAME} progbase)
target_link_libraries(${CMAKE_PROJECT_NAME} xml2)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY C_STANDARD 11)
target_link_libraries(${CMAKE_PROJECT_NAME} progbase jansson ssl)

project(client)

include_directories(include)
include_directories(/usr/include/libxml2)

add_executable(${CMAKE_PROJECT_NAME} "client.c" client.c src/request.c include/request.h src/matan.c include/matan.h include/fileWork.h src/fileWork.c include/fileWork.h)
target_link_libraries(${CMAKE_PROJECT_NAME} progbase)
target_link_libraries(${CMAKE_PROJECT_NAME} xml2)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY C_STANDARD 11)
target_link_libraries(${CMAKE_PROJECT_NAME} progbase jansson ssl)