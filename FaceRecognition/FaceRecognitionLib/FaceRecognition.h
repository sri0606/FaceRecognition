#pragma once

# include <iostream>
#include "Item.h"

class FaceRecognition
{
private:

	//item we want implement face recogniton on
	std::shared_ptr<Item> mItem;


public:
	void OnDraw(wxDC* dc);
	FaceRecognition(wxWindow* window, wxFrame* frame);
	FaceRecognition() = delete;
	void Save(const wxString& filename);
	void Load(wxWindow* parent,const wxString& filename);
	void Clear();

};