#ifndef GUI_H
#define GUI_H

#include <windows.h>
#include <string>

class GUI {
public:
    static void CreateAndShowWindow(HINSTANCE hInstance, int nCmdShow);
    static void AppendTextToConsole(const std::string& text);
private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static HWND hConsoleOutput; // Zone de texte simulant la console
};

#endif // GUI_H
