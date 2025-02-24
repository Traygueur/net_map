#include "gui.h"

HWND GUI::hConsoleOutput = NULL; // Zone de texte pour la "console"

LRESULT CALLBACK GUI::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        // Créer un Edit Control multi-lignes pour afficher la console
        GUI::hConsoleOutput = CreateWindowEx(
            WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            10, 10, 760, 500,
            hwnd, NULL, GetModuleHandle(NULL), NULL
        );
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void GUI::CreateAndShowWindow(HINSTANCE hInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"MaFenetreClass"; // Utiliser wchar_t pour Unicode

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Fenêtre avec Console Intégrée", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd) {
        ShowWindow(hwnd, nCmdShow);

        // Boucle principale de messages
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

void GUI::AppendTextToConsole(const std::string& text) {
    if (hConsoleOutput) {
        int length = GetWindowTextLength(hConsoleOutput);
        SendMessage(hConsoleOutput, EM_SETSEL, (WPARAM)length, (LPARAM)length);
        // Convertir std::string en std::wstring
        std::wstring wText(text.begin(), text.end());
        SendMessage(hConsoleOutput, EM_REPLACESEL, FALSE, (LPARAM)wText.c_str());
    }
}
