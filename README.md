# libitmf

![Build Status](https://github.com/ImmersiveAlliance/libitmf/tree/main/.github/workflows/ci.yml/badge.svg)

## Description

libitmf is an implementation of an encoder/decoder for the [Immersive Technology Media Format (ITMF) Container Specification](https://www.immersivealliance.org/download/download-itmf/). The implementation attempts to use a simple, object-oriented design to convey the core concepts of the specification. The library compiles to system library files, WASM, and command line tools, allowing usage in many different contexts.

The ITMF Container is a self-contained asset packaging system (i.e., binary and metadata container) that can be used for interchange amongst industry-standard digital content creation tools and distribution of digital assets, including volumetric and ray-traceable media. It is based on the container functionality and file structure of [ORBX](https://docs.otoy.com/StandaloneH_STA/StandaloneManual.htm#StandaloneSTA/TheORBXFileFormat.htm) developed by OTOY Inc.

The Container behaves as a virtual disk system and usually contains a single, high-level XML index file specified by the [ITMF Scene Graph Specification](https://www.immersivealliance.org/download/download-itmf/).

Files using the ITMF Container format are typically denoted by the `.itmf` extension. More information of an ITMF file can be found in [ARCHITECTURE.md](docs/ARCHITECTURE.md).

## Contents
  * [Building](#Building)
  * [Documentation](#Documentation)
  * [Usage](#Usage)
    * [C++ Library](#C-Library)
    * [Javascript and WASM](#Javascript-and-WASM)
    * [Command line tools](#Command-line-tools)
    * [Examples](#Examples)
  * [Support](#Support)
  * [License](#License)

## Building

See [BUILD.md](docs/BUILD.md) for dependencies and details.

## Documentation

For more detailed information about the ITMF Container Format, refer to the complete specification available [here](https://www.immersivealliance.org/download/download-itmf/).

An overview of the architecture for the library can be found in [ARCHITECTURE.md](docs/ARCHITECTURE.md).

## Usage

### C++ Library

The C++ API is formed around the basis of an `ITMFFILE`. This class can be created from scratch or from an existing .itmf file and provides an interface to access and edit elements of ITMF logical units as well as extracting or adding files to the container.

A fuller discussion on the full API can be found on [ARCHITECTURE.md](docs/ARCHITECTURE.md).

#### C++ Encoding API

libitmf offers three static functions to create an `ITMFFILE`: `CreateStreamsAtStart()`, `CreateStreamsAtEnd()`, and `CreateFromConfig()`. `CreateStreamsAtStart` and `CreateStreamsAtEnd` create default ITMF files that only contain non-optional logical units with streams at start and streams at end encoding order respectively. An `ITMFCONFIGURATION` is used to create a ITMF file of a custom configuration allowing for optional logical units to be included in the encoding and, in the near future, compression and encryption. Files can be added to the container using `addFile(std::string filepath)`. 

#### C++ Decoding API

The static function `ReadFile(std::string filepath)` creates the `ITMFFILE` representation from an existing .itmf file that lives on disk. Knowing what files are contained within the file is accomplished using `getFilelist()`. A file that is within the file list can be extracted to disk using `extractFile(std::string filename, std::string destination_path)` or all files can be extracted using `extractAllFiles(std::string destination_path)`.

### Javascript and WASM

libitmf can be built with Emscripten into a Javascript file and WASM module. The `ITMF` module must first be instantiated before encoding or decoding.

The library uses the Emscripten MEMFS file system in which files live in-memory. For more information on the Emscripten File System API can be found on the [Emscripten website](https://emscripten.org/docs/api_reference/Filesystem-API.html).

#### Javascript Encoding API

The Javascript encoding API can be used to create and add files to an ITMF Container. 
The `ITMFEncoder` must first be created before use. By default this creates an empty Streams at Start file. 
In the same manner as the C++ API different configurations can be created by calling `InitStreamsAtStart()`, `InitStreamsAtEnd()` or by using an `ITMFConfiguration` and `InitCustom()`. 
Files can then be added with an `Int8Array` from an `ArrayBuffer` with `AddFile`. Finally, `Write` encodes the ITMF file and saves it to the memory file system which can be accessed with the Emscripten file system API. This process is illustrated in [examples/javascript/encoder.html](examples/javascript/encoder.html).

The full Javascript encoding API can be found at [src/libitmf/javascript/emscripten/itmf_web.idl](src/libitmf/javascript/emscripten/itmf_web.idl).

#### Javascript Decoding API

The Javascript decoding API can be used to decode and extract files from an ITMF using Javascript. The `ITMFDecoder` must first be created before use. .itmf files must be first loaded into an `Int8Array` from an `ArrayBuffer` and passed into `ReadFile()` with a `byte` array. A list of the contained files can be grabbed by first creating an `ITMFString` then passing it into `GetFileList()`. A single file can be extracted and written into the in-memory file system by using `ExtractFile()` and the same goes for all the files using `ExtractAllFiles()`. This process is illustrated in [examples/javascript/decoder.html](examples/javascript/decoder.html).

The full Javascript decoding API can be found at [src/libitmf/javascript/emscripten/itmf_web.idl](src/libitmf/javascript/emscripten/itmf_web.idl).

#### Command line tools

Once the library is built, we have provided an encoder [`ITMFEncoder`](src/libitmf/tools/itmfencoder.cxx) and decoder [`ITMFDecoder`](src/libitmf/tools/itmfdecoder.cxx) example command line tools in the [src/libitmf/tools](src/libitmf/tools) directory.

#### Examples

We have also provided example Javascript code embedded in an HTML, as well as the generated `.wasm` and `.js`, to show how .itmf files can be encoded and decoded in the browser. These can be found in the [examples/javascript](examples/javascript) directory.

### Support

If you encounter any problems while using the library, please create a GitHub issue [here](https://github.com/ImmersiveAlliance/libitmf/issues).

For any other questions and comments, please contact [opensource@immersivealliance.org](mailto:opensource@immersivealliance.org). 

If you would like to contribute, thank you! We are working on defining contribution guidelines. In the meantime, please reach out to us at the above email or open an issue to start a discussion.

### License

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
More information on the license can be found at [LICENSE](LICENSE).