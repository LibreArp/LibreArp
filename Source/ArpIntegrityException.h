#pragma once


#include <string>
#include <stdexcept>

class ArpIntegrityException : public std::runtime_error {
public:
    explicit ArpIntegrityException(std::string message);
};


