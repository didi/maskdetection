#ifndef FACEMASKDETECTOR_H_
#define FACEMASKDETECTOR_H_

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "caffe/caffe.hpp"

using namespace std;
using namespace cv;
using namespace caffe;

class FaceMaskDetector
{
 public:
  FaceMaskDetector(const string &prototxt, const string &caffemodel);
  // Output face mask probability
  vector<float> getMaskProb(const Mat &img);
  // Initialize image input to model
  void Init_Img(const Mat &img, std::vector<Mat> *input_channels);
  // Get blob index according to bloc name
  unsigned int get_blob_index(boost::shared_ptr< Net<float> > &net, char *query_blob_name);
  Size input_geometry_;

  private:
  boost::shared_ptr< Net<float> > net_;
  int num_channels_;
};
#endif /*FACEMASKDETECTOR_H_*/
