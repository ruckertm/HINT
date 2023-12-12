cmake_minimum_required(VERSION 3.4.1)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wno-dangling-else -Wno-format")
set(CFLAGS "${CFLAGS} -g -Wno-dangling-else -Wno-format")

# The logging library
find_library( # Defines the name of the path variable that stores the
        # location of the NDK library.
        log-lib

        # Specifies the name of the NDK library that
        # CMake needs to locate.
        log)

# the FreeType Library

# include files
include_directories("${PROJECT_SOURCE_DIR}/../../../../../backend")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/freetype")
include_directories("${PROJECT_SOURCE_DIR}/include/freetype/config")
# compiler definitions
add_definitions(-DFT2_BUILD_LIBRARY)
add_definitions("-DFT_CONFIG_MODULES_H=<ftmodule.h>")

# source files
set(FT_SRCS
        freetype/base/ftsystem.c
        freetype/base/ftdebug.c
        freetype/base/ftinit.c
        freetype/base/ftbase.c
        freetype/base/ftbbox.c
        freetype/base/ftbitmap.c
        freetype/base/ftgasp.c
        freetype/base/ftglyph.c
        freetype/base/ftmm.c
        freetype/base/fttype1.c
        freetype/truetype/truetype.c
        freetype/type1/type1.c
        freetype/cff/cff.c
        freetype/cid/type1cid.c
        freetype/sfnt/sfnt.c
        freetype/pshinter/pshinter.c
        freetype/raster/raster.c
        freetype/smooth/smooth.c
        freetype/psaux/psaux.c
        freetype/psnames/psmodule.c)

add_library(freetype STATIC ${FT_SRCS})

# the HINT library
add_library(hintview SHARED
        gl_code.cpp
        rendergl.c
        ${PROJECT_SOURCE_DIR}/../../../../../backend/hfonts.c
        ${PROJECT_SOURCE_DIR}/../../../../../backend/tables.c
        ${PROJECT_SOURCE_DIR}/../../../../../backend/htex.c
        ${PROJECT_SOURCE_DIR}/../../../../../backend/get.c
        ${PROJECT_SOURCE_DIR}/../../../../../backend/hrender.c
        ${PROJECT_SOURCE_DIR}/../../../../../backend/hint.c
        )
target_compile_options(hintview PRIVATE -Wno-dangling-else)

# add lib dependencies
target_link_libraries(hintview
        android
        jnigraphics
        log
        EGL
        GLESv2
        z
        freetype)
