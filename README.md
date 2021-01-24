# Elemental UI

![C++ Builder](https://github.com/Haeri/ElementalUI/workflows/C++%20Builder/badge.svg)
![Version](https://img.shields.io/badge/dynamic/json?url=https://raw.githubusercontent.com/Haeri/ElementalUI/master/vcpkg.json&label=version&query=$['version-string']&color=blue)
[![License](https://img.shields.io/github/license/Haeri/ElementalUI.svg)](https://github.com/Haeri/ElementalUI/blob/master/LICENSE)
![Size](https://img.shields.io/github/languages/code-size/haeri/elementalui)

Portable C++ GUI library.


## Build Requirements
- [CMake 3.16^](https://cmake.org/download/) 
- [Python 3^](https://www.python.org/downloads/)

## Setup

### <img height="14" src="https://image.flaticon.com/icons/svg/888/888882.svg"> Windows
```cmd
git clone https://github.com/Haeri/ElementalUI.git --recursive
cd ElementalUI
./tools/generate_project_win.bat
```
### <img height="16" src="https://image.flaticon.com/icons/svg/226/226772.svg"> Linux
```bash
git clone https://github.com/Haeri/ElementalUI.git --recursive
cd ElementalUI
sudo apt update
sudo apt install -y libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev cmake curl unzip tar
./tools/generate_project_linux.sh
```

### <img height="16" src="https://image.flaticon.com/icons/svg/2/2235.svg"> Mac
```bash
git clone https://github.com/Haeri/ElementalUI.git --recursive
cd ElementalUI
./tools/generate_project_mac.sh
```
