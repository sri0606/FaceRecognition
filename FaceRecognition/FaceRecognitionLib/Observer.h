#pragma once
class FaceRecognition;

/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class Observer {
private:
    /// Picture we are observing
    //std::shared_ptr<FaceRecognition> mFaceRecogntion;

protected:
    /// Constructor (protected)
    Observer() {}

public:
    /// Copy constructor (disabled)
    Observer(const Observer&) = delete;

    ~Observer();

    /// Assignment operator
    void operator=(const Observer&) = delete;

    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    //virtual void SetFaceRecognition(std::shared_ptr<Picture> picture);

    /**
     * Get the picture we are observing
     * @return Pointer to picture we are observing
     */
     //std::shared_ptr<Picture> GetPicture() { return mPicture; }
};