#ifndef WINDOW_H

#include <string>

class Window
{
public:
    Window(unsigned short aWidth = 480, unsigned short aHeight = 480, const char* apTitle = "");
    
    void initialise();
    
    void run();
    
private:
    static void displayCallback();
    static void keyboardCallback(unsigned char aKey, int x, int y);

    unsigned short m_width;
    unsigned short m_height;
    
    unsigned int m_window_id;
    
    std::string m_title;
};

#endif // WINDOW_H
