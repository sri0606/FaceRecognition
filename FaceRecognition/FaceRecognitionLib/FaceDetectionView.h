#pragma once

#include "Observer.h"
/**
 * View class for the FaceDetectionView area of the screen.
 */
class FaceDetectionView final : public wxScrolledCanvas, public Observer {
private:

     virtual void OnPaint(wxPaintEvent& event) override;

    

public:
    static const int Height = 90;      ///< Height to make this window


    FaceDetectionView(wxFrame* parent);

    void UpdateObserver() override;

    /**
      * Add the face that has been detected
     */
    virtual void AddDetectedFace(cv::Mat faceImage) override;

    virtual void OnFileOpen(wxCommandEvent& event) override;
    virtual void OnFileSaveAs(wxCommandEvent& event) override;
};
