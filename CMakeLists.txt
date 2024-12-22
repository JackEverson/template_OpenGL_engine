cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project( template_OpenGL_engine )

# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")

set(source_dir "${PROJECT_SOURCE_DIR}/src/")
file(GLOB source_files "${source_dir}/*.cpp")
add_executable(${PROJECT_NAME} ${source_files})

set(ext_libs 
	glad
	glfw
)
target_link_libraries(${PROJECT_NAME} PUBLIC ${ext_libs})

include_directories(
	external/glad/include/
	external/glfw/include/
)

# glad
add_library(glad external/glad/src/glad.c)

# glfw
add_subdirectory(${PROJECT_SOURCE_DIR}/external/glfw/)



