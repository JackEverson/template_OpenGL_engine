cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project( template_OpenGL_engine )

# set(CMAKE_CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -WX- -std=c++17")
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
	external/
	external/glad-4.6/include/
	external/glfw-3.4/include/
)

add_library(glad external/glad-4.6/src/glad.c) # glad
add_subdirectory(${PROJECT_SOURCE_DIR}/external/glfw-3.4/) # glfw

# configure_file("${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/basic.glsl" 
	# "${CMAKE_CURRENT_BINARY_DIR}/res/shaders/basic.glsl")

file(GLOB res_files "${PROJECT_SOURCE_DIR}/res/*")
add_custom_target(res_files
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
	"${CMAKE_CURRENT_SOURCE_DIR}/res/${CMAKE_BUILD_TYPE}"
	"${CMAKE_CURRENT_BINARY_DIR}/res/${CMAKE_BUILD_TYPE}"
	COMMENT "Copying data"
)
add_dependencies(${PROJECT_NAME} res_files)

# Copy shaders
# file(GLOB shader_files "${PROJECT_SOURCE_DIR}/res/shaders/*.shader")
# add_custom_target(shader_files
# 	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
# 	"${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/"
# 	"${CMAKE_CURRENT_BINARY_DIR}/res/shaders/"
# 	COMMENT "Copying data"
# )

# Copy textures
# file(GLOB texture_files "${PROJECT_SOURCE_DIR}/res/textures/*")
# add_custom_target(texture_files
# 	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
# 	"${CMAKE_CURRENT_SOURCE_DIR}/res/textures/"
# 	"${CMAKE_CURRENT_BINARY_DIR}/res/textures/"
# 	COMMENT "Copying data"
# )




