HintView
=========
HintView is a simple Android Viewer for HINT files.
It is using GLES 2.0 to render the HINT files
It uses lots of C to read and layout HINT files
It uses some Java to implement a simple GUI
-------
Copyright 2019 Martin Ruckert


Licensed to the Apache Software Foundation (ASF) under one or more contributor
license agreements.  See the NOTICE file distributed with this work for
additional information regarding copyright ownership.  The ASF licenses this
file to you under the Apache License, Version 2.0 (the "License"); you may not
use this file except in compliance with the License.  You may obtain a copy of
the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
License for the specific language governing permissions and limitations under
the License.

Compile using Android Studio
============================


- install Android Studio [https://developer.android.com/studio/install](https://developer.android.com/studio/install)
- set Android SDK Path correctly (accept Adroid Studio to modify project's local.properties file)
- install NDK and CMake
  - In Android Studio: Tools -> SDK Manager -> SDK Tools -> NDK (Side by side)
  Click 'Show Package Details' and make sure ndk 21.0.6113669 is checked
  - In Android Studio: Tools -> SDK Manager -> SDK Tools -> CMake
- deprecated with Android Studio 4.0: ~~go to Gradle Scripts local.properties, correct ndk.dir and sdk.dir, if there is no ndk.dir add it. Usually the ndk.dir is the sdk.dir appended by `\\ndk-bundle`~~
- File -> Sync Project With Gradle Files
- Run/Debug Configurations select Android App and make sure no errors are given

GLM
---

Download https://github.com/g-truc/glm/releases/tag/0.9.9.8

Move the contained GLM folder (glm in glm) to ~/AppData/Local/Android/SDK/ndk-bundle/toolchains/llvm/prebuilt/windowsx86_64/sysroot/usr/include/glm

- Run

Setup
-----
- copy files from examples/*.hnt to Download Folder on Android Device
(if you can't access the Download Folder, send all files via email and download them on your device): in Android Studio go to Device File Explorer (lower right Border of Android Studio) - look for storage/emulated/0/Download, right click on Download and upload *.hnt files from examples folder
- give app permission to access storage on Android Device


