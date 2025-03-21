#include "gui.h"
#include <thread>
#include <chrono>
#include "map.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    std::thread guiThread([&]() {
        GUI::CreateAndShowWindow(hInstance, nCmdShow);
        });

    // Attendre un peu pour que la fenêtre s'affiche
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Simuler des logs
    createMap();

    guiThread.join(); // Attendre que la GUI se termine
    return 0;
}
