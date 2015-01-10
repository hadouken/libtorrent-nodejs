#ifndef TORRENT_INFO_H
#define TORRENT_INFO_H

#include <node.h>
#include <libtorrent/torrent_info.hpp>

namespace lt {
    class TorrentInfo : public node::ObjectWrap {
        public:
            static void Initialize(v8::Handle<v8::Object> exports);
            static v8::Local<v8::Object> New(const libtorrent::torrent_info &info);

            static libtorrent::torrent_info* Unwrap(const v8::Local<v8::Object> &obj) {
                return node::ObjectWrap::Unwrap<TorrentInfo>(obj)->torrent_info_;
            }

        private:
            TorrentInfo();
            TorrentInfo(const std::string &filename);
            ~TorrentInfo();

            static v8::Handle<v8::Value> NewInstance(const v8::Arguments &args);
            static v8::Handle<v8::Value> New(const v8::Arguments &args);
            static v8::Handle<v8::Value> GetName(const v8::Arguments &args);
            static v8::Handle<v8::Value> GetNumFiles(const v8::Arguments &args);
            static v8::Handle<v8::Value> GetTotalSize(const v8::Arguments &args);

            static v8::Persistent<v8::Function> constructor;

            libtorrent::torrent_info *torrent_info_;
    };
}

#endif