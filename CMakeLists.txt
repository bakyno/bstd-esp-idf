IF(COMPONENT_NAME)
    idf_component_register(SRCS "src/*"
                           INCLUDE_DIRS "include")
ELSE()
    cmake_minimum_required(VERSION 3.16.0)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
    project(bstd-esp-idf)
ENDIF()
