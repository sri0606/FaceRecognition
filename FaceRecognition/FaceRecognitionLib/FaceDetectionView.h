#pragma once

#include "Observer.h"
/**
 * View class for the FaceDetectionView area of the screen.
 */
class FaceDetectionView final : public wxScrolledCanvas, public Observer {
private:
  /*  void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);*/
    void OnPaint(wxPaintEvent& event);
    //void OnTimer(wxTimerEvent& event);

    std::vector<cv::Mat> mDetectedFaces;
public:
    static const int Height = 90;      ///< Height to make this window


    FaceDetectionView(wxFrame* parent);

    void UpdateObserver() override;

    /**
      * Add the face that has been detected
     */
    virtual void AddDetectedFace(cv::Mat faceImage) override;
};
