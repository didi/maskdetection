# maskdetection

## What is maskdetection?

## Requirements
- google/protobuf
- openblas or atlas
- opencv
- cuda/cudnn(if GPU is used)
- Caffe

## Installation
```bash
Clone the repository. We'll call the directory that you cloned as MASK_ROOT.
git clone --
```
```bash
Build Caffe
see:http://caffe.berkeleyvision.org
```
## Usage
### Note: In this part, we assume you are in the directory $MASK_ROOT/

- Install requirements (remember the install path to configure CMakeLists.txt)
- Configure CMakeLists.txt、 test/CMakeLists.txt、 lib/CMakeLists.txt
- Compile
```bash
mkdir build / cd build / cmake .. / make
```
- After compilation, executable files will be generated in directory: build/bin
- Detect the face bounding box, and then expand the bounding box to a certain proportion to get a detected face.
- Run executable files with the detected face to judge if the face is wearing mask.

## Model
- Our model is pretrained by public ResNet50-caffemodel.
- Trained by our collected private data.
- Introduce attention mechanism.
## Note
- Expanding the detected face bounding box is to reduce the impact of detection error.
- We expand each side of the original face bounding box by 40% for mask detection. It can be adjusted according to the actual situation, for example, the dense crowd can appropriately reduce the proportion to fit the actual scene.
