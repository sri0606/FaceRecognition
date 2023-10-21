
cmake_minimum_required(VERSION 3.20)
project(FaceRecognition)
set(APPLICATION_LIBRARY FaceRecognitionLib)

set(CMAKE_CXX_STANDARD 17)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
set(wxWidgets_DIR "C:/wxWidgets-3.2.1/lib")
set(CMAKE_PREFIX_PATH "C:/wxWidgets-3.2.1")
find_package(wxWidgets COMPONENTS core base xrc html xml )


# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp FaceRecognitionApp.cpp FaceRecognitionApp.h pch.h )

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
 #       DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)
add_subdirectory(Tests)