//
// Created by didi on 2020-02-15.
//

#include "face_mask.hpp"
using namespace std;
using namespace cv;


int main(int argc, char **argv) {

  caffe::GlobalInit(&argc, &argv);
  const char *imgpath = argv[1];

  // Configure file path
  const char *xmlConfig = "../../face_mask.xml";
  const char *prototxt;
  const char *caffemodel;

  // Initializing
  FM_RET_CODE init_ret = FM_init(xmlConfig, prototxt, caffemodel);
  if (FM_SUCCESS != init_ret)
  {
    cout << "Failed to initialize!" << endl;
    return init_ret;
  }

  Mat img;
  // Load cropped face image(detected by face detector)
  FM_RET_CODE load_image_ret = FM_loadImage(imgpath, img);
  if (load_image_ret != FM_SUCCESS)
  {
    cout << "Failed to load image: " << imgpath << endl;
    return load_image_ret;
  }

  // Face mask flag: 1-- with face mask, -1-- without face mask
  int mask_flag = 0;
  // Detect face mask
  FM_RET_CODE det_mask_ret = FM_detFaceMask(img, mask_flag);
  if (det_mask_ret != FM_SUCCESS)
  {
    cout << "Failed to detect face mask!" << endl;
    return det_mask_ret;
  }

  // Release space
  FM_RET_CODE rel_ret = FM_Release();
  if (rel_ret != FM_SUCCESS)
  {
    cout << "Failed to release!" << endl;
    return rel_ret;
  }

  // Output detected face mask result
  if (1 == mask_flag)
  {
    cout << "Face mask is detected!" << endl;
  }
  else
  {
    cout << "Face mask is not detected!" << endl;
  }

  return 0;
}
