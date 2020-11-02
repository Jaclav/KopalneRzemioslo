//DONOT: include this before tools.hpp, because math.h has log();
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

	void log(std::string message = "Empty log message.");
	void warning(std::string message = "Empty warning message.");
	void error(std::string message = "Empty error message.");

	//real functions
	void __log(const char* func, int line, std::string message = "Empty log message.");
	void __warning(const char* func, int line, std::string message = "Empty warning message.");
	void __error(const char* func, int line, std::string message = "Empty error message.");

#define log(...) __log(__func__,__LINE__,__VA_ARGS__)
#define warning(...) __warning(__func__,__LINE__,__VA_ARGS__)
#define error(...) __error(__func__,__LINE__,__VA_ARGS__)

};

#endif // CONSOLE_HPP
