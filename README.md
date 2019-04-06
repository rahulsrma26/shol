# shol

Simple header only library for C++. Containing various useful functions. Like python like print support for conatiners using cout see [std_cout](examples/std_cout.cpp).

I've tried to make it as cross platform as possible. But there is no guarantee. Examples are tested for Windows, MacOX and Linux.

---

## Install

Just copy the headers.

* Copy the [include](include) folder to your build tree and use a C++14 compiler.

---

## Running examples

Examples can be build using [cmake](https://cmake.org/).

* Linux and MacOS (make)
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

* Windows

    Visual Studio 2017 and later can directly open a CMake project. However, if you want to build using Developer Command prompt instead then run:
    ```sh
    mkdir build
    cd build
    cmake ..
    msbuild examples.sln /t:Build /p:Configuration=Release
    ```
---

## More ways to build

Examples can also be build using [ninja](https://ninja-build.org/) across any platform.

* Using ninja
    ```sh
    mkdir build
    cd build
    cmake .. -GNinja
    ninja -v
    ```

* If you want to use mingw (GCC) instead of MSVC under windows then [chocolatey](https://chocolatey.org/) can be used to install dependencies for ninja build.

    ```sh
    choco intall -y mingw ninja cmake
    ```
    After that append cmake install path ("C:\Program Files\CMake\bin") to [Environment Variable](https://helpdeskgeek.com/windows-10/add-windows-path-environment-variable/).
