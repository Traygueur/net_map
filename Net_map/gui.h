#ifndef GUI_H
#define GUI_H

#include <windows.h>
#include <string>
//lib for png in the gui
#include <gdiplus.h>
#pragma comment (lib,"gdiplus.lib")

#include <codecvt>


class GUI {
public:
    static void CreateAndShowWindow(HINSTANCE hInstance, int nCmdShow);
    static void AppendTextToConsole(const std::string& text);
    static void AppendImageToConsole(const std::wstring& imagePath);
private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static HWND hConsoleOutput; // Zone de texte simulant la console
};

#endif // GUI_H
