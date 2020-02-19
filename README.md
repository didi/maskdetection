# maskdetection

## What is maskdetection?
To further help combat the coronavirus, Didi Chuxing decides to open up its face mask detection technology to the public for free. Developed by DiDi AI team, the mask detection technology is based on DFS face detection algorithm and the face attributes recognition algorithm DiDi employs on its platform. 
The model has overcome several difficulties like complex lighting changes in a day, face pose variety, face scales, etc. It uses weighted loss function and data augmentation methods to deal with different mask types and uneven mask data during the day and the night. 

The system can identify non-mask drivers using their uploaded images with 99.5 per cent accuracy, and achieves 98 per cent accuracy during DiDi’s spot inspection with in-vehicle cameras. The model was trained on a dataset of 200,000 faces to ensure its robustness. 

This quick detection system can be widely used in travel scenes, with mobile phone photos, surveillance images etc., and is able to work round the clock.

## Requirements
- google/protobuf
- openblas or atlas
- opencv
- cuda/cudnn(if GPU is used)
- Caffe

## Installation
- Clone the repository. We'll call the directory that you cloned as MASK_ROOT.
```bash
git clone --
```
- Build Caffe,see:http://caffe.berkeleyvision.org

## Usage
### Note: In this part, we assume you are in the directory $MASK_ROOT/

- Install requirements (remember the install path to configure CMakeLists.txt)
- Configure CMakeLists.txt、 test/CMakeLists.txt、 lib/CMakeLists.txt
- Compile
```bash
mkdir build/ 
cd build/
cmake ../
make
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
