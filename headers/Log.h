#ifndef LOG_H
#define LOG_H

#include <iostream>

#ifndef DEBUG_MODE

#define ERROR(string)
#define DEBUG(string, ...)

#else

#define ERROR(string) { error(string); }
#define DEBUG(string, ...) { debugLog(string, __VA_ARGS__); }

static void error(const char* string) {
	std::cout << "[ERROR] " << string << std::endl;
}

static void debug(const char* string) {
    std::cout << string << std::endl;
}

template<typename T, typename ...Args>
static void debug(const char* string, T value, Args... args) {

    for (; *string != '\0'; string++)
    {
        if (*string == '%')
        {
            std::cout << std::to_string(value);
            debug(string + 1, args...); 
            return;
        }
        std::cout << *string;
    }

   
}

template<typename ...Args>
static void debugLog(const char* string, Args... args) {
    std::cout << "[DEBUG] ";
    debug(string, args...);
}
#endif


#endif //LOG_H