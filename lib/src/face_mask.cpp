//
// Created by didi on 2020-02-15.
//

#include "face_mask.hpp"
#include "FaceMaskDetector.hpp"

FaceMaskDetector *pFaceMaskDetector = NULL;

// Initialize Face mask detector
FM_RET_CODE FM_init(const char *xmlConfigFile, const char *&prototxt, const char *&caffemodel)
{
  // Check input validly
  if (NULL == xmlConfigFile)
  {
    return FM_INIT_ERR;
  }
  // Load xml file
  TiXmlDocument doc(xmlConfigFile);
  bool loadOkay = doc.LoadFile();
  if (true != loadOkay)
  {
    return FM_INIT_ERR;
  }
  // Get root element
  TiXmlElement *root = doc.RootElement();
  if (NULL == root)
  {
    return FM_INIT_ERR;
  }
  TiXmlNode *item = root->FirstChild();
  if (NULL == item)
  {
    return FM_INIT_ERR;
  }
  // Get prototxt
  TiXmlNode *child = item->FirstChild();
  if (NULL == child)
  {
    return FM_INIT_ERR;
  }

  prototxt = child->ToElement()->GetText();
  if (NULL == prototxt)
  {
    return FM_INIT_ERR;
  }

  // Get caffe model
  child = item->IterateChildren(child);
  if (NULL == child)
  {
    return FM_INIT_ERR;
  }
  
  caffemodel = child->ToElement()->GetText();
  if (NULL == caffemodel)
  {
    return FM_INIT_ERR;
  }

  // New face mask detector
  pFaceMaskDetector = new FaceMaskDetector(prototxt, caffemodel);
  if (NULL == pFaceMaskDetector)
  {
    return FM_INIT_ERR;
  }

  return FM_SUCCESS;
}

// Load cropped face(detected by face detector)
FM_RET_CODE FM_loadImage(const char *imgFile, Mat &img)
{
  // Check input validly
  if (NULL == imgFile)
  {
    return FM_LOADIMG_ERR;
  }

  // Read image
  img = imread(imgFile);
  if (!img.data)
  {
    return FM_LOADIMG_ERR;
  }

  return FM_SUCCESS;
}

// Detect face mask result
FM_RET_CODE FM_detFaceMask(const Mat &image, int &mask_flag)
{
  // Check input validly
  if (!image.data)
  {
    return FM_IMG_INVALID;
  }

  // Get output probability from model
  vector<float> prob;
  prob = pFaceMaskDetector->getMaskProb(image);
  if (prob.empty())
  {
    return FM_DETMASK_ERR;
  }

  // Compare probability wit threshold
  float thresh_value = -0.3f;
  if (prob[0] > thresh_value)
  {
    // With face mask
    mask_flag = 1;
  }
  else
  {
    // Without face mask
    mask_flag = -1;
  }

  return FM_SUCCESS;
}

// Release space
FM_RET_CODE FM_Release()
{
  if(NULL != pFaceMaskDetector)
  {
    delete pFaceMaskDetector;
    pFaceMaskDetector = NULL;
  }

  return FM_SUCCESS;
}

