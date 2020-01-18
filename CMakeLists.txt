cmake_minimum_required(VERSION 2.8)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 11)

find_package(glfw3 REQUIRED)
find_package(X11 REQUIRED)
find_package(OpenGL 4.0 REQUIRED)

set(LIBS glfw3 ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread ${ASSIMP_LIBRARY})

include_directories(
    ${GLFW_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}
    )

set(CHAPTERS
    1.getting_started
    )

set(1.getting_started
    1.1.single_triangle
    1.2.triangle_exercise
    1.3.rectangle
    2.1.shader
    2.2.shader_class
    3.1.texture
    )

add_library(STB_IMAGE "src/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

add_library(GLAD "src/glad.c")
set(LIBS ${LIBS} GLAD)

foreach(CHAPTER ${CHAPTERS})
    foreach(DEMO ${${CHAPTER}})
        file(GLOB SOURCE
            "src/${CHAPTER}/${DEMO}/*.h"
            "src/${CHAPTER}/${DEMO}/*.cpp"
            "src/${CHAPTER}/${DEMO}/*.vs"
            "src/${CHAPTER}/${DEMO}/*.fs"
            "src/${CHAPTER}/${DEMO}/*.gs"
            )
        set(NAME "${CHAPTER}__${DEMO}")
        add_executable(${NAME} ${SOURCE})
        target_link_libraries(${NAME} ${LIBS})
        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER}")

        file(GLOB SHADERS
                "src/${CHAPTER}/${DEMO}/*.vs"
                # "src/${CHAPTER}/${DEMO}/*.frag"
                "src/${CHAPTER}/${DEMO}/*.fs"
                "src/${CHAPTER}/${DEMO}/*.gs"
                )
        foreach(SHADER ${SHADERS})
                file(COPY ${SHADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER})
        endforeach(SHADER)
    endforeach(DEMO)
endforeach(CHAPTER)