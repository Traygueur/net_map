#include "gui.h"
#include <thread>
#include <chrono>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    std::thread guiThread([&]() {
        GUI::CreateAndShowWindow(hInstance, nCmdShow);
        });

    // Attendre un peu pour que la fenêtre s'affiche
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Simuler des logs
    for (int i = 0; i < 10; ++i) {
        GUI::AppendTextToConsole("Log numéro " + std::to_string(i) + "\r\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    guiThread.join(); // Attendre que la GUI se termine
    return 0;
}
