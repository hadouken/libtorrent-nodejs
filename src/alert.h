#ifndef ALERT_H
#define ALERT_H

#include <node.h>
#include <libtorrent/alert.hpp>

namespace lt {
    class Alert {
        public:
            static v8::Handle<v8::Value> ToObject(const libtorrent::alert &alert);
    };
}

#endif