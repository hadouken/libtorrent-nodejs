#ifndef SESSION_H
#define SESSION_H

#include <node.h>
#include <libtorrent/session.hpp>

#define LT_METHOD(MethodName) static v8::Handle<v8::Value> MethodName(const v8::Arguments &args);

namespace lt {
    class Session : public node::ObjectWrap {
        public:
            static void Initialize(v8::Handle<v8::Object> exports);
            static libtorrent::session* Unwrap(const v8::Local<v8::Object> &obj) {
                return node::ObjectWrap::Unwrap<Session>(obj)->session_;
            }

        private:
            explicit Session(v8::Local<v8::Array> args);
            ~Session();

            static v8::Handle<v8::Value> New(const v8::Arguments &args);
            //static v8::Handle<v8::Value> LoadState(const v8::Arguments &args);
            //static v8::Handle<v8::Value> SaveState(const v8::Arguments &args);
            //static v8::Handle<v8::Value> RefreshTorrentStatus(const v8::Arguments &args);
            //static v8::Handle<v8::Value> GetTorrentStatus(const v8::Arguments &args);
            LT_METHOD(PostTorrentUpdates)
            LT_METHOD(FindTorrent)
            LT_METHOD(GetTorrents)
            LT_METHOD(AsyncAddTorrent)
            LT_METHOD(AddTorrent)
            LT_METHOD(Resume)
            LT_METHOD(Pause)
            LT_METHOD(IsPaused)
            //LT_METHOD(Status)
            //LT_METHOD(GetCacheStatus)
            //LT_METHOD(GetCacheInfo)
            //LT_METHOD(AddFeed)
            //LT_METHOD(RemoveFeed)
            //LT_METHOD(GetFeeds)
            LT_METHOD(IsDhtRunning)
            LT_METHOD(StartDht)
            LT_METHOD(StopDht)
            //LT_METHOD(SetDhtSettings)
            LT_METHOD(AddDhtRouter)
            LT_METHOD(AddDhtNode)
            //LT_METHOD(DhtGetItem)
            //LT_METHOD(DhtPutItem)
            //LT_METHOD(AddExtension)
            LT_METHOD(LoadCountryDb)
            LT_METHOD(LoadAsnumDb)
            LT_METHOD(AsForIp)
            //LT_METHOD(GetIpFilter)
            //LT_METHOD(SetIpFilter)
            //LT_METHOD(SetPortFilter)
            LT_METHOD(Id);
            LT_METHOD(SetPeerId)
            LT_METHOD(SetKey)
            LT_METHOD(ListenOn)
            LT_METHOD(IsListening)
            LT_METHOD(ListenPort)
            LT_METHOD(SslListenPort)
            LT_METHOD(RemoveTorrent)
            //LT_METHOD(Settings)
            //LT_METHOD(SetSettings)
            //LT_METHOD(GetPeSettings)
            //LT_METHOD(SetPeSettings)
            //LT_METHOD(SetProxy)
            //LT_METHOD(Proxy)
            //LT_METHOD(I2pProxy)
            //LT_METHOD(SetI2pProxy)
            LT_METHOD(PopAlerts)
            LT_METHOD(PopAlert)
            LT_METHOD(WaitForAlert)
            LT_METHOD(SetAlertMask)
            //LT_METHOD(SetAlertDispatch)
            LT_METHOD(StopLsd)
            LT_METHOD(StartLsd)
            LT_METHOD(StopUpnp)
            LT_METHOD(StartUpnp)
            LT_METHOD(DeletePortMapping)
            LT_METHOD(AddPortMapping)
            LT_METHOD(StopNatpmp)
            LT_METHOD(StartNatpmp)

            static void WaitForAlertWork(uv_work_t *req);
            static void WaitForAlertAfter(uv_work_t *req, int status);
            // member variables
            libtorrent::session *session_;
    };
}

#endif