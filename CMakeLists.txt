cmake_minimum_required(VERSION 3.30)
project( template_OpenGL_engine )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package( OpenGL REQUIRED ) # technically not required for glfw

include_directories(
	./dependencies/glfw/include/
)

set ( ALL_LIBS
	${OPENGL_LIBRARY}
	# OpenGL::GL
	glfw
)


add_executable( enginetest src/main.cpp )
target_link_libraries(enginetest
	${ALL_LIBS}
)

# GLFW
set(GLFW_INSTALL FALSE)

add_subdirectory(./dependencies/glfw/)

# target_link_libraries( enginetest OpenGL::GL)




#include_directories( ${OpenCV_INCLUDE_DIRS} )
