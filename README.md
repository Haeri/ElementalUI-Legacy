# Elemental UI

![C++ Builder](https://github.com/Haeri/ElementalUI/workflows/C++%20Builder/badge.svg)
![Version](https://img.shields.io/badge/dynamic/json?url=https://raw.githubusercontent.com/Haeri/ElementalUI/master/vcpkg.json&label=version&query=$['version-string']&color=blue)
[![License](https://img.shields.io/github/license/Haeri/ElementalUI.svg)](https://github.com/Haeri/ElementalUI/blob/master/LICENSE)
![Size](https://img.shields.io/github/languages/code-size/haeri/elementalui)

Portable C++ GUI library.


## Build Requirements
- [CMake 3.16^](https://cmake.org/download/) 

## Setup

### <img height="14" src="https://cdn-icons-png.flaticon.com/512/220/220215.png"> Windows

```cmd
git clone https://github.com/Haeri/ElementalUI.git --recursive
cd ElementalUI
./scripts/generate_project_win.bat
```
### <img height="18" src="https://cdn-icons-png.flaticon.com/512/226/226772.png"> Linux

```bash
git clone https://github.com/Haeri/ElementalUI.git --recursive
cd ElementalUI
sudo apt update
sudo apt install -y libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev cmake curl unzip tar
./scripts/generate_project_linux.sh
```

### <img height="18" src="https://cdn-icons-png.flaticon.com/512/179/179309.png"> macOS

```bash
git clone https://github.com/Haeri/ElementalUI.git --recursive
cd ElementalUI
./scripts/generate_project_mac.sh
```
