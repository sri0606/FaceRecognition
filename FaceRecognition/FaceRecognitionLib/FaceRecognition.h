#pragma once

# include <iostream>
#include "Item.h"
class Observer;

class FaceRecognition
{	
private:

	//item we want implement face recogniton on
	std::unique_ptr<Item> mItem;

	/// The observers of this picture
	std::vector<Observer*> mObservers;


public:
	void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);
	FaceRecognition();
	void Save(const wxString& filename);
	void Load(const wxString& filename);
	void Clear();
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);
	void UpdateObservers();
	void AddDetectedFaces(cv::Mat faceImage);
};