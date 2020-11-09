#include "Console.hpp"

Console::Console() {
    debugLog.open("debug.log", std::ios::app);
    if(!debugLog.good()) {
#ifdef _WIN32
        MessageBox(NULL, "Cannot save log to debug.log", "Error", MB_DEFAULT_DESKTOP_ONLY | MB_ICONERROR | MB_APPLMODAL);
#else
        usingSystem = system("zenity --error --text=\"Cannot save log to debug.log!\" --title=\"Error!\" --width=200 &");
#endif // _WIN32
        exit(-1);
    }
}

Console::~Console() {
    debugLog.close();
}

void Console::__log(const char* func, int line, std::string message) {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);

    debugLog << '[' << buffer << ']' << func << ':' << line << "=>" << message << '\n' << std::flush;

    return;
}

void Console::__warning(const char* func, int line, std::string message) {
    __log(func, line, "Warning: " + message);
#ifdef _WIN32
    ShowWindow(windowHandle, SW_MINIMIZE);
    MessageBox(NULL, message.c_str(), "Warning", MB_DEFAULT_DESKTOP_ONLY | MB_ICONWARNING | MB_TOPMOST);
#else
    usingSystem = system(std::string(std::string("zenity --warning --text=\"") + message.c_str() + "\" --title=\"Warning!\" --width=200 &").c_str());
#endif // _WIN32
    return;
}

void Console::__error(const char* func, int line, std::string message) {
    __log(func, line, "Error: " + message);
#ifdef _WIN32
    ShowWindow(windowHandle, SW_MINIMIZE);
    MessageBox(NULL, message.c_str(), "Error", MB_DEFAULT_DESKTOP_ONLY | MB_ICONERROR | MB_APPLMODAL);
#else
    usingSystem = system(std::string(std::string("zenity --error --text=\"") + message.c_str() + "\" --title=\"Error!\" --width=200 &").c_str());
#endif // _WIN32
    exit(-1);
}
