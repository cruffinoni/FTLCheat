/*
** EPITECH PROJECT, 2020
** FTLCheat
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Memory.hpp"
#include <tlhelp32.h>
#include <iostream>

FTL::Memory::Memory(const std::string& process_name) : _process_name(process_name) {
    HWND window = FindWindow(nullptr, process_name.c_str());
    GetWindowThreadProcessId(window, &this->_p_id);

    this->_process = OpenProcess(PROCESS_ALL_ACCESS, false, this->_p_id);
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->_p_id);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 module_entry;
        module_entry.dwSize = sizeof(module_entry);
        if (Module32First(hSnap, &module_entry)) {
            do {
                if (std::string(module_entry.szModule).find("FTL") != std::string::npos) {
                    std::cout << "Module: " << module_entry.szModule << " w/ 0x" << std::hex << (uintptr_t) module_entry.modBaseAddr << std::endl;
                    this->_base_addr = (uintptr_t) module_entry.modBaseAddr;
                }
            } while (Module32Next(hSnap, &module_entry));
        }
    }
    CloseHandle(hSnap);
    this->GetPlayerData();
}

FTL::Memory::~Memory() {
    CloseHandle(this->_process);
}

void FTL::Memory::GetPlayerData() {
    this->Read(&this->_user_data[RESERVED].first,
               this->_base_addr + this->_user_data[RESERVED].second);
    int k = SCRAP;
    for (auto &i: this->_user_data) {
        this->_user_data[k].second += this->_user_data[RESERVED].first;
        this->Read(&this->_user_data[k].first, this->_user_data[k].second);
        k++;
    }
}
