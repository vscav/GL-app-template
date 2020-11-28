# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (opengl-app-template)

# Get application files
get_filename_component(FILE app.cpp NAME_WE)
file(GLOB HEADER_FILES header/*.hpp)
file(GLOB SRC_FILES src/*.cpp)

# App executable
add_executable(${FILE} ${SRC_FILES} ${HEADER_FILES})
set_property(TARGET ${FILE} PROPERTY CXX_STANDARD 11)
target_compile_options(${FILE} PRIVATE -Wall)

include_directories(lib/glm)
include_directories(lib/glimac/include)

# glfw library
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(${FILE} PRIVATE glfw)

# glew library
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(${FILE} PRIVATE libglew_static)

# glm library
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(${FILE} PRIVATE glm)

# glimac library
add_subdirectory(lib/glimac EXCLUDE_FROM_ALL)
target_link_libraries(${FILE} PRIVATE glimac)

# doxygen (documentation)
add_subdirectory(doc)
