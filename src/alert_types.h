#ifndef TORRENT_ADDED_ALERT_H
#define TORRENT_ADDED_ALERT_H

#include <node.h>
#include <libtorrent/alert_types.hpp>

#define ALERT(ClassName, AlertType) \
    class ClassName { \
    public: \
        static void ExtendObject(const libtorrent::AlertType &alert, v8::Local<v8::Object> obj); \
    };

namespace lt {
    class TorrentAlert {
    public:
        static void ExtendObject(const libtorrent::torrent_alert &alert, v8::Local<v8::Object> obj);
    };

    class PeerAlert {
    public:
        static void ExtendObject(const libtorrent::peer_alert &alert, v8::Local<v8::Object> obj);
    };

    class TrackerAlert {
    public:
        static void ExtendObject(const libtorrent::tracker_alert &alert, v8::Local<v8::Object> obj);
    };

    ALERT(TorrentRemovedAlert,          torrent_removed_alert)
    ALERT(ReadPieceAlert,               read_piece_alert)
    ALERT(FileCompletedAlert,           file_completed_alert)
    ALERT(FileRenamedAlert,             file_renamed_alert)
    ALERT(FileRenameFailedAlert,        file_rename_failed_alert)
    ALERT(PerformanceAlert,             performance_alert)
    ALERT(StateChangedAlert,            state_changed_alert)
    ALERT(TrackerErrorAlert,            tracker_error_alert)
    ALERT(TrackerWarningAlert,          tracker_warning_alert)
    ALERT(ScrapeReplyAlert,             scrape_reply_alert)
    ALERT(ScrapeFailedAlert,            scrape_failed_alert)
    ALERT(TrackerReplyAlert,            tracker_reply_alert)
    ALERT(DhtReplyAlert,                dht_reply_alert)
    ALERT(TrackerAnnounceAlert,         tracker_announce_alert)
    ALERT(HashFailedAlert,              hash_failed_alert)
    ALERT(PeerErrorAlert,               peer_error_alert)
    ALERT(PeerConnectAlert,             peer_connect_alert)
    ALERT(PeerDisconnectedAlert,        peer_disconnected_alert)
    ALERT(InvalidRequestAlert,          invalid_request_alert)
    ALERT(PieceFinishedAlert,           piece_finished_alert)
    ALERT(RequestDroppedAlert,          request_dropped_alert)
    ALERT(BlockTimeoutAlert,            block_timeout_alert)
    ALERT(BlockFinishedAlert,           block_finished_alert)
    ALERT(BlockDownloadingAlert,        block_downloading_alert)
    ALERT(UnwantedBlockAlert,           unwanted_block_alert)
    ALERT(StorageMovedAlert,            storage_moved_alert)
    ALERT(StorageMovedFailedAlert,      storage_moved_failed_alert)
    ALERT(TorrentDeletedAlert,          torrent_deleted_alert)
    ALERT(TorrentDeleteFailedAlert,     torrent_delete_failed_alert)
    ALERT(SaveResumeDataAlert,          save_resume_data_alert)
    ALERT(SaveResumeDataFailedAlert,    save_resume_data_failed_alert)
    ALERT(UrlSeedAlert,                 url_seed_alert)
    ALERT(FileErrorAlert,               file_error_alert)
    ALERT(MetadataFailedAlert,          metadata_failed_alert)
    ALERT(UdpErrorAlert,                udp_error_alert)
    ALERT(ExternalIpAlert,              external_ip_alert)
    ALERT(ListenFailedAlert,            listen_failed_alert)
    ALERT(ListenSucceededAlert,         listen_succeeded_alert)
    ALERT(PortmapErrorAlert,            portmap_error_alert)
    ALERT(PortmapAlert,                 portmap_alert)
    ALERT(PortmapLogAlert,              portmap_log_alert)
    ALERT(FastresumeRejectedAlert,      fastresume_rejected_alert)
    ALERT(PeerBlockedAlert,             peer_blocked_alert)
    ALERT(DhtAnnounceAlert,             dht_announce_alert)
    ALERT(DhtGetPeersAlert,             dht_get_peers_alert)
    ALERT(StatsAlert,                   stats_alert)
    ALERT(AnonymousModeAlert,           anonymous_mode_alert)
    ALERT(TrackeridAlert,               trackerid_alert)
    ALERT(RssAlert,                     rss_alert)
    ALERT(TorrentErrorAlert,            torrent_error_alert)
    ALERT(TorrentNeedCertAlert,         torrent_need_cert_alert)
    ALERT(IncomingConnectionAlert,      incoming_connection_alert)
    ALERT(AddTorrentAlert,              add_torrent_alert)
    ALERT(StateUpdateAlert,             state_update_alert)
    ALERT(TorrentUpdateAlert,           torrent_update_alert)
    ALERT(RssItemAlert,                 rss_item_alert)
    ALERT(DhtErrorAlert,                dht_error_alert)
    ALERT(DhtImmutableItemAlert,        dht_immutable_item_alert)
    ALERT(DhtMutableItemAlert,          dht_mutable_item_alert)
    ALERT(DhtPutAlert,                  dht_put_alert)
    ALERT(I2pAlert,                     i2p_alert)
}

#endif