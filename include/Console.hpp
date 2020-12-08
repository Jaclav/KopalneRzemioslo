#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <chrono>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
extern HWND windowHandle;
#endif // _WIN32

extern int usingSystem;

class Console {
private:
    std::fstream debugLog;
public:
    Console();
    ~Console();

    void doLog(std::string message = "Empty doLog message.");
    void warning(std::string message = "Empty warning message.");
    void error(std::string message = "Empty error message.");

    //real functions
    void __doLog(const char* func, int line, std::string message = "Empty doLog message.");
    void __warning(const char* func, int line, std::string message = "Empty warning message.");
    void __error(const char* func, int line, std::string message = "Empty error message.");

#define doLog(...) __doLog(__func__,__LINE__,__VA_ARGS__)
#define warning(...) __warning(__func__,__LINE__,__VA_ARGS__)
#define error(...) __error(__func__,__LINE__,__VA_ARGS__)

};

#endif // CONSOLE_HPP
