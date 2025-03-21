#include "gui.h"
#include <gdiplus.h>
#pragma comment (lib, "gdiplus.lib")
#include <codecvt>
#include <windows.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <locale>


HWND GUI::hConsoleOutput = NULL; // Zone de texte pour la "console"
LPCWSTR imagePath = L"C:\\Users\\coulo\\Documents\\ESAIP\\PROJECT_APPLICATIF_C++\\net_map\\Net_map\\test.bmp"; // Remplace par le chemin de ton image
HBITMAP hBitmap = NULL; // Image chargée

LRESULT CALLBACK GUI::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        // Créer un Edit Control multi-lignes pour afficher la console
        GUI::hConsoleOutput = CreateWindowEx(
            WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            10, 10, 760, 200, // Hauteur réduite pour laisser de la place à l’image
            hwnd, NULL, GetModuleHandle(NULL), NULL
        );

        // Charger l'image BMP
        hBitmap = (HBITMAP)LoadImage(NULL, imagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (!hBitmap) {
            MessageBox(hwnd, L"Erreur lors du chargement de l'image !", L"Erreur", MB_OK | MB_ICONERROR);
        }
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (hBitmap) {
            HDC hdcMem = CreateCompatibleDC(hdc);
            SelectObject(hdcMem, hBitmap);

            BITMAP bitmap;
            GetObject(hBitmap, sizeof(BITMAP), &bitmap);

            // Affichage de l'image en dessous de l'Edit Control
            int imageX = 10;  // Position horizontale
            int imageY = 220; // Position verticale sous l'Edit Control
            BitBlt(hdc, imageX, imageY, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

            DeleteDC(hdcMem);
        }

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        // Libérer la mémoire de l'image
        if (hBitmap) {
            DeleteObject(hBitmap);
        }
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
};

bool fileExists(const std::wstring& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::string wstringToString(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

