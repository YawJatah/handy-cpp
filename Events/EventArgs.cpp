#include "EventArgs.h"

#include <utility>

namespace IlluminiaStudios::HandyCPP {

    using namespace std;

    EventArgs EventArgs::Empty = EventArgs();

    EventArgs::EventArgs() {

    }

    EventArgs::EventArgs(EventArgs && other) {
        *this = move(other);
    }

    EventArgs::~EventArgs() {

    }
    
    EventArgs & EventArgs::operator=(EventArgs && other) {
        *this = move(other);
        return *this;
    }
}
