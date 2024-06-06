#include "model.h"
#include "view.h"
#include "controller.h"

int main()
{
    // Instantiate the physics engine
    Model m;
    
    // Run engine in separate thread
    pthread_t modelThreadId;
    pthread_create(&modelThreadId, nullptr, &Model::threadEntry, &m);

    // Create a controller, pass in our model instance
    Controller c(&m);

    // Create a view, pass in our controller instance
    View v(&c);
    // Start rendering loop for the view
    v.Render();

    pthread_join(modelThreadId, nullptr);

}
