#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    // Initialise GLUT
    glutInit(&argc, argv);
    
    // Create an instance of Window
    Window example_window(200, 200, "Example");
    
    example_window.run();
    
    return (0);
}
