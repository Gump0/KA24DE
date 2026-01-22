# __KA24DE__
<p align="center">
  <img src="/documentation/KA24DE-logo.png" width="550">
</p>

<br>

## __Features__
+ Extendable ECS system
+ Input handling
+ 2D Sprite rendering
+ 2D __AABB__ collision
+ Abstracted user scripting layer

<p>
  <img src="/documentation/user-input.gif" width="400">
</p>

<p>
  <img src="/documentation/collision.gif" width="400">
</p>

## __Building // Running the Project__ (Linux + Windows)

#### __Prerequisites__

>[!WARNING]
>This project requires the following prerequisites.

```bash
cmake, clang (or c++ compiler of your choice), SDL3.
```
And any SDL3 [dependencies](https://wiki.libsdl.org/SDL3/README-linux).

Clone with submodules:

```bash
git clone https://github.com/Gump0/KA24DE.git   # clone repo
git submodule update --init --recursive         # grab dependencies
cd KA24DE/                                      # go into project folder :)
```

#### __Linux__
```bash

cmake -B build
cmake --build build
./build/YourProject

# Use CC=clang if you prefer Clang:

CC=clang cmake -B build
cmake --build build
```
<br>
    
```bash
# or run my bash script that compiles and runs the project for you.
sudo chmod +x build.sh      # trust me bro
./build.sh
```

#### __Windows__
```bash
#In a Developer Command Prompt:
cmake -B build
cmake --build build --config Release

#Run the exe from:
build/KA24DE.exe
```
