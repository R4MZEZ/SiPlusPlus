cmake_minimum_required(VERSION 3.10)

project(lab2)
set(SRCDIR src)
set(INCDIR include)
file(GLOB SRCS "${SRCDIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCDIR})
target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
