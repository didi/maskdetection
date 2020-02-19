//
// Created by didi on 2020-02-15.
//

#ifndef FACE_MASK_HPP
#define FACE_MASK_HPP

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "caffe/caffe.hpp"
#include "util/xml/tinyxml/tinyxml.h"
#include "util/xml/tinyxml/tinystr.h"
#include "RetCode.hpp"

using namespace std;
using namespace cv;
using namespace caffe;

// Initialize Face mask detector
FM_RET_CODE FM_init(const char *xmlConfigFile, const char *&prototxt, const char *&model);
// Load cropped face(detected by face detector)
FM_RET_CODE FM_loadImage(const char *imgFile, Mat &img);
// Detect face mask result
FM_RET_CODE FM_detFaceMask(const Mat &image, int &mask_flag );
// Release space
FM_RET_CODE FM_Release();

#endif //FACE_MASK_HPP
