#include <iostream>
#include <windows.h>
#include "src/Memory.hpp"

//void DisplayLastErr() {
//    DWORD err = ::GetLastError();
//    if (err == 0) {
//        std::cerr << "Cannot access to the last err but no one so far" << std::endl;
//        return;
//    }
//    LPSTR messageBuffer = nullptr;
//    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//                   nullptr, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, nullptr);
//    std::cerr << "Last error: " << messageBuffer << std::endl;
//    LocalFree(messageBuffer);
//}

int main(int, char **) {
    FTL::Memory memory("FTL: Faster Than Light");
    std::cout << "Player has " << std::to_string(memory.GetUserData<int>(FTL::Memory::SCRAP)) << std::endl;
    memory.SetUserData(FTL::Memory::SCRAP, 0xFFFF); // 0xFFFF = 65565
    memory.SetUserData(FTL::Memory::DRONE, 0xFFFF);
    memory.SetUserData(FTL::Memory::FUEL, 0xFFFF);
    return 0;
}
