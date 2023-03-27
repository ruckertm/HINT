set(WITH_GTK "0" CACHE STRING "GTK version")

if(WITH_GTK STREQUAL "0")
	message("Build without GTK support")
    add_library(GTK INTERFACE)
elseif(WITH_GTK STREQUAL "2" OR WITH_GTK STREQUAL "3")
	message("Build with GTK${WITH_GTK} support")
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GTK REQUIRED "gtk+-${WITH_GTK}.0" IMPORTED_TARGET GLOBAL)
    add_library(GTK ALIAS PkgConfig::GTK)
else()
	message(FATAL_ERROR "Valid values for WITH_GTK are 0, 2 or 3")
endif()

find_package(GLEW REQUIRED)       # GLEW::GLEW
find_package(glfw3 REQUIRED)      # glfw
find_package(Freetype REQUIRED)   # Freetype::Freetype
find_package(ZLIB)                # ZLIB::ZLIB

file(GLOB HINTVIEW_SRC CONFIGURE_DEPENDS "*.c")
set(HINTVIEW_OBJECT "")
foreach(File IN LISTS HINTVIEW_SRC)
     get_filename_component(FileName ${File} NAME_WE)
     add_library(${FileName} OBJECT ${File})
     list(APPEND HINTVIEW_OBJECT $<TARGET_OBJECTS:${FileName}>)
endforeach()

target_compile_definitions(main PUBLIC WITH_GTK=${WITH_GTK})
target_link_libraries(main PUBLIC GTK)
target_link_libraries(main PUBLIC GLEW::GLEW)
target_link_libraries(renderOGL PUBLIC Freetype::Freetype)
target_link_libraries(renderOGL PUBLIC GLEW::GLEW)
target_link_libraries(hfonts PUBLIC Freetype::Freetype)

add_executable(hintview WIN32 MACOSX_BUNDLE ${HINTVIEW_OBJECT})

target_link_libraries(hintview PRIVATE GTK)
target_link_libraries(hintview PRIVATE GLEW::GLEW)
target_link_libraries(hintview PRIVATE glfw)
target_link_libraries(hintview PRIVATE Freetype::Freetype)
target_link_libraries(hintview PRIVATE ZLIB::ZLIB)

install(TARGETS hintview BUNDLE DESTINATION "/Applications")
install(FILES "../man/hintview.1" TYPE MAN)
