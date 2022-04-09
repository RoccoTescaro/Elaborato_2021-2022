#ifndef LOG_H
#define LOG_H

#include <iostream>

#ifndef DEBUG_MODE

#define ERROR(string)
#define DEBUG(string, ...)

#else

#define ERROR(string) { error(string); }
#define DEBUG(string, ...) { debugLog(string, __VA_ARGS__);}

void error(const char* string) {
	std::cout << "[ERROR] " << string << std::endl;
}

void debug(const char* string) {
    std::cout << string << std::endl;
}

template<typename T, typename ...Args>
void debug(const char* string, T value, Args... args) {

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
void debugLog(const char* string, Args... args) {
    std::cout << "[DEBUG] ";
    debug(string, args...);
}




#endif


#endif //LOG_H