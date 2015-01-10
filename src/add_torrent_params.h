#ifndef ADD_TORRENT_PARAMS_H
#define ADD_TORRENT_PARAMS_H

#include <node.h>
#include <libtorrent/add_torrent_params.hpp>

namespace lt {
    class AddTorrentParams {
        public:
            static libtorrent::add_torrent_params FromObject(v8::Local<v8::Object> obj);
    };
}

#endif