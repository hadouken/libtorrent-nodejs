#include <node.h>
#include <libtorrent/alert.hpp>
#include <libtorrent/alert_types.hpp>

#include "alert.h"
#include "alert_types.h"

using namespace libtorrent;
using namespace v8;

#define ALERT_CASE(AlertType, ClassName) \
    case AlertType::alert_type: \
        ClassName::ExtendObject(static_cast<AlertType const &>(alert), obj); \
        break;

namespace lt {
    Handle<Value> Alert::ToObject(const alert &alert) {
        HandleScope handle_scope;
        Local<Object> obj = Object::New();

        // common
        // TODO timestamp obj->Set(String::NewSymbol())
        obj->Set(String::NewSymbol("type"), Integer::New(alert.type()));
        obj->Set(String::NewSymbol("what"), String::New(alert.what()));
        obj->Set(String::NewSymbol("message"), String::New(alert.message().c_str()));
        obj->Set(String::NewSymbol("category"), Integer::New(alert.category()));
        obj->Set(String::NewSymbol("discardable"), Boolean::New(alert.discardable()));

        switch(alert.type()) {
            ALERT_CASE(torrent_added_alert,             TorrentAlert)
            ALERT_CASE(torrent_removed_alert,           TorrentRemovedAlert)
            ALERT_CASE(read_piece_alert,                ReadPieceAlert)
            ALERT_CASE(file_completed_alert,            FileCompletedAlert)
            ALERT_CASE(file_renamed_alert,              FileRenamedAlert)
            ALERT_CASE(file_rename_failed_alert,        FileRenameFailedAlert)
            ALERT_CASE(performance_alert,               PerformanceAlert)
            ALERT_CASE(state_changed_alert,             StateChangedAlert)
            ALERT_CASE(tracker_error_alert,             TrackerErrorAlert)
            ALERT_CASE(tracker_warning_alert,           TrackerWarningAlert)
            ALERT_CASE(scrape_reply_alert,              ScrapeReplyAlert)
            ALERT_CASE(scrape_failed_alert,             ScrapeFailedAlert)
            ALERT_CASE(tracker_reply_alert,             TrackerReplyAlert)
            ALERT_CASE(dht_reply_alert,                 DhtReplyAlert)
            ALERT_CASE(hash_failed_alert,               HashFailedAlert)
            ALERT_CASE(peer_ban_alert,                  PeerAlert)
            ALERT_CASE(peer_unsnubbed_alert,            PeerAlert)
            ALERT_CASE(peer_snubbed_alert,              PeerAlert)
            ALERT_CASE(peer_error_alert,                PeerErrorAlert)
            ALERT_CASE(peer_connect_alert,              PeerConnectAlert)
            ALERT_CASE(peer_disconnected_alert,         PeerDisconnectedAlert)
            ALERT_CASE(invalid_request_alert,           InvalidRequestAlert)
            ALERT_CASE(torrent_finished_alert,          TorrentAlert)
            ALERT_CASE(piece_finished_alert,            PieceFinishedAlert)
            ALERT_CASE(request_dropped_alert,           RequestDroppedAlert)
            ALERT_CASE(block_timeout_alert,             BlockTimeoutAlert)
            ALERT_CASE(block_finished_alert,            BlockFinishedAlert)
            ALERT_CASE(block_downloading_alert,         BlockDownloadingAlert)
            ALERT_CASE(unwanted_block_alert,            UnwantedBlockAlert)
            ALERT_CASE(storage_moved_alert,             StorageMovedAlert)
            ALERT_CASE(storage_moved_failed_alert,      StorageMovedFailedAlert)
            ALERT_CASE(torrent_deleted_alert,           TorrentDeletedAlert)
            ALERT_CASE(torrent_delete_failed_alert,     TorrentDeleteFailedAlert)
            ALERT_CASE(save_resume_data_alert,          SaveResumeDataAlert)
            ALERT_CASE(save_resume_data_failed_alert,   SaveResumeDataFailedAlert)
            ALERT_CASE(torrent_paused_alert,            TorrentAlert)
            ALERT_CASE(torrent_resumed_alert,           TorrentAlert)
            ALERT_CASE(torrent_checked_alert,           TorrentAlert)
            ALERT_CASE(url_seed_alert,                  UrlSeedAlert)
            ALERT_CASE(file_error_alert,                FileErrorAlert)
            ALERT_CASE(metadata_failed_alert,           MetadataFailedAlert)
            ALERT_CASE(metadata_received_alert,         TorrentAlert)
            ALERT_CASE(udp_error_alert,                 UdpErrorAlert)
            ALERT_CASE(external_ip_alert,               ExternalIpAlert)
            ALERT_CASE(listen_failed_alert,             ListenFailedAlert)
            ALERT_CASE(listen_succeeded_alert,          ListenSucceededAlert)
            ALERT_CASE(portmap_error_alert,             PortmapErrorAlert)
            ALERT_CASE(portmap_alert,                   PortmapAlert)
            ALERT_CASE(portmap_log_alert,               PortmapLogAlert)
            ALERT_CASE(fastresume_rejected_alert,       FastresumeRejectedAlert)
            ALERT_CASE(peer_blocked_alert,              PeerBlockedAlert)
            ALERT_CASE(dht_announce_alert,              DhtAnnounceAlert)
            ALERT_CASE(dht_get_peers_alert,             DhtGetPeersAlert)
            ALERT_CASE(stats_alert,                     StatsAlert)
            ALERT_CASE(cache_flushed_alert,             TorrentAlert)
            ALERT_CASE(anonymous_mode_alert,            AnonymousModeAlert)
            ALERT_CASE(lsd_peer_alert,                  PeerAlert)
            ALERT_CASE(trackerid_alert,                 TrackeridAlert)
            //ALERT_CASE(dht_bootstrap_alert,             DhtBootstrapAlert) // Unused
            ALERT_CASE(rss_alert,                       RssAlert)
            ALERT_CASE(torrent_error_alert,             TorrentErrorAlert)
            ALERT_CASE(torrent_need_cert_alert,         TorrentNeedCertAlert)
            ALERT_CASE(incoming_connection_alert,       IncomingConnectionAlert)
            ALERT_CASE(add_torrent_alert,               AddTorrentAlert)
            ALERT_CASE(state_update_alert,              StateUpdateAlert)
            ALERT_CASE(torrent_update_alert,            TorrentUpdateAlert)
            ALERT_CASE(rss_item_alert,                  RssItemAlert)
            ALERT_CASE(dht_error_alert,                 DhtErrorAlert)
            ALERT_CASE(dht_immutable_item_alert,        DhtImmutableItemAlert)
            ALERT_CASE(dht_mutable_item_alert,          DhtMutableItemAlert)
            ALERT_CASE(dht_put_alert,                   DhtPutAlert)
            ALERT_CASE(i2p_alert,                       I2pAlert)
        }

        return handle_scope.Close(obj);
    }
}