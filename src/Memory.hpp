/*
** EPITECH PROJECT, 2020
** FTLCheat
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef FTLCHEAT_MEMORY_HPP
#define FTLCHEAT_MEMORY_HPP

#include <string>
#include <vector>
#include <utility>
#include <windows.h>

namespace FTL {
    class Memory {
        public:
        typedef uint32_t localptr_t;
        typedef uint16_t localoffset_t;

        explicit Memory(const std::string& process_name);
        ~Memory();

        template <class T>
        void Write(T value, localptr_t addr)  {
            SIZE_T read = 0;
            printf("Addr: 0x%X w/ %i\n", addr, value);
            if (WriteProcessMemory(this->_process, reinterpret_cast<LPVOID>(addr),
                                   reinterpret_cast<LPCVOID>(&value), sizeof(T), &read))
                printf("I wrote %llu w/ %u at %p\r\n", read, value, addr);
            else
                printf("Cant write/err: %d\n", ::GetLastError());
        }

        template <class T>
        void Read(T* hold, localptr_t addr) {
            SIZE_T read = 0;
            printf("Addr: 0x%X\n", addr);
            if (ReadProcessMemory(this->_process, reinterpret_cast<LPCVOID>(addr), hold, sizeof(T), &read))
                printf("I read %llu w/ %u (0x%X) at %p\r\n", read, *hold, *hold, addr);
            else
                printf("Cant write/err: %d\n", ::GetLastError());
        }

        enum PlayerDataMember : uint8_t {
            RESERVED,
            SCRAP,
            DRONE,
            FUEL
        };
        template <typename T = int>
        void SetUserData(PlayerDataMember member, T data) {
            if (member == RESERVED)
                return;
            this->_user_data[member].first = data;
            this->Write(data, this->_user_data[member].second);
        }

        template <typename T = int>
        T GetUserData(PlayerDataMember member) {
            if (member == RESERVED)
                return ((T) -1);
            return (this->_user_data[member].first);
        }

        private:
        std::string _process_name;
        uint32_t _p_id = 0;
        uintptr_t _base_addr;

        HANDLE _process;

        void GetPlayerData();
        std::vector<std::pair<int32_t, localptr_t>> _user_data = {
            std::make_pair(0, 0x51348C),
            std::make_pair(0, 0x4D4),
            std::make_pair(0, 0x800),
            std::make_pair(0, 0x494)
        };
    };
}


#endif //FTLCHEAT_MEMORY_HPP
