## Building (Linux + Windows)

Clone with submodules:

```bash
git clone --recursive https://github.com/yourname/YourProject.git
cd YourProject
```

#### 🐧 Linux
```bash

cmake -B build
cmake --build build
./build/YourProject

Use CC=clang if you prefer Clang:

CC=clang cmake -B build
cmake --build build
```
<br>

#### 🪟 Windows (Visual Studio)
```bash
In a Developer Command Prompt:

cmake -B build
cmake --build build --config Release

Run the exe from:

build/Release/YourProject.exe
```
