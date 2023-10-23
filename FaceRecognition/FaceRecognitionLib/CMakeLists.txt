project(FaceRecognitionLib)

set(SOURCE_FILES FaceRecognition.cpp FaceRecognition.h MainFrame.h MainFrame.cpp pch.h ids.h FaceRecognitionView.h FaceRecognitionView.cpp Image.h Image.cpp "Item.h" "Item.cpp" "FaceDetectionView.h" "FaceDetectionView.cpp" "Observer.h" "Observer.cpp")
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
set(OpenCV_DIR "C:/Program Files/opencv/build")
find_package(OpenCV REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${OpenCV_LIBS})