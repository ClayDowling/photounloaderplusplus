# photounloaderplusplus
Copy image and video files from camera media with a graphical interface


## Building

### Requirements

You need the following installed on your system:

1. CMake higher than 3.20
2. A C++ compiler that supports C++20 or higher
3. Qt version 6
4. Windows - Sorry, enumeration of hardware devices is still operating system specific, and I do my photo work on Windows, so I haven't built in support for other operating systems. If you're trying to port this to other systems I'd love to see a PR.

### Building

First, configure with CMake.  I normally build with GCC and GNU Make, so my command looks like this:

    cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH="C:\Qt\6.3.1\mingw_64\lib\cmake" ..

The path added to CMAKE_PREFIX_PATH should be the path to your specific Qt6 installation. I'm running a bit behind current, so your installation might be different.

A note on Qt and CMake: CMake will lead you to believe that an environment variable `Qt6_DIR` can be set which will allow CMake to find your Qt6 installation. This is misleading. It will find that location, but it won't be able to create a successful build configuration. You need to put the path into CMAKE_PREFIX_PATH for build success. Trust me, I lost a couple of days to this peculiar behavior.