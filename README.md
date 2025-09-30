# uo
simple utils cmd organizer
## functional
create short cmd with arg equals full cmd  
example:  
$uo =main print call
config path + main.ccf -> block <print> -> arg [args] = echo print: arg_1 ->> $print: call  

in file:  
```ccf
<print>
[args] = echo print: arg_1
</print>
```

### step 0 - check software
CMake 3.10+  
git  
GCC/Clang on Linux  
Visual Studio 2022 on Windows  
[ff_lib](https://github.com/opexepc/ff_lib) in system or edit CMakeLists.txt

## Linux
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
cp uo ~/.local/bin/
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
