#pragma once
#include "pch.h"

bool CompareImagesByFeatureMatching(const wxBitmap& bitmap1, const wxBitmap& bitmap2, int threshold = 30);
bool CompareImagesByHistogram(const wxBitmap& bitmap1, const wxBitmap& bitmap2, double threshold = 0.2);
