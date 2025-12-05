# Chartastic -  C++ Charting library

### UNI: kpd2136, ru2155, ka3088

Library uses [raylib](https://www.raylib.com/) as the underlying graphics engine and exposes an API for users to plot multiple types of charts.

## Installation

### 1. Setup Raylib
Please refer to the [Raylib build and instillation](https://github.com/raysan5/raylib#build-and-installation) guide for instructions to download raylib on your OS.

### 2. Building Chartastic
```bash
cd build
cmake ..
make
```
Run make to create executables for all demos in the `examples` directory, or to create one for a specific example:
```bash
make bar_example
```
