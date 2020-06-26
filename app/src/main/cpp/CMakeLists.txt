cmake_minimum_required(VERSION 3.4.1)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wno-dangling-else -Wno-format -DDEBUG")
set(CFLAGS "${CFLAGS} -g -Wno-dangling-else -Wno-format -DDEBUG")

# Import the CMakeLists.txt for the glm library
#add_subdirectory(glm) # if your CMakeLists is at '../cpp'
#add_subdirectory(../src/main/cpp/glm) # if your CMakeLists is at '../app'

find_library( # Defines the name of the path variable that stores the
        # location of the NDK library.
        log-lib

        # Specifies the name of the NDK library that
        # CMake needs to locate.
        log)

add_library(hintview SHARED
        gl_code.cpp
        rendergl.cpp
        stb_image.cpp
        hfonts.c
        hformat.c
        hget.c
        htex.c
        hrender.c
        hint.c
        )
target_compile_options(hintview PRIVATE -Wno-dangling-else)

# add lib dependencies
target_link_libraries(hintview
        android
        jnigraphics
        log
        EGL
        GLESv2
        z)
