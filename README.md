# Pixa

Pixa is a small desktop image-processing application written in C++ with
[SFML](https://www.sfml-dev.org/). It provides a graphical interface for
loading an image, applying common image-processing filters, comparing the
original and processed images, and saving the result.

## Features

- Load PNG, JPEG, BMP, or TGA images through the native Windows file picker.
- Display the input and processed images side by side.
- Display RGB histograms for both images.
- Apply the following operations:
  - Smoothing (3x3 convolution)
  - Edge detection
  - Red, green, or blue channel isolation
  - Mosaic/pixelation
  - Grayscale conversion
  - Negative transformation
  - Binarization at 50%, 90%, 93%, 95%, or 99% thresholds
- Move the processed image back into the input slot to chain operations.
- Save the processed image as PNG, JPEG, or BMP.

## Requirements

- Windows
- A C++17-compatible compiler
- [CMake](https://cmake.org/) 3.28 or newer
- Git, required by CMake to download SFML

SFML 3.1.0 is declared as a CMake `FetchContent` dependency, so it is
downloaded automatically during the first configuration.

## Build

From the project root, configure and build an out-of-source build directory:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

The executable is written to the selected CMake binary directory. With a
single-configuration generator, run it with:

```powershell
.\build\Pixa.exe
```

With a multi-configuration generator such as Visual Studio, use:

```powershell
.\build\Release\Pixa.exe
```

For a debug build:

```powershell
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug --config Debug
.\build-debug\Pixa.exe
```

If you use an IDE such as Visual Studio or CLion, open the repository as a
CMake project and select the `Pixa` target.

## Usage

1. Start `Pixa.exe` from the project root, so the application can find its
   runtime assets.
2. Click **Load Button** and choose an image.
3. Select a filter from the left-hand toolbar.
4. Review the processed image and its RGB histogram on the right.
5. Use **Img1 <- Img2** to make the processed image the new input image if
   you want to apply another operation.
6. Click **Save Button** and choose an output path.

The application window is designed around a base size of 1660 x 840 pixels.
Images are scaled to fit within 640 x 360 pixels while preserving their
aspect ratio.

## Project structure

```text
.
├── CMakeLists.txt       # CMake project and SFML dependency configuration
├── main.cpp             # Application window, event loop, and UI wiring
├── src/
│   ├── Button.*         # Interactive UI button
│   ├── Chart.*          # RGB histogram widget
│   ├── Constants.hpp    # Window and layout constants
│   └── func.*           # File dialogs, scaling, and image filters
└── assets/
    ├── icon.png        # Window icon
    └── cheese_milky/   # UI font
```

## Notes

- The native file dialogs and current implementation use Windows APIs, so the
  project is currently Windows-specific.
- Runtime asset paths are relative to the working directory. Run the
  executable from the repository root, or copy the `assets` directory beside
  the executable.
- The bundled `Cheese Milky` font is accompanied by a license notice in
  [`assets/cheese_milky/Read Me.txt`](assets/cheese_milky/Read%20Me.txt).
  That notice states that the font is for personal use only and requires a
  separate license for promotional or commercial use.

## License

No project license file is currently included. Contact the repository owner
before redistributing or using the project commercially.
