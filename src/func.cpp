#include "func.hpp"

#include <windows.h>
#include <commdlg.h>
#include <iostream>

std::string openImageDialog() {
    char fileName[MAX_PATH] = "";

    OPENFILENAMEA ofn{};
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;

    ofn.lpstrFilter =
        "Image Files\0*.png;*.jpg;*.jpeg;*.bmp;*.tga\0"
        "All Files\0*.*\0";

    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
        return fileName;

    return "";
}