#include <node.h>
#include <libtorrent/torrent_info.hpp>

#include "torrent_info.h"

using namespace v8;

namespace lt {
    Persistent<Function> TorrentInfo::constructor;
    
    void InitTorrentInfo(Handle<Object> exports) {
        TorrentInfo::Initialize(exports);
    }

    TorrentInfo::TorrentInfo() {
        this->torrent_info_ = NULL;
    }

    TorrentInfo::TorrentInfo(const std::string &filename) {
        this->torrent_info_ = new libtorrent::torrent_info(filename);
    }

    TorrentInfo::~TorrentInfo() {
        if(this->torrent_info_ != NULL) {
            delete this->torrent_info_;
        }
    }

    void TorrentInfo::Initialize(Handle<Object> exports) {
        Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
        tpl->SetClassName(String::NewSymbol("torrent_info"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // name
        tpl->PrototypeTemplate()->Set(String::NewSymbol("name"),
            FunctionTemplate::New(GetName)->GetFunction());

        // total size
        tpl->PrototypeTemplate()->Set(String::NewSymbol("total_size"),
            FunctionTemplate::New(GetTotalSize)->GetFunction());

        // num_files
        tpl->PrototypeTemplate()->Set(String::NewSymbol("num_files"),
            FunctionTemplate::New(GetNumFiles)->GetFunction());

        exports->Set(String::NewSymbol("torrent_info"),
            Persistent<Function>::New(tpl->GetFunction()));

        constructor = Persistent<Function>::New(tpl->GetFunction());
    }

    Handle<Value> TorrentInfo::NewInstance(const Arguments &args) {
        HandleScope handle_scope;

        if(!args.IsConstructCall())
        {
            return ThrowException(Exception::TypeError(
                String::New("Use the new operator to create instances of this object.")));
        }

        TorrentInfo *ti;

        if(args.Length() == 1 && args[0]->IsString()) {
            std::string filename(*String::Utf8Value(args[0]->ToString()));
            ti = new TorrentInfo(filename);
        }

        ti->Wrap(args.This());

        return handle_scope.Close(args.This());
    }

    Handle<Value> TorrentInfo::GetName(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_info* ti = TorrentInfo::Unwrap(args.This());
        return handle_scope.Close(String::New(ti->name().c_str()));
    }

    Handle<Value> TorrentInfo::GetNumFiles(const Arguments &args) {
        HandleScope handle_scope;
        
        libtorrent::torrent_info *ti = TorrentInfo::Unwrap(args.This());
        return handle_scope.Close(Integer::New(ti->num_files()));
    }

    Handle<Value> TorrentInfo::GetTotalSize(const Arguments &args) {
        HandleScope handle_scope;
        
        libtorrent::torrent_info *ti = TorrentInfo::Unwrap(args.This());
        return handle_scope.Close(Integer::New(ti->total_size()));
    }
}