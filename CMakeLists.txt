cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project( template_OpenGL_engine )

# set(CMAKE_CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -WX -std=c++17")
 else()
 	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")
endif()

set(source_dir "${PROJECT_SOURCE_DIR}/src/")
file(GLOB source_files "${source_dir}/*.cpp")
add_executable(${PROJECT_NAME} ${source_files})

set(ext_libs 
	glad
	glfw
)
target_link_libraries(${PROJECT_NAME} PUBLIC ${ext_libs})

include_directories(
	include/
	external/glad-4.6/include/
	external/glfw-3.4/include/
)

# configure_file("${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/basic.glsl" 
	# "${CMAKE_CURRENT_BINARY_DIR}/res/shaders/basic.glsl")


# Copy shaders
file(GLOB shader_files "${PROJECT_SOURCE_DIR}/res/shaders/*.shader")
add_custom_target(shader_files
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
	"${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/"
	"${CMAKE_CURRENT_BINARY_DIR}/res/shaders/"
	COMMENT "Copying data"
)

# glad
add_library(glad external/glad-4.6/src/glad.c)

# glfw
add_subdirectory(${PROJECT_SOURCE_DIR}/external/glfw-3.4/)



