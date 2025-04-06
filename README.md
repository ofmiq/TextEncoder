# TextEncoder

TextEncoder is a simple desktop application designed to encrypt and decrypt text using basic ciphers. The application provides a simple user-friendly interface written in QT, the ability to use 5 different ciphers and the ability to load text directly from a file.

## Features

* Encrypt and decrypt text using multiple classical ciphers.
* Supports direct text input and output display.
* Load input text from files (`.txt`).
* Save output results to files (`.txt`).
* Key generation assistance for applicable ciphers.
* User-friendly interface built with Qt.

## Supported Ciphers

TextEncoder currently supports the following algorithms:
* Caesar Cipher
* Atbash Cipher
* Vigenère Cipher
* XOR Cipher
* Playfair Cipher

## Installation

### Using Prebuilt Release

1.  Download the latest release from the [Releases](https://github.com/ofmiq/TextEncoder/releases/) page. 
2.  Extract the archive.
3.  Run `TextEncoder.exe`.

## Build Steps

Follow these steps to build and run the project from source.

### 1. Install Dependencies

Make sure you have the following installed:

* Qt (e.g., Qt 6.x or compatible version) with MinGW 64-bit (or your chosen compiler/kit like MSVC).
* CMake (e.g., 3.16+ or compatible).
* A C++ compiler compatible with your Qt kit (e.g., MinGW GCC, MSVC, Clang).
* `windeployqt` tool (typically included with Qt installation).

### 2. Configure and Build the Project

1.  Clone the repository:
    ```sh
    git clone https://github.com/ofmiq/TextEncoder.git
    cd TextEncoder
    ```

2.  Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3.  Run CMake to generate the build files (adjust paths and generator as needed):

    ```sh
    cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/path/to/Qt/6.x.x/mingw_64" -DCMAKE_C_COMPILER="C:/path/to/mingw64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/path/to/mingw64/bin/g++.exe"
    ```

4.  Compile the project:

    *Using MinGW Makefiles:*
    ```sh
    mingw32-make
    ```
    *Using other generators (like Visual Studio or Ninja):*
    ```sh
    cmake --build . --config Release
    ```

### 3. Deploy the Executable (Windows Example)

After a successful build, navigate to the directory containing the built `TextEncoder.exe`. Run `windeployqt` to copy required Qt libraries:

```sh
C:/path/to/Qt/6.x.x/mingw_64/bin/windeployqt.exe --release TextEncoder.exe
```

## Usage

### 1. Input Text: 

- Enter text directly into the "Input Text" area, OR
- Click "Select File" to load text from a .txt file, OR
- Drag and drop a single text file onto the main window.

### 2. Select Cipher: 

- Choose the desired encryption algorithm from the dropdown menu.

### 3. Enter Key: 

- Input the appropriate key in the "Key" field for the selected cipher.
- Generate Key (Optional): Click "Generate Key" for assistance creating a suitable key (if applicable to the chosen cipher).

### 4. Process: 

- Click "Encrypt" or "Decrypt".

### 5. View Output: 

- The result will appear in the "Output Text" area.

### 6. Save Output (Optional): 

- Click "Save Result" to save the output text to a file.

## License
This project is licensed under the MIT License. See the [LICENSE](https://github.com/ofmiq/TextEncoder/blob/main/LICENSE) file for details.