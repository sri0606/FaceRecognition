
#include "pch.h"
#include "Image.h"
#include <opencv2/opencv.hpp>
#include <wx/splitter.h>

#include "Item.h"
using namespace cv;


/**
 * Image Constructor
 */
Image::Image(wxWindow* parent,const wxString& filename):Item(parent,filename)
{
    this->SetImage(filename);
}

/**
* Process the image
*/
void Image::Process(wxDC* dc)
{
    cv::Mat originalImage = cv::imread(mPath.ToStdString());

    // Convert the OpenCV image to a wxImage
    wxImage wxImg(originalImage.cols, originalImage.rows, originalImage.data, true);
    if (!wxImg.IsOk()) {
        wxLogError("Failed to convert OpenCV image to wxImage.");
        return;
    }

    // Clear the background
    dc->Clear();

    // Draw the image on the DC
    dc->DrawBitmap(wxBitmap(wxImg), 0, 0, false);

}

void Image::Draw(wxDC* dc)
{
    this->Process(dc);
}

void Image::SetImage(const wxString& imagePath)
{
    // Load the image using the provided path
    mImage = LoadImage(imagePath);
}


wxImage Image::LoadImage(const wxString& imagePath)
{
    // Load the image from the provided path
    wxImage img(imagePath, wxBITMAP_TYPE_ANY);

    if (!img.IsOk()) {
        // Handle image loading error
        wxLogError("Failed to load image: %s", imagePath);
    }

    return img;
}
