#include "model.h"
#include "view.h"
#include "my_view.h"
#include "controller.h"
int main()
{
    // Instantiate the model
    Model m;
    
    // Run the model in separate thread
    pthread_t modelThreadId;

    // Create a new thread for the model, pass in the model instance, and run the model in that thread (see model.h for threadEntry function)
    pthread_create(&modelThreadId, nullptr, &Model::threadEntry, &m);

    // Create a controller, pass in our model instance
    Controller c(&m);

    // Create a view, pass in our controller instance, and a MyView instance.
    // View is completely abstracted away for you. You only need to care about MyView
    // for implementing your own rendering and event handling.
    MyView mv(&c);
    View v(&c, &mv);

    // Start rendering loop for the view (this also handles events and rendering ImGui)
    v.Render();

    pthread_join(modelThreadId, nullptr);

}
