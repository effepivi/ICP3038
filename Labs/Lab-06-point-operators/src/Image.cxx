#include "Image.h"

#include <sstream>
#include <stdexcept>      // std::out_of_range


//--------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& anOutputStream, const Image& anImage)
//--------------------------------------------------------------------------
{
    // Output all the rows
    for (unsigned row = 0; row < anImage.getHeight(); ++row)
    {
        // Output all the columns
        for (unsigned col = 0; col < anImage.getWidth(); ++col)
        {
            // Output the corresponding pixel
            anOutputStream << anImage(col, row);

            // Add a space charater if needed
            if (col < anImage.getWidth() - 1)
            {
                anOutputStream << " ";
            }
        }

        // Add a end of line if needed
        if (row < anImage.getHeight() - 1)
        {
            anOutputStream << std::endl;
        }
    }

    // Return the stream
    return anOutputStream;
}


//---------------------------
Image::Image():
//---------------------------
    m_width(0),
    m_height(0),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(true)
//---------------------------
{}


//-------------------------------------------------------
Image::Image(const Image& anImage):
//-------------------------------------------------------
    m_pixel_data(anImage.m_pixel_data),
    m_width(anImage.m_width),
    m_height(anImage.m_height),
    m_min_pixel_value(anImage.m_min_pixel_value),
    m_max_pixel_value(anImage.m_max_pixel_value),
    m_average_pixel_value(anImage.m_average_pixel_value),
    m_stddev_pixel_value(anImage.m_stddev_pixel_value),
    m_stats_up_to_date(anImage.m_stats_up_to_date)
//-------------------------------------------------------
{}


//----------------------------------------------------------------
Image::Image(const float* anImage, size_t aWidth, size_t aHeight):
//----------------------------------------------------------------
    m_pixel_data(anImage, anImage + aWidth * aHeight),
    m_width(aWidth),
    m_height(aHeight),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(false)
//----------------------------------------------------------------
{}


//-----------------------------------------------------------------------------
Image::Image(const std::vector<float>& anImage, size_t aWidth, size_t aHeight):
//-----------------------------------------------------------------------------
    m_pixel_data(anImage),
    m_width(aWidth),
    m_height(aHeight),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(false)
//-----------------------------------------------------------------------------
{}


//-----------------------------------------------------------
Image::Image(float aConstant, size_t aWidth, size_t aHeight):
//-----------------------------------------------------------
    m_pixel_data(aWidth * aHeight, aConstant),
    m_width(aWidth),
    m_height(aHeight),
    m_min_pixel_value(aConstant),
    m_max_pixel_value(aConstant),
    m_average_pixel_value(aConstant),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(true)
//-----------------------------------------------------------
{}


//----------------------------------
Image::Image(const char* aFilename):
//----------------------------------
    m_width(0),
    m_height(0),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(true)
//---------------------------
{
    load(aFilename);
}


//-----------------------------------------
Image::Image(const std::string& aFilename):
//-----------------------------------------
    m_width(0),
    m_height(0),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(true)
//-----------------------------------------
{
    load(aFilename);
}


//------------------------------------------------
Image& Image::operator=(const Image& anInputImage)
//------------------------------------------------
{
    m_pixel_data = anInputImage.m_pixel_data;
    m_width = anInputImage.m_width;
    m_height = anInputImage.m_height;
    m_min_pixel_value = anInputImage.m_min_pixel_value;
    m_max_pixel_value = anInputImage.m_max_pixel_value;
    m_average_pixel_value = anInputImage.m_average_pixel_value;
    m_stddev_pixel_value = anInputImage.m_stddev_pixel_value;
    m_stats_up_to_date = anInputImage.m_stats_up_to_date;

    return *this;
}


//--------------------------------------------
Image& Image::operator=(const char* aFileName)
//--------------------------------------------
{
    load(aFileName);
    return *this;
}


//---------------------------------------------------
Image& Image::operator=(const std::string& aFileName)
//---------------------------------------------------
{
    load(aFileName);
    return *this;
}


//-------------------------------------
void Image::load(const char* aFilename)
//-------------------------------------
{

}


//--------------------------------------------
void Image::load(const std::string& aFilename)
//--------------------------------------------
{

}


//----------------------------------------------------------
const float& Image::operator()(size_t col, size_t row) const
//----------------------------------------------------------
{
    // Check if the coordinates are valid, if not throw an error
    if (col < 0 || col >= m_width || row < 0 || row >= m_height)
    {
        // Format a nice error message
        std::stringstream error_message;
        error_message << "ERROR:" << std::endl;
        error_message << "\tin File:" << __FILE__ << std::endl;
        error_message << "\tin Function:" << __FUNCTION__ << std::endl;
        error_message << "\tat Line:" << __LINE__ << std::endl;
        error_message << "\tMESSAGE: Pixel(" << col << ", " << row << ") does not exist. The image size is: " << m_width << "x" << m_height << std::endl;

        // Throw an exception
        throw std::out_of_range(error_message.str());
    }

    return m_pixel_data[row * m_width + col];
}


//----------------------------------------------
float& Image::operator()(size_t col, size_t row)
//----------------------------------------------
{
    // Check if the coordinates are valid, if not throw an error
    if (col < 0 || col >= m_width || row < 0 || row >= m_height)
    {
        // Format a nice error message
        std::stringstream error_message;
        error_message << "ERROR:" << std::endl;
        error_message << "\tin File:" << __FILE__ << std::endl;
        error_message << "\tin Function:" << __FUNCTION__ << std::endl;
        error_message << "\tat Line:" << __LINE__ << std::endl;
        error_message << "\tMESSAGE: Pixel(" << col << ", " << row << ") does not exist. The image size is: " << m_width << "x" << m_height << std::endl;

        // Throw an exception
        throw std::out_of_range(error_message.str());
    }

    // To be on the safe side, turn the flag off
    m_stats_up_to_date = false;

    return m_pixel_data[row * m_width + col];
}


//----------------------------
size_t Image::getWidth() const
//----------------------------
{
    return m_width;
}


//-----------------------------
size_t Image::getHeight() const
//-----------------------------
{
    return m_height;
}


//-----------------------------------------
const float* Image::getPixelPointer() const
//-----------------------------------------
{
    // There are pixels
    if (m_pixel_data.size() && m_width && m_height)
        return &m_pixel_data[0];
    // There is no pixel
    else
        return 0;
}

//-----------------------------
float* Image::getPixelPointer()
//-----------------------------
{
    // To be on the safe side, turn the flag off
    m_stats_up_to_date = false;

    // There are pixels
    if (m_pixel_data.size() && m_width && m_height)
        return &m_pixel_data[0];
    // There is no pixel
    else
        return 0;
}
