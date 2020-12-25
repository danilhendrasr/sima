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
