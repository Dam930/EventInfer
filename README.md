# EventInfer

**EventInfer** is a real-time inference engine written entirely in C++ that leverages an event-driven architecture to maximize performance. Designed to handle AI workloads efficiently, it uses multithreading to reduce latency and improve scalability in real-time applications.

## Key Features
- **Event-driven architecture** for efficient inference management.
- **Multithreading support** to maximize performance across CPU cores.
- **Optimized for real-time applications**, minimizing latency.
- **Lightweight and modular**, easy to integrate into existing AI pipelines.

## Purpose
The goal of EventInfer is to provide a fast and lightweight infrastructure for real-time inference tasks, making it ideal for applications real time applications. Unlike proprietary solutions such as **NVIDIA DeepStream**, which is tightly integrated with NVIDIA hardware and ecosystems, **EventInfer** is designed to be flexible and adaptable across various platforms and environments. 

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

## Contributions
Contributions are welcome! Feel free to fork the repository, create issues, or submit pull requests to enhance the project.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.