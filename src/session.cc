#include <node.h>
#include <req_wrap.h>

#include "add_torrent_params.h"
#include "alert.h"
#include "session.h"
#include "torrent_handle.h"

using namespace v8;

namespace lt {
    static Persistent<String> oncomplete_sym;

    struct lt_work {
        Persistent<Function> callback;
        libtorrent::session *session_;
        int timeout;
        bool has_alert;
    };

    // InitSession
    void InitSession(Handle<Object> exports) {
        Session::Initialize(exports);
    }

    Session::Session(Local<Array> args) {
        this->session_ = new libtorrent::session();
    }

    Session::~Session() {
        delete this->session_;
    }

    void Session::Initialize(Handle<Object> exports) {
        Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
        tpl->SetClassName(String::NewSymbol("session"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        tpl->PrototypeTemplate()->Set(String::NewSymbol("post_torrent_updates"), FunctionTemplate::New(PostTorrentUpdates)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("find_torrent"), FunctionTemplate::New(FindTorrent)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("get_torrents"), FunctionTemplate::New(GetTorrents)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("async_add_torrent"), FunctionTemplate::New(AsyncAddTorrent)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("add_torrent"), FunctionTemplate::New(AddTorrent)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("resume"), FunctionTemplate::New(Resume)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("pause"), FunctionTemplate::New(Pause)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("is_paused"), FunctionTemplate::New(IsPaused)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("is_dht_running"), FunctionTemplate::New(IsDhtRunning)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("start_dht"), FunctionTemplate::New(StartDht)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("stop_dht"), FunctionTemplate::New(StopDht)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("add_dht_router"), FunctionTemplate::New(AddDhtRouter)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("add_dht_node"), FunctionTemplate::New(AddDhtNode)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("load_country_db"), FunctionTemplate::New(LoadCountryDb)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("load_asnum_db"), FunctionTemplate::New(LoadAsnumDb)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("as_for_ip"), FunctionTemplate::New(AsForIp)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("id"), FunctionTemplate::New(Id)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("set_peer_id"), FunctionTemplate::New(SetPeerId)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("set_key"), FunctionTemplate::New(SetKey)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("listen_on"), FunctionTemplate::New(ListenOn)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("is_listening"), FunctionTemplate::New(IsListening)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("listen_port"), FunctionTemplate::New(ListenPort)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("ssl_listen_port"), FunctionTemplate::New(SslListenPort)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("remove_torrent"), FunctionTemplate::New(RemoveTorrent)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("pop_alerts"), FunctionTemplate::New(PopAlerts)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("pop_alert"), FunctionTemplate::New(PopAlert)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("wait_for_alert"), FunctionTemplate::New(WaitForAlert)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("set_alert_mask"), FunctionTemplate::New(SetAlertMask)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("stop_lsd"), FunctionTemplate::New(StopLsd)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("start_lsd"), FunctionTemplate::New(StartLsd)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("stop_upnp"), FunctionTemplate::New(StopUpnp)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("start_upnp"), FunctionTemplate::New(StartUpnp)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("delete_port_mapping"), FunctionTemplate::New(DeletePortMapping)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("add_port_mapping"), FunctionTemplate::New(AddPortMapping)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("stop_natpmp"), FunctionTemplate::New(StopNatpmp)->GetFunction());
        tpl->PrototypeTemplate()->Set(String::NewSymbol("start_natpmp"), FunctionTemplate::New(StartNatpmp)->GetFunction());

        exports->Set(String::NewSymbol("session"),
            Persistent<Function>::New(tpl->GetFunction()));
    }

    Handle<Value> Session::New(const Arguments &args) {
        HandleScope handle_scope;

        if(!args.IsConstructCall()) {
            return ThrowException(Exception::TypeError(
                String::New("Use the new operator to create instances of this object.")));
        }

        Local<Array> data = Array::New();

        for(int i = 0, e = args.Length(); i < e; i++) {
            data->Set(i, args[i]);
        }

        Session *s = new Session(data);
        s->Wrap(args.This());

        return handle_scope.Close(args.This());
    }

    Handle<Value> Session::FindTorrent(const Arguments &args) {
        HandleScope handle_scope;

        String::Utf8Value arg(args[0]->ToString());
        
        libtorrent::sha1_hash hash(*arg);
        libtorrent::torrent_handle th = Session::Unwrap(args.This())->find_torrent(hash);

        return handle_scope.Close(TorrentHandle::New(th));
    }

    Handle<Value> Session::GetTorrents(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::session *s = Session::Unwrap(args.This());
        std::vector<libtorrent::torrent_handle> torrents = s->get_torrents();

        Local<Array> result = Array::New(torrents.size());

        for(int i = 0; i < torrents.size(); i++) {
            result->Set(i, TorrentHandle::New(torrents[i]));
        }

        return handle_scope.Close(result);
    }

    Handle<Value> Session::AsyncAddTorrent(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::add_torrent_params p = AddTorrentParams::FromObject(args[0]->ToObject());
        libtorrent::session *s = Session::Unwrap(args.This());

        s->async_add_torrent(p);

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::PostTorrentUpdates(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->post_torrent_updates();

        return Undefined();
    }

    Handle<Value> Session::AddTorrent(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::add_torrent_params p = AddTorrentParams::FromObject(args[0]->ToObject());
        libtorrent::session *s = Session::Unwrap(args.This());

        libtorrent::error_code ec;
        libtorrent::torrent_handle th = s->add_torrent(p, ec);

        return handle_scope.Close(TorrentHandle::New(th));
    }

    Handle<Value> Session::Resume(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->resume();
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::Pause(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->pause();
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::IsPaused(const Arguments &args) {
        HandleScope handle_scope;

        Handle<Boolean> is_paused = Boolean::New(Session::Unwrap(args.This())->is_paused());
        return handle_scope.Close(is_paused);
    }

    Handle<Value> Session::IsDhtRunning(const Arguments &args) {
        HandleScope handle_scope;

        Handle<Boolean> is_dht_running = Boolean::New(Session::Unwrap(args.This())->is_dht_running());
        return handle_scope.Close(is_dht_running);
    }

    Handle<Value> Session::StartDht(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->start_dht();
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::StopDht(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->stop_dht();
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::AddDhtRouter(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::session *s = Session::Unwrap(args.This());

        if(args.Length() > 1) {
            std::string arg1(*String::Utf8Value(args[0]->ToString()));
            int arg2 = args[1]->IntegerValue();

            s->add_dht_router(std::pair<std::string, int>(arg1, arg2));
        }

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::AddDhtNode(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::session *s = Session::Unwrap(args.This());

        if(args.Length() > 1) {
            std::string arg1(*String::Utf8Value(args[0]->ToString()));
            int arg2 = args[1]->IntegerValue();

            s->add_dht_router(std::pair<std::string, int>(arg1, arg2));
        }

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::LoadCountryDb(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::session *s = Session::Unwrap(args.This());
            s->load_country_db(*String::Utf8Value(args[0]->ToString()));
        }
        
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::LoadAsnumDb(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::session *s = Session::Unwrap(args.This());
            s->load_asnum_db(*String::Utf8Value(args[0]->ToString()));
        }
        
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::AsForIp(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            std::string addr(*String::Utf8Value(args[0]->ToString()));
            libtorrent::session *s = Session::Unwrap(args.This());
            int as = s->as_for_ip(libtorrent::address::from_string(addr));

            return handle_scope.Close(Integer::New(as));
        }
        
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::Id(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::session *s = Session::Unwrap(args.This());
        libtorrent::peer_id id = s->id();

        return handle_scope.Close(String::New(id.to_string().c_str()));
    }

    Handle<Value> Session::SetPeerId(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            String::Utf8Value arg(args[0]->ToString());
            libtorrent::peer_id id(*arg);

            libtorrent::session *s = Session::Unwrap(args.This());
            s->set_peer_id(id);
        }

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::SetKey(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            int key = args[0]->IntegerValue();

            libtorrent::session *s = Session::Unwrap(args.This());
            s->set_key(key);
        }

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::ListenOn(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            Local<Array> arr = Array::Cast(*args[0]);

            libtorrent::session *s = Session::Unwrap(args.This());
            s->listen_on(std::make_pair(arr->Get(0)->IntegerValue(), arr->Get(1)->IntegerValue()));
        }

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::IsListening(const Arguments &args) {
        HandleScope handle_scope;

        Handle<Boolean> is_listening = Boolean::New(Session::Unwrap(args.This())->is_listening());
        return handle_scope.Close(is_listening);
    }

    Handle<Value> Session::ListenPort(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::session *s = Session::Unwrap(args.This());
        return handle_scope.Close(Integer::New(s->listen_port()));
    }

    Handle<Value> Session::SslListenPort(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::session *s = Session::Unwrap(args.This());
        return handle_scope.Close(Integer::New(s->ssl_listen_port()));
    }

    Handle<Value> Session::RemoveTorrent(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            libtorrent::torrent_handle *th = TorrentHandle::Unwrap(args[0]->ToObject());
            libtorrent::session *s = Session::Unwrap(args.This());

            s->remove_torrent(*th);
        }

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::PopAlerts(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::session *s = Session::Unwrap(args.This());
        std::deque<libtorrent::alert*> alerts;

        s->pop_alerts(&alerts);

        Local<Array> data = Array::New(alerts.size());
        int index = 0;

        for(auto &i : alerts) {
            data->Set(index, Alert::ToObject(*i));

            index += 1;
            delete i;
        }

        return handle_scope.Close(data);
    }

    Handle<Value> Session::PopAlert(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::session *s = Session::Unwrap(args.This());
        std::auto_ptr<libtorrent::alert> alert = s->pop_alert();

        Handle<Value> result = Alert::ToObject(*alert);
        return handle_scope.Close(result);
    }

    Handle<Value> Session::WaitForAlert(const Arguments &args) {
        HandleScope handle_scope;

        libtorrent::session *s = Session::Unwrap(args.This());
        
        uv_work_t *req = new uv_work_t;
        lt_work *work = new lt_work;
        req->data = work;

        work->session_ = s;
        work->timeout = args[1]->IntegerValue();
        work->callback = Persistent<Function>::New(args[0].As<Function>());

        uv_queue_work(uv_default_loop(), req, &Session::WaitForAlertWork, &Session::WaitForAlertAfter);

        return Undefined();
    }

    void Session::WaitForAlertWork(uv_work_t *req) {
        lt_work *work = static_cast<lt_work*>(req->data);
        work->has_alert = (work->session_->wait_for_alert(libtorrent::milliseconds(work->timeout)) != 0);
    }

    void Session::WaitForAlertAfter(uv_work_t *req, int status) {
        HandleScope handle_scope;

        lt_work *work = static_cast<lt_work*>(req->data);

        Handle<Value> argv[1];
        argv[0] = Boolean::New(work->has_alert);

        node::MakeCallback(Context::GetCurrent()->Global(),
            work->callback,
            1,
            argv);

        work->callback.Dispose();
        work->callback.Clear();

        delete work;
    }

    Handle<Value> Session::SetAlertMask(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            int mask = args[0]->IntegerValue();
            Session::Unwrap(args.This())->set_alert_mask(mask);
        }

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::StopLsd(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->stop_lsd();
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::StartLsd(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->start_lsd();
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::StopUpnp(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->stop_upnp();
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::StartUpnp(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->start_upnp();
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::DeletePortMapping(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 0) {
            int handle = args[0]->IntegerValue();
            Session::Unwrap(args.This())->delete_port_mapping(handle);
        }

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::AddPortMapping(const Arguments &args) {
        HandleScope handle_scope;

        if(args.Length() > 2) {
            int protocol_type = args[0]->IntegerValue();
            int external_port = args[1]->IntegerValue();
            int local_port    = args[2]->IntegerValue();

            Session::Unwrap(args.This())->add_port_mapping((libtorrent::session::protocol_type) protocol_type,
                external_port,
                local_port);
        }

        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::StopNatpmp(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->stop_natpmp();
        return handle_scope.Close(Undefined());
    }

    Handle<Value> Session::StartNatpmp(const Arguments &args) {
        HandleScope handle_scope;

        Session::Unwrap(args.This())->start_natpmp();
        return handle_scope.Close(Undefined());
    }
}
