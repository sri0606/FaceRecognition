#include "pch.h"
#include "FaceRecognition.h"
#include <wx/xml/xml.h>
#include <wx/splitter.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/filename.h>
#include "Image.h"
#include "Video.h"
#include "Observer.h"
#include "FaceRecognitionView.h"
#include "../ImageResourcesLib/convertmattowxbmp.h"
#include "../ImageResourcesLib/ImageMatching.h"

using namespace std;

/**
 * FaceRecognition Constructor
 */
FaceRecognition::FaceRecognition()
{

}
	
/**
 * Draw the face rec
 * @param dc The device context to draw on
 */
void FaceRecognition::OnDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Set the background color
    graphics->SetBrush(wxBrush(wxColour(0, 255, 0)));
    graphics->SetPen(*wxTRANSPARENT_PEN);  // Set a transparent pen or remove border
    
    wxFont font(wxSize(0, 20),
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_NORMAL,
        wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);  // Set the font and text color

    if (mItem != nullptr) {
        mItem->Draw(graphics);
    }
}



/**
* Save detected faces
*/
void FaceRecognition::Save(const wxString& folderPath)
{
    wxImage image;
    int i = 1;

    // Create a subfolder in the selected folder
    wxString subfolderName = wxFileName(mItem->GetPath()).GetName();
    wxString subfolderPath = folderPath+"\\"+ subfolderName;
 

    if (!wxFileName::DirExists(subfolderPath) && !wxFileName::Mkdir(subfolderPath, wxS_DIR_DEFAULT)) {
        wxMessageBox("Failed to create the folder.", "Error", wxICON_ERROR | wxOK);
        return;
    }

    for (wxBitmap detectedFace : mDetectedFaces) {
        image = detectedFace.ConvertToImage();

        wxString filename = wxString::Format(L"detected_face_%d.png", i);
        wxString filePath = subfolderPath +"\\" + filename;

        if (!image.SaveFile(filePath, wxBITMAP_TYPE_PNG)) {
            // Handle the error, e.g., show an error message
            wxMessageBox("Failed to save image.", "Error", wxICON_ERROR | wxOK);
            return;
        }
        i++;
    }
    wxMessageBox("Images saved successfully.", "Success", wxICON_INFORMATION | wxOK);
}

void FaceRecognition::LoadImage(FaceRecognitionView* parent,const wxString& filename)
{
	mItem = std::make_unique<Image>(filename,parent,this);
    mItem->Process();
}

void FaceRecognition::LoadVideo(FaceRecognitionView* parent, const wxString& filename)
{
    mItem = std::make_unique<Video>(filename, parent, this);
    mItem->Process();
}

void FaceRecognition::Clear()
{
}

/**
 * Add an observer.
 * @param observer The observer to add
 */
void FaceRecognition::AddObserver(Observer* observer)
{
	mObservers.push_back(observer);
}


/**
 * Remove an observer
 * @param observer The observer to remove
 */
void FaceRecognition::RemoveObserver(Observer* observer)
{
	auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
	if (loc != std::end(mObservers))
	{
		mObservers.erase(loc);
	}
}

/**
 * Update all observers to indicate the picture has changed.
 */
void FaceRecognition::UpdateObservers()
{
	for (auto observer : mObservers)
	{
		observer->UpdateObserver();
	}
}

void FaceRecognition::AddDetectedFace(cv::Mat faceImage)
{
    wxBitmap faceBitmap(faceImage.cols, faceImage.rows, 24);
    ConvertMatBitmapTowxBitmap(faceImage, faceBitmap);
    for (auto detectedFace = mDetectedFaces.rbegin(); detectedFace != mDetectedFaces.rend(); ++detectedFace)
    {
        if (CompareImagesByHistogram(*detectedFace, faceBitmap) || CompareImagesByFeatureMatching(*detectedFace, faceBitmap)) {
            return;
        }
        else {
            continue;
        }
    }
    mDetectedFaces.push_back(faceBitmap);
}

void FaceRecognition::ClearDetectedFaces()
{
    mDetectedFaces.clear();
    //UpdateObservers();
}

std::vector<wxBitmap> FaceRecognition::GetDetectedFaces() {

    return mDetectedFaces;
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void FaceRecognition::Update()
{
    if (mItem!=nullptr)
        mItem->Update();
}