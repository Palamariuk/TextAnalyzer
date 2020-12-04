#ifndef NOLETTERSEXEPTION_H
#define NOLETTERSEXEPTION_H

#include <exception>

class NoLettersException : public std::exception{
public:
    NoLettersException() = default;

    const char * what() const noexcept{
        return "There are no letters in your text.";
    }
};

#endif // NOLETTERSEXEPTION_H
