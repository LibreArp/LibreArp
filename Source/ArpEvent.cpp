#include "ArpEvent.h"

bool ArpEvent::operator<(ArpEvent &other) {
    return this->time < other.time;
}

bool ArpEvent::operator<=(ArpEvent &other) {
    return this->time <= other.time;
}

bool ArpEvent::operator>(ArpEvent &other) {
    return this->time < other.time;
}

bool ArpEvent::operator>=(ArpEvent &other) {
    return this->time >= other.time;
}

bool ArpEvent::operator==(ArpEvent &other) {
    return this->time == other.time;
}
