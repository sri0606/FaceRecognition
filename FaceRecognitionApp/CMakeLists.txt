# CMakeList.txt : CMake project for FaceRecognitionApp, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (FaceRecognitionApp "FaceRecognitionApp.cpp" "FaceRecognitionApp.h" "pch.h" "main.cpp" "FaceRecognitionLib/FaceRecognition.h" "FaceRecognitionLib/FaceRecognition.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FaceRecognitionApp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
