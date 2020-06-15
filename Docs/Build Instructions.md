# Ingredients:

- [Visual Studio 2019 (or newer)](https://visualstudio.microsoft.com/), with C++ compiler installed.
- [Python 3](https://www.python.org/).
- [CMake](https://cmake.org/).
- [zlib](https://zlib.net/).
- [libzip](https://libzip.org/).

# Recipe:

1. Download and build *zlib* - you want to get a static build out of it. The thing's buildable using *CMake*.
2. Download and build *libzip* - you want to get a static build out of it. The thing's buildable using *CMake*.
3. Open the *Project/Stellar Ledger Prosthesis.sln* solution file in *Visual Studio*.
4. Open the *Property Sheet* property sheet.
5. Navigate to the *User Macros* page.
6. Replace all the directory paths present there with correct values. You want "zlibHeadersDirectoryPath" to point at the directory containing *zlib*'s header files; "libzipHeadersDirectoryPath" to point at the directory containing *libzip*'s header files; and so on.
7. Make sure *python.exe* is in your PATH variable.
8. Build the solution.
9. A Python script preparing the final build is executed as a post-build event: it copies all the DLLs and EXEs from the *Build* folder to the *Environment* folder (which it creates if it doesn't exist), then copies some files from the *Docs* folder there.