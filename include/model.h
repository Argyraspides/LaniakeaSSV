#pragma once
#include <pthread.h>
#include "model_interface.h"

class Model : public ModelInterface
{
public:
    Model();
    ~Model();
    void run() override; // BEGINS THE MODEL
    
    // Emscripten doesn't support std::thread for multithreading, only C-type pthread's. This will essentially be a pointer
    // to the run() function so we can actually pass it into pthread_create() in main.cpp and run the model in a separate thread.
    static void *threadEntry(void *instance)
    {
        reinterpret_cast<Model *>(instance)->run();
        return nullptr;
    }
};
