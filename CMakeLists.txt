cmake_minimum_required(VERSION 3.13)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 11)

find_package(glfw3)
find_package(OpenGL 4.0)

include_directories(
    ${GLFW_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}
    )

add_executable(single_triangle single_triangle.cpp src/glad.c)
target_link_libraries(single_triangle
    glfw
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    )

add_executable(rectangle rectangle.cpp src/glad.c)
target_link_libraries(rectangle
    glfw
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    )

add_executable(triangle_exercise1 triangle_exercise1.cpp src/glad.c)
target_link_libraries(triangle_exercise1
    glfw
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

add_executable(shader shader.cpp src/glad.c)
target_link_libraries(shader
    glfw
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    )

add_executable(texture texture.cpp stb_image.cpp src/glad.c)
target_link_libraries(texture
    glfw
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    )