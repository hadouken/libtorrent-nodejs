#include <node.h>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_info.hpp>

#include "add_torrent_params.h"
#include "torrent_info.h"

using namespace v8;

namespace lt {
    libtorrent::add_torrent_params AddTorrentParams::FromObject(Local<Object> obj) {
        HandleScope handle_scope;
        libtorrent::add_torrent_params p;

        if(obj->Has(String::NewSymbol("ti"))) {
            Local<Object> ti = obj->Get(String::NewSymbol("ti"))->ToObject();
            p.ti = new libtorrent::torrent_info(*TorrentInfo::Unwrap(ti));
        }

        if(obj->Has(String::NewSymbol("save_path"))) {
            String::Utf8Value sp(obj->Get(String::NewSymbol("save_path")));
            p.save_path = std::string(*sp);
        }

        return p;
    }
}