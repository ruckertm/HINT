cmake_minimum_required(VERSION 3.6.0)
project(Android)
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


set(TOP_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../../../../..")
set(FREETYPE_SOURCE_DIR "${TOP_SOURCE_DIR}/external/freetype-2.12.1")
# include files
include_directories("${TOP_SOURCE_DIR}/backend")
include_directories("${FREETYPE_SOURCE_DIR}/include")
include_directories("${FREETYPE_SOURCE_DIR}/include/freetype")
include_directories("${FREETYPE_SOURCE_DIR}/include/freetype/config")
# compiler definitions
add_definitions(-DFT2_BUILD_LIBRARY)
add_definitions("-DFT_CONFIG_MODULES_H=<ftmodule.h>")

# source files
# the FreeType Library
set(FT_SRCS
        ${FREETYPE_SOURCE_DIR}/src/base/ftsystem.c
        ${FREETYPE_SOURCE_DIR}/src/base/ftdebug.c
        ${FREETYPE_SOURCE_DIR}/src/base/ftinit.c
        ${FREETYPE_SOURCE_DIR}/src/base/ftbase.c
        ${FREETYPE_SOURCE_DIR}/src/base/ftbbox.c
        ${FREETYPE_SOURCE_DIR}/src/base/ftbitmap.c
        ${FREETYPE_SOURCE_DIR}/src/base/ftgasp.c
        ${FREETYPE_SOURCE_DIR}/src/base/ftglyph.c
        ${FREETYPE_SOURCE_DIR}/src/base/ftmm.c
        ${FREETYPE_SOURCE_DIR}/src/base/fttype1.c
        ${FREETYPE_SOURCE_DIR}/src/truetype/truetype.c
        ${FREETYPE_SOURCE_DIR}/src/type1/type1.c
        ${FREETYPE_SOURCE_DIR}/src/cff/cff.c
        ${FREETYPE_SOURCE_DIR}/src/cid/type1cid.c
        ${FREETYPE_SOURCE_DIR}/src/sfnt/sfnt.c
        ${FREETYPE_SOURCE_DIR}/src/pshinter/pshinter.c
        ${FREETYPE_SOURCE_DIR}/src/raster/raster.c
        ${FREETYPE_SOURCE_DIR}/src/smooth/smooth.c
        ${FREETYPE_SOURCE_DIR}/src/psaux/psaux.c
        ${FREETYPE_SOURCE_DIR}/src/psnames/psmodule.c
        )

add_library(freetype STATIC ${FT_SRCS})
target_compile_options(freetype  PRIVATE -Wno-shift-negative-value -Wno-empty-body)

# the HINT library
add_library(hintview SHARED
        gl_code.cpp
        rendergl.c
        tables.c
        get.c
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
        z
        freetype)
