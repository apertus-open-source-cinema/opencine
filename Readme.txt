ATTENTION: The infos from Readme.txt and also from Wiki will be moved to https://wiki.apertus.org/index.php?title=Open_Cine


-----

!!!Placeholder for more sophisticated content, cleanup and structuring will follow

TODO:

 - Move build instructions to BuildInstructions.txt (or similar)
 -

Used frameworks/libs/tools:

 - Qt 5.4 (switched because of several bugs in 5.3)
 - CMake 2.8.12 (at least 2.8 is required)


Preliminary notes:

 - All source code should be placed into "Source" folder. Preliminary content (subject to change):

	"OpenCine" - project which will contain Qt code for GUI and processing logic
	(obsolete atm!)"CinemaDNGDecoder" - dummy project at the moment, plugin, will be implemented if no already available solution is found to decode CinemaDNG (e.g. FFmpeg or similar)

 - CMake will be used for most projects to simplify building on different platforms

 - Get Qt (actual version is 5.3, but 5.4 is considered when released) from http://qt-project.org/downloads

 - Get Cmake from http://www.cmake.org/download/ or install it from repository in Linux

 - To resolve CMake errors like

    -----------------------------------------------------------------------------
      CMake Error at Source/OpenCine/CMakeLists.txt:5 (FIND_PACKAGE):
      By not providing "FindQt5Widgets.cmake" in CMAKE_MODULE_PATH this project
      has asked CMake to find a package configuration file provided by
      "Qt5Widgets", but CMake did not find one.
    -----------------------------------------------------------------------------

   please refer to http://stackoverflow.com/questions/22215900/add-the-installation-prefix-of-qt5widgets-to-cmake-prefix-path

   Short version (temporarily): Set CMAKE_PREFIX_PATH to the folder of Qt e.g. export CMAKE_PREFIX_PATH=/home/<username>/Qt/5.3/gcc_64/
   Short version (permanently): Put e.g. export CMAKE_PREFIX_PATH=/home/<username>/Qt/5.3/gcc_64/ into .profile in home folder

 - Linux build commands (execute in the root of the OpenCine folder):

    mkdir build
    cd build
    cmake ..
    make

   If no errors occured then the executable can be found in /build/bin

 - CMakeLists.txt can be opened directly in QtCreator and build as usual (.pro isn't needed now, maybe it should be deleted later)

 - Disadvantage (at least at the moment): Files in QtCreator have to be created manually or with "File/New File or Project" afterwards "Build/Run Cmake" have to be executed to update the project. If problems occur check the CMakeLists.txt for bugs or things like missing directives for processing of required file extensions.

 - Use "-DCMAKE_BUILD_TYPE=Debug" as CMake argument to get debug symbols

Useful links:

CinemaDNG - http://www.cinema-dng.com/?page_id=26 (specification can be found in Docs/Specifications)

MXF - http://en.wikipedia.org/wiki/Material_Exchange_Format (specification can be found in Docs/Specifications)

MXF SDK - https://github.com/Limecraft/ebu-mxfsdk

Bayer demosaic on GPU - http://graphics.cs.williams.edu/papers/BayerJGT09/

Icon pack(preliminary): http://www.flaticon.com/packs/basic-application

QtRaw - https://github.com/mardy/qtraw (used for references)
