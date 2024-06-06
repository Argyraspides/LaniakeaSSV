# CPP-WASM-TEMPLATE 
## Purpose:
This is a template to quickly get started making applications for the web using C++. WebAssembly is the compilation target, and some neat tools are included including ImGui, SDL2, SDL2-gfx, and Emscripten to help with this.
Build instructions are limited to Linux platforms at the moment, which includes the .vscode folder provided for non-EMCC compiler paths, although with slight tweaking you should be able to get it up and running on both Windows and macOS.

The template includes a simple MVC pattern. Refer to the code comments to understand how the template works in full detail.

## "Prerequisites"
- ### [WebAssembly](https://developer.mozilla.org/en-US/docs/WebAssembly) compatible browser
  - Nearly all modern browsers support WebAssembly. If you want to check if your browser is supported see [this page](https://caniuse.com/wasm).
- ### [SDL2](https://www.libsdl.org/)
  - Already included in this repo. SDL2 is a C Library which provides a low-level interface for multimedia and input functionalities.
- ### [Emscripten](https://emscripten.org/index.html)
  - Already included in this repo. EMscripten is a toolchain used to compile C++ to JS and ultimately [WebAssembly](https://developer.mozilla.org/en-US/docs/WebAssembly) (.wasm).
- ### [ImGui](https://github.com/ocornut/imgui)
  - Already included in this repo. ImGui is a GUI library for C++.
- ### [CMake](https://cmake.org/)
  - A powerful build tool for building C/C++ programs. You must install this yourself.
 
## Building & Running (Debian Linux)
First ensure you have OpenGL, CMake and essential build tools installed by running:
```
sudo apt-get update && sudo apt-get install build-essential
sudo apt install cmake
sudo apt install freeglut3-dev
```
To *just* build, you can run in the ``lib`` folder:
```
./build_local.sh
```

To build **and run** in a *web browser*, simply run in the ``lib`` folder:
```
./run_web.sh
```
To build and run **locally**, i.e. a normal OS window:
```
./release_local.sh
```
To create a debug executable (in the .vscode folder this script is tied to the debug button):
```
./debug_local.sh
```
If you get a permission denied error for running any of the shell scripts, you can simply run:

```
sudo chmod u+x {SCRIPT NAME}.sh
```

