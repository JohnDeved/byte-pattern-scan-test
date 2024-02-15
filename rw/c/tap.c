#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <time.h>

DWORD FindProcessId(const char* processName) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe32 = { .dwSize = sizeof(PROCESSENTRY32) };
        if (Process32First(hSnap, &pe32)) {
            do {
                if (strcmp(pe32.szExeFile, processName) == 0) {
                    CloseHandle(hSnap);
                    return pe32.th32ProcessID;
                }
            } while (Process32Next(hSnap, &pe32));
        }
        CloseHandle(hSnap);
    }
    return 0;
}

DWORD GetModuleBaseAddress(DWORD dwProcessId, const char* szModuleName) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 ModuleEntry32 = { .dwSize = sizeof(MODULEENTRY32) };
        if (Module32First(hSnap, &ModuleEntry32)) {
            do {
                if (strcmp(ModuleEntry32.szModule, szModuleName) == 0) {
                    CloseHandle(hSnap);
                    return (DWORD_PTR)ModuleEntry32.modBaseAddr;
                }
            } while (Module32Next(hSnap, &ModuleEntry32));
        }
        CloseHandle(hSnap);
    }
    return 0;
}

DWORD CalculateFinalAddress(HANDLE hProcess, DWORD lpBaseAddress, DWORD offsets[], int noffsets) {
    DWORD address = lpBaseAddress;
    for (int i = 0; i < noffsets - 1; i++) {
        address += offsets[i];
        if (!ReadProcessMemory(hProcess, (LPVOID)(DWORD_PTR)address, &address, sizeof(address), NULL) || address == 0) {
            return 0;
        }
    }
    return address + offsets[noffsets - 1];
}

int main() {
    const char* processName = "Sakura Clicker.exe";
    DWORD pid = FindProcessId(processName);
    if (pid == 0) return 1;

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess) return 1;

    DWORD_PTR lpBaseAddress = GetModuleBaseAddress(pid, processName);
    if (!lpBaseAddress) return 1;

    DWORD offsets[] = {0x2F0DD8, 0x24, 0x8};
    DWORD_PTR finalAddress = CalculateFinalAddress(hProcess, lpBaseAddress, offsets, sizeof(offsets) / sizeof(offsets[0]));
    if (finalAddress == 0) return 1;

    clock_t time = clock() + 5000;
    int index = 0;
    clock_t now;
    for (now = clock(); now <= time; now = clock(), index++) {
        double value = (double)index;
        if (!WriteProcessMemory(hProcess, (LPVOID)finalAddress, &value, sizeof(value), NULL)) return 1;
    }
    printf("writes: %f / sec\n", index / 5.0);

    time = now + 5000;
    index = 0;
    for (now = clock(); now <= time; now = clock(), index++) {
        double readValue = 0;
        if (!ReadProcessMemory(hProcess, (LPVOID)finalAddress, &readValue, sizeof(readValue), NULL)) return 1;
    }
    printf("reads: %f / sec\n", index / 5.0);

    CloseHandle(hProcess);
    return 0;
}