#include <node.h>
#include <v8.h>

#include <libtorrent/version.hpp>

namespace lt {
    using namespace v8;

    void InitSession(Handle<Object> exports);
    void InitTorrentInfo(Handle<Object> exports);
    void InitTorrentHandle(Handle<Object> exports);

    void Init(Handle<Object> exports) {
        InitSession(exports);
        InitTorrentInfo(exports);
        InitTorrentHandle(exports);

        exports->Set(String::NewSymbol("version"), String::New(LIBTORRENT_VERSION));
    }
}

NODE_MODULE(libtorrent, lt::Init)