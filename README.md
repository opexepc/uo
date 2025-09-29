# uo
simple utils cmd organizer
## functional
create short cmd with arg equals full cmd  
example:  
$uo =main print call
config path + main.ccf -> block <print> -> arg [args] = echo print: arg_1 ->> $print: call  

in file:  
"<print>"
[args] = echo print: arg_1
"</print>"  

### step 0 - check software
CMake 3.10+
GCC/Clang on Linux

## Linux

Visual Studio or MinGW on Windows
### step 1 - build lib
```bash
git clone https://github.com/opexepc/uo.git
cd uo
mkdir build && cd build
cmake ..
make
```

### step 2 - clone to bin dir
```bash
cp build/uo ~/.local/bin/
```

## Windows
### step 1 - build lib
```bash
git clone https://github.com/opexepc/uo.git
cd uo
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```
