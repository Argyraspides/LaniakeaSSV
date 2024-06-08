##############################################################################################################
# SETUP CMAKE

cmake_minimum_required(VERSION 3.22)
project(Telos)
set(CMAKE_CXX_STANDARD 17)
set(MY_COMPILER "default" CACHE STRING "Choose a compiler: 'emcc', or 'gcc'")

##############################################################################################################
# GRAB ALL SOURCE FILES

# RECURSIVELY OBTAIN ALL SOURCE FILES FOR LANIAKEA
file(GLOB_RECURSE LANIAKEASSV_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# SOURCE FILES FOR IMGUI, SDL2_GFX, AND LANIAKEA
file(GLOB SOURCES 
    ${LANIAKEASSV_SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_sdl2.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_sdl2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_sdlrenderer2.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_sdlrenderer2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_gfx-1.0.4/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_gfx-1.0.4/*.cpp"
)
##############################################################################################################
# ADD SDL2 AS A LIBRARY. IT ALREADY HAS ITS OWN CMAKELISTS.TXT SO WE CAN JUST STRAIGHT UP ADD THE SUBDIRECTORY
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2")


##############################################################################################################
# ADD IMGUI AS A STATIC LIBRARY
add_library(imgui STATIC "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui.cpp")


##############################################################################################################
# ADD SDL2_GFX AS A STATIC LIBRARY AS WELL
file(GLOB SDL2GFX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_gfx-1.0.4/*.cpp")
add_library(SDL2GFX STATIC ${SDL2GFX_SOURCES})


##############################################################################################################
# RECURSIVELY OBTAIN ALL DIRECTORIES THAT HAVE .H FILES FOR THE PROJECT
file(GLOB_RECURSE PROJECT_INCLUDE_DIRS LIST_DIRECTORIES true
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*"  
)

# ONLY KEEP THE PATHS TO THE DIRECTORIES AND NOT FILES THEMSELVES
foreach(header_file IN LISTS PROJECT_INCLUDE_DIRS)
     get_filename_component(dir_path ${header_file} DIRECTORY)
     list(APPEND PROJECT_INCLUDES ${dir_path})
endforeach()

# REMOVE DUPLICATE DIRECTORY PATHS
list(REMOVE_DUPLICATES PROJECT_INCLUDES) 


# LET CMAKE KNOW OF ALL INCLUDE DIRECTORIES FOR SDL2, IMGUI, CURLPP, AND THE PROJECT
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/include"                      # SDL2
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2_gfx-1.0.4"                    # SDL2_GFX
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui"                             # IMGUI
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends"                    # IMGUI BACKENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/examples/libs/emscripten"    # IMGUI EMSCRIPTEN
    ${PROJECT_INCLUDES}                                                 # THE PROJECT ITSELF

    # WHEN WE RECURSIVELY SEARCHED FOR DIRECTORIES INSIDE OF /INCLUDE, THIS 
    # DID NOT INCLUDE THE /INCLUDE DIRECTORY ITSELF. SO WE NEED TO ADD IT MANUALLY
    "${CMAKE_CURRENT_SOURCE_DIR}/include"                               
)



##############################################################################################################
# ADD THE EXECUTABLE
add_executable(${PROJECT_NAME} ${SOURCES}) 


##############################################################################################################
# FIND OPENGL
find_package(OpenGL REQUIRED)

##############################################################################################################
# IF WE ARE BUILDING TO RUN ON A WEB BROWSER, WE NEED TO USE THE EMCC COMPILER.
if(MY_COMPILER STREQUAL "emcc")

    # SET THE COMPILER TO EMCC
    set(CMAKE_CXX_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/lib/emsdk/upstream/emscripten/emcc")
    # SET THE EXECUTABLE SUFFIX TO .JS
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
    # SET THE COMPILER FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FETCH")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s PTHREAD_POOL_SIZE=navigator.hardwareConcurrency")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s TOTAL_MEMORY=512MB")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/Roboto@assets/Roboto")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    
    # include_directories("${CURL_INCLUDE_DIRS}")  # Ensure curl include directory is set
    link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2")

    target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/curl/include")
    target_link_libraries(${PROJECT_NAME} "imgui" "SDL2GFX" "curlpp")

elseif((MY_COMPILER STREQUAL "gcc")) 
    target_link_libraries(${PROJECT_NAME} "SDL2" "SDL2GFX" "imgui" "OpenGL::GL")
endif() 


##############################################################################################################
