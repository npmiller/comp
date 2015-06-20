cmake_minimum_required(VERSION 3.2)
project("comp")

add_definitions(-Wall -pedantic)

set(CMAKE_C_FLAGS "-Wall -pedantic")

include_directories(include)

add_executable(comp src/comp.c)

# External libraries
target_link_libraries(comp readline)

# Static libraries
target_link_libraries(comp lang)

add_library(lang STATIC 
	src/Parse.c
	src/LinkedList.c
	src/Stack.c
	src/Identifiers.c
	src/Eval.c
	src/Vars.c
	src/BalancedBinaryTree.c
	src/Type.c
	src/stdlib/calc.c
	src/stdlib/ctrl.c
	src/stdlib/io.c
	src/stdlib/string.c
)
