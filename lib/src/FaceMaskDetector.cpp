#include "FaceMaskDetector.hpp"

FaceMaskDetector::FaceMaskDetector(const string &prototxt, const string &caffemodel)
{
  // Set GPU mode
  Caffe::set_mode(Caffe::GPU);

  // Set TEST mode
  string model_file = prototxt;
  net_.reset(new Net<float>(model_file, TEST));

  // Get net structure
  string trained_file = caffemodel;
  net_->CopyTrainedLayersFrom(trained_file);

  Blob<float> *input_layer = net_->input_blobs()[0];
  input_geometry_ = Size(input_layer->width(),
                         input_layer->height());
  Blob<float> *output_layer = net_->output_blobs()[0];
}

// Output face mask probability
vector<float> FaceMaskDetector::getMaskProb(const Mat &img)
{
  // Reshape input layer
  num_channels_ = 3;
  Blob<float> *input_layer = net_->input_blobs()[0];
  input_layer->Reshape(1, num_channels_, input_geometry_.height, input_geometry_.width);
  net_->Reshape();

  // Initialize input image
  vector<Mat> input_channels;
  Init_Img(img, &input_channels);

  // Forwarding
  net_->Forward();

  // Get output
  char *query_blob_name = "fc5";
  unsigned int blob_id = get_blob_index(net_, query_blob_name);
  boost::shared_ptr<Blob<float>> blob = net_->blobs()[blob_id];
  unsigned int num_data = blob->count();
  const float *begin = blob->cpu_data();
  const float *end = begin + num_data;

  return vector<float>(begin, end);
}

// Initialize image input to model
void FaceMaskDetector::Init_Img(const Mat &img, std::vector<Mat> *input_channels)
{
  Blob<float> *input_layer = net_->input_blobs()[0];
  int width = input_layer->width();
  int height = input_layer->height();
  int channels = input_layer->channels();
  float *input_data = input_layer->mutable_cpu_data();
  for (int i = 0; i < channels; ++i)
  {
    cv::Mat channel(height, width, CV_32FC1, input_data);
    input_channels->push_back(channel);
    input_data += width * height;
  }

  // Resize input image
  Mat sample;
  resize(img, sample, input_geometry_);
  Mat sample_float;
  sample.convertTo(sample_float, CV_32FC3);

  // Normalize input image
  Mat sample_normalized;
  subtract(sample_float, Scalar(127.5, 127.5, 127.5), sample_normalized);
  split(sample_normalized, *input_channels);
}

// Get blob index according to bloc name
unsigned int FaceMaskDetector::get_blob_index(boost::shared_ptr< Net<float> > &net, char *query_blob_name)
{
  std::string str_query(query_blob_name);
  vector<string> const &blob_names = net->blob_names();
  for (unsigned int i = 0; i != blob_names.size(); ++i)
  {
    if (str_query == blob_names[i])
    {
      return i;
    }
  }

  LOG(FATAL) << "Unknown blob name: " << str_query;
}
