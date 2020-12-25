# Sistem Informasi Mahasiswa (SIMA)
Basic CRUD program written in C++ with .bin file as database.

## Prerequisites
- g++ (built on v9.3.0)
- Linux OS (not cross-platform)


## Build & Run

### With included build script
```bash
# Give current user permission to execute build.sh
chmod u+x build.sh

# Run build.sh, binary file is generated in dist/ directory
./build.sh
```

### Manually using g++
```bash
# Build main.cpp
g++ -o sima main.cpp

# Execute the generated binary file
./sima
```

## What I've Learned From Completing This Assignment
- How to use fstream library to write and read from files
- Got used to pointers
- String data type is not always reliable (it caused a bug which causes me to switch to array of char instead)
- Know the difference between dot operator and arrow operator
