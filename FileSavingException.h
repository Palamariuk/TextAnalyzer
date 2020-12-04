#ifndef FILESAVINGEXCEPTION_H
#define FILESAVINGEXCEPTION_H

#include <exception>

class FileSavingException : public std::exception{
public:
    FileSavingException() = default;

    const char * what() const noexcept{
        return "Cannot save to file! Please, try again.";
    }
};

#endif // FILESAVINGEXCEPTION_H
