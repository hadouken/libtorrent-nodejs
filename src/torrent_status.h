#ifndef TORRENT_STATUS_H
#define TORRENT_STATUS_H

#include <node.h>
#include <libtorrent/torrent_handle.hpp>

namespace lt {
    class TorrentStatus {
        public:
            static v8::Handle<v8::Value> ToObject(const libtorrent::torrent_status &status);
    };
}

#endif