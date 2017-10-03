#include "GreyscaleImage.h"


GreyscaleImage::GreyscaleImage(): // What if I forget the initialisation?
        m_width(0),
        m_height(0),
        m_p_data(0)
{}


GreyscaleImage::~GreyscaleImage()
{
    if (m_p_data) delete [] m_p_data;
}


void GreyscaleImage::create(unsigned int aWidth, unsigned int aHeight, unsigned char aDefaultValue)
{
    m_width = aWidth;
    m_height = aHeight;
    
    if (m_p_data) delete [] m_p_data;
    m_p_data = new unsigned char[m_width * m_height];
    
    unsigned char* p_temp(m_p_data);
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        *p_temp++ = aDefaultValue;
    }
}


unsigned char GreyscaleImage::getPixel(unsigned int i, unsigned int j) const
{
    return (m_p_data[j * m_width + i]);
}


void GreyscaleImage::setPixel(unsigned int i, unsigned int j, unsigned char aValue)
{
    m_p_data[j * m_width + i] = aValue;
}


double GreyscaleImage::aspectRatio() const
{
    return (double(m_width) / double(m_height)); // What is it?
}
