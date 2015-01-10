#include <node.h>

#include "torrent_handle.h"
#include "torrent_status.h"

using namespace v8;

namespace lt {
    Persistent<Function> TorrentHandle::constructor;

    TorrentHandle::TorrentHandle() {
        this->torrent_handle_ = NULL;
    }

    TorrentHandle::~TorrentHandle() {
        if(this->torrent_handle_ != NULL) {
            delete this->torrent_handle_;
        }
    }

    void InitTorrentHandle(Handle<Object> exports) {
        TorrentHandle::Initialize(exports);
    }

    void TorrentHandle::Initialize(Handle<Object> exports) {
        Local<FunctionTemplate> tpl = FunctionTemplate::New(NewInstance);
        tpl->SetClassName(String::NewSymbol("torrent_handle"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        tpl->PrototypeTemplate()->Set(String::NewSymbol("read_piece"), FunctionTemplate::New(ReadPiece)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("have_piece"), FunctionTemplate::New(HavePiece)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("status"), FunctionTemplate::New(Status)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("reset_piece_deadline"), FunctionTemplate::New(ResetPieceDeadline)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("clear_piece_deadlines"), FunctionTemplate::New(ClearPieceDeadlines)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("set_piece_deadline"), FunctionTemplate::New(SetPieceDeadline)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("set_priority"), FunctionTemplate::New(SetPriority)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("clear_error"), FunctionTemplate::New(ClearError)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("add_url_seed"), FunctionTemplate::New(AddUrlSeed)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("remove_url_seed"), FunctionTemplate::New(RemoveUrlSeed)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("add_http_seed"), FunctionTemplate::New(AddHttpSeed)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("remove_http_seed"), FunctionTemplate::New(RemoveHttpSeed)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("is_valid"), FunctionTemplate::New(IsValid)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("pause"), FunctionTemplate::New(Pause)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("resume"), FunctionTemplate::New(Resume)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("set_upload_mode"), FunctionTemplate::New(SetUploadMode)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("set_share_mode"), FunctionTemplate::New(SetShareMode)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("flush_cache"), FunctionTemplate::New(FlushCache)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("name"), FunctionTemplate::New(GetName)->GetFunction());

        constructor = Persistent<Function>::New(tpl->GetFunction());
    }

    Local<Object> TorrentHandle::New(const libtorrent::torrent_handle &handle) {
        HandleScope handle_scope;

        Local<Object> obj = constructor->NewInstance();
        ObjectWrap::Unwrap<TorrentHandle>(obj)->torrent_handle_ = new libtorrent::torrent_handle(handle);

        return handle_scope.Close(obj);
    }

    Handle<Value> TorrentHandle::NewInstance(const Arguments &args) {
        HandleScope handle_scope;

        if(!args.IsConstructCall()) {
            return ThrowException(Exception::TypeError(
                String::New("Use the new operator to create new instances of this object.")));
        }

        TorrentHandle *handle = new TorrentHandle();
        handle->Wrap(args.This());

        return handle_scope.Close(args.This());
    }

    Handle<Value> TorrentHandle::ReadPiece(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() == 1) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            handle->read_piece(args[0]->IntegerValue());
        }

        return Undefined();
    }

    Handle<Value> TorrentHandle::HavePiece(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() == 1) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            return handle_scope.Close(Boolean::New(handle->have_piece(args[0]->IntegerValue())));
        }

        return Undefined();
    }

    Handle<Value> TorrentHandle::Status(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
        return handle_scope.Close(TorrentStatus::ToObject(handle->status()));
    }

    Handle<Value> TorrentHandle::ResetPieceDeadline(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() == 1) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            handle->reset_piece_deadline(args[0]->IntegerValue());
        }
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::ClearPieceDeadlines(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
        handle->clear_piece_deadlines();
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::SetPieceDeadline(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());

        int index = args[0]->IntegerValue();
        int deadline = args[1]->IntegerValue();

        if(args.Length() == 2) {
            handle->set_piece_deadline(index, deadline);
        } else if(args.Length() == 3) {
            int flags = args[2]->IntegerValue();
            handle->set_piece_deadline(index, deadline, flags);
        }
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::SetPriority(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            handle->set_priority(args[0]->IntegerValue());
        }
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::ClearError(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
        handle->clear_error();        
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::AddUrlSeed(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            std::string url = *String::Utf8Value(args[0]->ToString());

            handle->add_url_seed(url);
        }
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::RemoveUrlSeed(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            std::string url = *String::Utf8Value(args[0]->ToString());

            handle->remove_url_seed(url);
        }
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::AddHttpSeed(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            std::string url = *String::Utf8Value(args[0]->ToString());

            handle->add_http_seed(url);
        }
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::RemoveHttpSeed(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            std::string url = *String::Utf8Value(args[0]->ToString());

            handle->remove_http_seed(url);
        }
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::IsValid(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
        return handle_scope.Close(Boolean::New(handle->is_valid()));
    }

    Handle<Value> TorrentHandle::Pause(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
        int flags = 0;

        if(args.Length() > 0) {
            flags = args[0]->IntegerValue();
        }

        handle->pause(flags);

        return Undefined();
    }

    Handle<Value> TorrentHandle::Resume(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
        handle->resume();

        return Undefined();
    }

    Handle<Value> TorrentHandle::SetUploadMode(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            handle->set_upload_mode(args[0]->BooleanValue());
        }
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::SetShareMode(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
            handle->set_share_mode(args[0]->BooleanValue());
        }
        
        return Undefined();
    }

    Handle<Value> TorrentHandle::FlushCache(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
        handle->flush_cache();

        return Undefined();
    }

    Handle<Value> TorrentHandle::GetName(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(args.This());
        return handle_scope.Close(String::New(handle->name().c_str()));
    }
}
