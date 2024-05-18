# Prerequisites
## Install packages
- OpenCV by source code
- nlohmann_json as ubuntu package
- onnxruntime https://medium.com/@massimilianoriva96/onnxruntime-integration-with-ubuntu-and-cmake-5d7af482136a
- xtensor as ubuntu package

# inference-cpp



## Build

```
mkdir build
cd build
cmake ..
make
```

## Run

```
./artificialy_anomaly_detection ../config/run-app.json 
```