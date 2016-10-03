#include <cstdlib>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"


//------------------------------------
Window::Window(unsigned short aWidth,
               unsigned short aHeight,
               const char* apTitle):
//------------------------------------
        m_width(aWidth),
        m_height(aHeight),
        m_window_id(0),
        m_title(apTitle)
//------------------------------------
{
    // Do nothing else
}


//-----------------------
void Window::initialise()
//-----------------------
{
    // Create the window
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(m_width, m_height);
	glutCreateWindow(m_title.data());
    
    // Register the callbacks
	glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);
}


//----------------
void Window::run()
//----------------
{
    if (!m_window_id)
    {
        initialise();
    }
    
    glutMainLoop();
}


//----------------------------
void Window::displayCallback()
//----------------------------
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Display here

	glutSwapBuffers();
}


//-------------------------------------------------------------
void Window::keyboardCallback(unsigned char aKey, int x, int y)
//-------------------------------------------------------------
{
    switch (aKey)
    {
    case 27:
    case 'q':
        exit(EXIT_SUCCESS);
        break;
        
    default:
        // Do nothing
        break;
    }
}
