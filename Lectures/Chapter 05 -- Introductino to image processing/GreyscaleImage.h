#ifndef __GreyscaleImage_h
#define __GreyscaleImage_h

class GreyscaleImage
{
public:
    GreyscaleImage();
    ~GreyscaleImage();
    void create(unsigned int aWidth, unsigned int aHeight, unsigned char aDefaultValue = 0);
    unsigned char getPixel(unsigned int i, unsigned int j) const;
    void setPixel(unsigned int i, unsigned int j, unsigned char aValue);
    double aspectRatio() const;

private:
    unsigned int m_width;
    unsigned int m_height;
    unsigned char* m_p_data;
};

#endif
