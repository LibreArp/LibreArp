#include "ArpIntegrityException.h"

#include <string>
#include <stdexcept>

ArpIntegrityException::ArpIntegrityException(std::string message) : std::runtime_error(message) {

}
