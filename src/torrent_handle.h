#ifndef TORRENT_HANDLE_H
#define TORRENT_HANDLE_H

#include <node.h>
#include <libtorrent/torrent_handle.hpp>

namespace lt {
    class TorrentHandle : public node::ObjectWrap {
        public:
            static void Initialize(v8::Handle<v8::Object> exports);
            static v8::Local<v8::Object> New(const libtorrent::torrent_handle &handle);

            static libtorrent::torrent_handle* Unwrap(const v8::Local<v8::Object> &obj) {
                return node::ObjectWrap::Unwrap<TorrentHandle>(obj)->torrent_handle_;
            }

        private:
            TorrentHandle();
            ~TorrentHandle();

            static v8::Handle<v8::Value> NewInstance(const v8::Arguments &args);
            //static v8::Handle<v8::Value> AddPiece(const v8::Arguments &args);
            static v8::Handle<v8::Value> ReadPiece(const v8::Arguments &args);
            static v8::Handle<v8::Value> HavePiece(const v8::Arguments &args);
            //static v8::Handle<v8::Value> GetPeerInfo(const v8::Arguments &args);
            static v8::Handle<v8::Value> Status(const v8::Arguments &args);
            //static v8::Handle<v8::Value> GetDownloadQueue(const v8::Arguments &args);
            static v8::Handle<v8::Value> ResetPieceDeadline(const v8::Arguments &args);
            static v8::Handle<v8::Value> ClearPieceDeadlines(const v8::Arguments &args);
            static v8::Handle<v8::Value> SetPieceDeadline(const v8::Arguments &args);
            static v8::Handle<v8::Value> SetPriority(const v8::Arguments &args);
            //static v8::Handle<v8::Value> FileProgress(const v8::Arguments &args);
            static v8::Handle<v8::Value> ClearError(const v8::Arguments &args);
            //static v8::Handle<v8::Value> Trackers(const v8::Arguments &args);
            //static v8::Handle<v8::Value> ReplaceTrackers(const v8::Arguments &args);
            //static v8::Handle<v8::Value> AddTracker(const v8::Arguments &args);
            static v8::Handle<v8::Value> AddUrlSeed(const v8::Arguments &args);
            static v8::Handle<v8::Value> RemoveUrlSeed(const v8::Arguments &args);
            //static v8::Handle<v8::Value> UrlSeeds(const v8::Arguments &args);
            static v8::Handle<v8::Value> AddHttpSeed(const v8::Arguments &args);
            static v8::Handle<v8::Value> RemoveHttpSeed(const v8::Arguments &args);
            //static v8::Handle<v8::Value> HttpSeeds(const v8::Arguments &args);
            //static v8::Handle<v8::Value> AddExtension(const v8::Arguments &args);
            //static v8::Handle<v8::Value> SetMetadata(const v8::Arguments &args);
            static v8::Handle<v8::Value> IsValid(const v8::Arguments &args);
            static v8::Handle<v8::Value> Pause(const v8::Arguments &args);
            static v8::Handle<v8::Value> Resume(const v8::Arguments &args);
            static v8::Handle<v8::Value> SetUploadMode(const v8::Arguments &args);
            static v8::Handle<v8::Value> SetShareMode(const v8::Arguments &args);
            static v8::Handle<v8::Value> FlushCache(const v8::Arguments &args);

            static v8::Handle<v8::Value> GetName(const v8::Arguments &args);
            
            static v8::Persistent<v8::Function> constructor;

            // member variables
            libtorrent::torrent_handle *torrent_handle_;
    };
}

#endif