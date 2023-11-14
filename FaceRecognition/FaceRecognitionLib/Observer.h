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
  
    wxPanel* mParentPanel;
protected:
    
    /// Picture we are observing
    std::shared_ptr<FaceRecognition> mFaceRecognition;


public:
    /// Copy constructor (disabled)
    Observer(const Observer&) = delete;

    ~Observer();
    /// Constructor (protected)
    Observer(wxPanel* parent);
    /// Assignment operator
    void operator=(const Observer&) = delete;

    //void OnMouseMove(wxMouseEvent& event);
    //void OnLeftUp(wxMouseEvent& event);
    //void OnLeftDown(wxMouseEvent& event);
    //void OnDoubleClick(wxMouseEvent& event);
    virtual void OnPaint(wxPaintEvent& event)=0;

    virtual void OnImageOpen(wxCommandEvent& event)=0;
    virtual void OnVideoOpen(wxCommandEvent& event) = 0;
    virtual void OnFileSaveAs(wxCommandEvent& event) =0;

    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    virtual void SetFaceRecognition(std::shared_ptr<FaceRecognition> facrec);

    /**
     * Get the picture we are observing
     * @return Pointer to picture we are observing
     */
     std::shared_ptr<FaceRecognition> GetFaceRecognition() { return mFaceRecognition; }

     /**
     * Get the panel the views being painted on
     * @return Pointer to panel
     */
     wxPanel* GetParentPanel() { return mParentPanel; }

};
