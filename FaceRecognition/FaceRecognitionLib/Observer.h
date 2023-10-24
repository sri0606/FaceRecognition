#pragma once

#include "FaceRecognition.h"

/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class Observer {
private:
  

protected:
    /// Constructor (protected)
    Observer() {}
    /// Picture we are observing
    std::shared_ptr<FaceRecognition> mFaceRecognition;

public:
    /// Copy constructor (disabled)
    Observer(const Observer&) = delete;

    ~Observer();

    /// Assignment operator
    void operator=(const Observer&) = delete;

    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    virtual void SetFaceRecognition(std::shared_ptr<FaceRecognition> facrec);

    /**
     * Get the picture we are observing
     * @return Pointer to picture we are observing
     */
     std::shared_ptr<FaceRecognition> GetFaceRecognition() { return mFaceRecognition; }

     /**
      * Add the face that has been detected
     */
     virtual void AddDetectedFace(std::shared_ptr<wxImage> faceImage){}
};
