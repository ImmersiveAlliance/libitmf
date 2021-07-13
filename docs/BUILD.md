# Building libitmf

libitmf can be built for Windows, macOS, and Linux.

## Dependencies  

libitmf requires the following dependencies.  
 * CMake (tested on version 3.18.4 and 3.20)  
 * One of the following C++ Compilers  
   * GCC (tested on 9.3.0)   
   * MSVC (tested on 19.29.30038.1)  
   * AppleClang (tested on 12.0.0.12000032)  
 * Boost (tested on version 1.73) 

## Build Process  

Boost must be installed on the machine before building with CMake. It uses `FindBoost` to locate the Boost installation meaning the `Boost_DIR` and `Boost_INCLUDEDIR` environment variables must be set to the root Boost directory and include directory respectively.

### CMake
To build libitmf using CMake, run `cmake` in the build directory. For example, from the libitmf root this can be done by
```
mkdir build
cd build
cmake ..
cmake build .
```
The core binaries and headers can then be found in `src/libitmf/core`.

### Emscripten

Instructions to install Emscripten can be found [here](https://emscripten.org/docs/getting_started/downloads.html).

Once Emscripten is installed, the build with Emscripten is similar to the CMake above with an extra step using `make`. From the libitmf root, this is done by
```
mkdir build-emscripten
cd build-emscripten
emcmake cmake ..
emmake make
```

The `itmf.js` and `itmf.wasm` files can then be found in the `src/libitmf/javascript/emscripten` directory.

## Tests

libitmf uses GoogleTest for its testing framework. This is installed and added to the build using CMake. Using the CMake flag `-DITMF_TESTS=ON` will build the unit tests written using [GoogleTest](https://github.com/google/googletest). 
```
cmake .. -DITMF_TESTS=ON
```
