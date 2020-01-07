cmake_minimum_required(VERSION 3.4.1)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -Wno-dangling-else -Wno-format")
set(CFLAGS "${CFLAGS} -Wno-dangling-else -Wno-format")

# Import the CMakeLists.txt for the glm library
#add_subdirectory(glm) # if your CMakeLists is at '../cpp'
#add_subdirectory(../src/main/cpp/glm) # if your CMakeLists is at '../app'

find_library( # Defines the name of the path variable that stores the
              # location of the NDK library.
              log-lib

              # Specifies the name of the NDK library that
              # CMake needs to locate.
              log )

add_library(hintview SHARED
            gl_code.cpp
            rendergl.cpp
            stb_image.cpp
            pkfonts.c
            fonts.c
            hinttop.c
            hget.c
            hmem.c
            hformat.c
            hdefaults.c
            htex.c
            hbuildpage.c
            hrender.c
            hbox.c
            hpack.c
            hlinebreak.c
            hlist.c
            hdisplay.c
            harith.c
            hfont.c
            hpos.c
            )
target_compile_options(hintview PRIVATE -Wno-dangling-else )

# add lib dependencies
target_link_libraries(hintview
                      android
                      log
                      EGL
                      GLESv2
                      z)
