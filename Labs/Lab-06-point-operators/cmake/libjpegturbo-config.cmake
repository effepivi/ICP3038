set(LIBJPEGTURBO_FOUND TRUE) # auto 
set(LIBJPEGTURBO_ROOT_DIR "c:/libjpeg-turbo64")

find_path(LIBJPEGTURBO_INCLUDE_DIR NAMES jpeglib.h turbojpeg.h PATHS "${LIBJPEGTURBO_ROOT_DIR}/include") 
mark_as_advanced(LIBJPEGTURBO_INCLUDE_DIR) # show entry in cmake-gui

find_library(LIBJPEGTURBO_JPEG_LIBRARY NAMES jpeg.lib PATHS "${LIBJPEGTURBO_ROOT_DIR}/lib") 
mark_as_advanced(LIBJPEGTURBO_JPEG_LIBRARY) # show entry in cmake-gui

find_library(LIBJPEGTURBO_TURBOJPEG_LIBRARY NAMES turbojpeg.lib PATHS "${LIBJPEGTURBO_ROOT_DIR}/lib") 
mark_as_advanced(LIBJPEGTURBO_TURBOJPEG_LIBRARY) # show entry in cmake-gui

# use xxx_INCLUDE_DIRS and xxx_LIBRARIES in CMakeLists.txt
set(LIBJPEGTURBO_INCLUDE_DIRS ${LIBJPEGTURBO_INCLUDE_DIR} )
set(LIBJPEGTURBO_LIBRARIES ${LIBJPEGTURBO_JPEG_LIBRARY} ${LIBJPEGTURBO_TURBOJPEG_LIBRARY} )

message( "libjpegturbo-config.cmake " ${LIBJPEGTURBO_ROOT_DIR})