# CPP-WASM-TEMPLATE 
## Purpose:

This would probably best be suited for buildling single-page applications (SPAs) that run on the web. Check out my physics engine [here](https://gaugamela.me/Telos) as an example for what you can make with this template.

This is a template to quickly get started making applications for the web using C++. Depending on your experience and goals this will save quite a bit of development time. WebAssembly is the compilation target, and some neat tools are included including ImGui, SDL2, SDL2-gfx, and Emscripten to help with this.

Build instructions are limited to Linux platforms at the moment, although with slight tweaking you should be able to get it up and running on both Windows and macOS.

I have included a .vscode folder provided for emcc and gcc compiler paths on Linux-based platforms and some some simple build scripts for running locally, debugging locally, or running for the web.

The template is a simple MVC pattern You can immediately start adding anything to ``my_view.cpp`` in the source folder for rendering and handling user input events. You have full access to the ``SDL_Renderer`` for rendering whatever you want, ``SDL_Event`` for event general event handling and ``ImGuiIO`` for all things ImGui related.

The model, view, and controller all run on separate threads, so it's vital you ensure some sort of thread safety between these components. The view itself is split into two threads: one for rendering and one for handling input events (through ``SDL_Event``)

The controller and model is, of course, completely up to you as to how you implement it as that will be completely dependent on what you want to make. The only thing to note that the ``run`` function in the model is mandatory as it is the function invoked by its thread, and this will be the models ``main`` function, basically.

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

