# HINT
Sources and Documentation for Viewing HINT files
under various operating systems

## Directories
backend - This directory contains C source files shared
  for all operating systems offering a common API.
  Most importantly, it contains functions for reading
  HINT files, creating an internal representation of pages
  using the datastructures of TeX; breaking Paragraphs into lines
  and building pages. using the algorithms of TeX.

  The rendering of all applications is implemented using OpenGL
  or OpenEGL. For a sample implementation see one of the implementations
  in the following directories. The differences are small.

Android

iOS

MacOS

Linux

Win32
