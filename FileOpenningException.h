#ifndef FILEOPENNINGEXCEPTION_H
#define FILEOPENNINGEXCEPTION_H

#include <exception>

class FileOpenningException : public std::exception{
public:
    FileOpenningException() = default;

    const char * what() const noexcept{
        return "Cannot open file! Please, try again.";
    }
};

#endif // FILEOPENNINGEXCEPTION_H
