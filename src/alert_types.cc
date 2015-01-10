#include <node.h>
#include <libtorrent/alert_types.hpp>

#include "alert_types.h"
#include "torrent_handle.h"
#include "torrent_status.h"

using namespace libtorrent;
using namespace v8;

namespace lt {
    void TorrentAlert::ExtendObject(const torrent_alert &alert, Local<Object> obj) {
        obj->Set(String::NewSymbol("handle"), TorrentHandle::New(alert.handle));
    }

    void PeerAlert::ExtendObject(const peer_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);

        Local<Array> ip = Array::New(2);
        ip->Set(0, String::New(alert.ip.address().to_string().c_str()));
        ip->Set(1, Integer::New(alert.ip.port()));

        obj->Set(String::NewSymbol("ip"), ip);
        // TODO peer id
    }

    void TrackerAlert::ExtendObject(const tracker_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("url"), String::New(alert.url.c_str()));
    }

    void TorrentRemovedAlert::ExtendObject(const torrent_removed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("info_hash"), String::New(alert.info_hash.to_string().c_str()));
    }

    void ReadPieceAlert::ExtendObject(const read_piece_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        // TODO error code obj->Set(Strin// )
        // TODO buffer obj->Set(String::NewSymbol())
        obj->Set(String::NewSymbol("piece"), Integer::New(alert.piece));
        obj->Set(String::NewSymbol("size"), Integer::New(alert.size));
    }

    void FileCompletedAlert::ExtendObject(const file_completed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("index"), Integer::New(alert.index));
    }

    void FileRenamedAlert::ExtendObject(const file_renamed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("name"), String::New(alert.name.c_str()));
        obj->Set(String::NewSymbol("index"), Integer::New(alert.index));
    }

    void FileRenameFailedAlert::ExtendObject(const file_rename_failed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("index"), Integer::New(alert.index));
        // TODO error code obj->Set(String::NewSymbol("index", Integer::New(alert.index)));
    }

    void PerformanceAlert::ExtendObject(const performance_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("warning_code"), Integer::New(alert.warning_code));
    }

    void StateChangedAlert::ExtendObject(const state_changed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("state"), Integer::New(alert.state));
        obj->Set(String::NewSymbol("prev_state"), Integer::New(alert.prev_state));
    }

    void TrackerErrorAlert::ExtendObject(const tracker_error_alert &alert, Local<Object> obj) {
        TrackerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("times_in_row"), Integer::New(alert.times_in_row));
        obj->Set(String::NewSymbol("status_code"), Integer::New(alert.status_code));
        // TODO error code obj->Set(String::NewSymbol("status_code"), Integer::New(alert.status_code));
        obj->Set(String::NewSymbol("msg"), String::New(alert.msg.c_str()));
    }

    void TrackerWarningAlert::ExtendObject(const tracker_warning_alert &alert, Local<Object> obj) {
        TrackerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("msg"), String::New(alert.msg.c_str()));
    }

    void ScrapeReplyAlert::ExtendObject(const scrape_reply_alert &alert, Local<Object> obj) {
        TrackerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("incomplete"), Integer::New(alert.incomplete));
        obj->Set(String::NewSymbol("complete"), Integer::New(alert.complete));
    }

    void ScrapeFailedAlert::ExtendObject(const scrape_failed_alert &alert, Local<Object> obj) {
        TrackerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("msg"), String::New(alert.msg.c_str()));
    }

    void TrackerReplyAlert::ExtendObject(const tracker_reply_alert &alert, Local<Object> obj) {
        TrackerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("num_peers"), Integer::New(alert.num_peers));
    }

    void DhtReplyAlert::ExtendObject(const dht_reply_alert &alert, Local<Object> obj) {
        TrackerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("num_peers"), Integer::New(alert.num_peers));
    }

    void TrackerAnnounceAlert::ExtendObject(const tracker_announce_alert &alert, Local<Object> obj) {
        TrackerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("event"), Integer::New(alert.event));
    }

    void HashFailedAlert::ExtendObject(const hash_failed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("piece_index"), Integer::New(alert.piece_index));
    }

    void PeerErrorAlert::ExtendObject(const peer_error_alert &alert, Local<Object> obj) {
        PeerAlert::ExtendObject(alert, obj);
        // TODO error code obj->Set
    }

    void PeerConnectAlert::ExtendObject(const peer_connect_alert &alert, Local<Object> obj) {
        PeerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("socket_type"), Integer::New(alert.socket_type));
    }

    void PeerDisconnectedAlert::ExtendObject(const peer_disconnected_alert &alert, Local<Object> obj) {
        PeerAlert::ExtendObject(alert, obj);
        // TODO error code obj->Set(String::NewSymbol(""))
    }

    void InvalidRequestAlert::ExtendObject(const invalid_request_alert &alert, Local<Object> obj) {
        PeerAlert::ExtendObject(alert, obj);
        // TODO peer request
    }

    void PieceFinishedAlert::ExtendObject(const piece_finished_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("piece_index"), Integer::New(alert.piece_index));
    }

    void RequestDroppedAlert::ExtendObject(const request_dropped_alert &alert, Local<Object> obj) {
        PeerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("block_index"), Integer::New(alert.block_index));
        obj->Set(String::NewSymbol("piece_index"), Integer::New(alert.piece_index));
    }

    void BlockTimeoutAlert::ExtendObject(const block_timeout_alert &alert, Local<Object> obj) {
        PeerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("block_index"), Integer::New(alert.block_index));
        obj->Set(String::NewSymbol("piece_index"), Integer::New(alert.piece_index));
    }

    void BlockFinishedAlert::ExtendObject(const block_finished_alert &alert, Local<Object> obj) {
        PeerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("block_index"), Integer::New(alert.block_index));
        obj->Set(String::NewSymbol("piece_index"), Integer::New(alert.piece_index));
    }

    void BlockDownloadingAlert::ExtendObject(const block_downloading_alert &alert, Local<Object> obj) {
        PeerAlert::ExtendObject(alert, obj);
        // TODO peer_speedmsg
        obj->Set(String::NewSymbol("block_index"), Integer::New(alert.block_index));
        obj->Set(String::NewSymbol("piece_index"), Integer::New(alert.piece_index));
    }

    void UnwantedBlockAlert::ExtendObject(const unwanted_block_alert &alert, Local<Object> obj) {
        PeerAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("block_index"), Integer::New(alert.block_index));
        obj->Set(String::NewSymbol("piece_index"), Integer::New(alert.piece_index));
    }

    void StorageMovedAlert::ExtendObject(const storage_moved_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("path"), String::New(alert.path.c_str()));
    }

    void StorageMovedFailedAlert::ExtendObject(const storage_moved_failed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        // TODO error code
    }

    void TorrentDeletedAlert::ExtendObject(const torrent_deleted_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("info_hash"), String::New(alert.info_hash.to_string().c_str()));
    }

    void TorrentDeleteFailedAlert::ExtendObject(const torrent_delete_failed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("info_hash"), String::New(alert.info_hash.to_string().c_str()));
        // TODO error code
    }

    void SaveResumeDataAlert::ExtendObject(const save_resume_data_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        // TODO resume data
    }

    void SaveResumeDataFailedAlert::ExtendObject(const save_resume_data_failed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        // TODO error code
    }

    void UrlSeedAlert::ExtendObject(const url_seed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("url"), String::New(alert.url.c_str()));
        obj->Set(String::NewSymbol("msg"), String::New(alert.msg.c_str()));
    }

    void FileErrorAlert::ExtendObject(const file_error_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("file"), String::New(alert.file.c_str()));
        // TODO error code
    }

    void MetadataFailedAlert::ExtendObject(const metadata_failed_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        // TODO error code
    }

    void UdpErrorAlert::ExtendObject(const udp_error_alert &alert, Local<Object> obj) {
        Local<Array> endpoint = Array::New(2);
        endpoint->Set(0, String::New(alert.endpoint.address().to_string().c_str()));
        endpoint->Set(1, Integer::New(alert.endpoint.port()));

        obj->Set(String::NewSymbol("endpoint"), endpoint);
        // TODO error code
    }

    void ExternalIpAlert::ExtendObject(const external_ip_alert &alert, Local<Object> obj) {
        obj->Set(String::NewSymbol("external_address"), String::New(alert.external_address.to_string().c_str()));
    }

    void ListenFailedAlert::ExtendObject(const listen_failed_alert &alert, Local<Object> obj) {
        Local<Array> endpoint = Array::New(2);
        endpoint->Set(0, String::New(alert.endpoint.address().to_string().c_str()));
        endpoint->Set(1, Integer::New(alert.endpoint.port()));

        obj->Set(String::NewSymbol("endpoint"), endpoint);
        // TODO error code
        obj->Set(String::NewSymbol("operation"), Integer::New(alert.operation));
        obj->Set(String::NewSymbol("sock_type"), Integer::New(alert.sock_type));
    }

    void ListenSucceededAlert::ExtendObject(const listen_succeeded_alert &alert, Local<Object> obj) {
        Local<Array> endpoint = Array::New(2);
        endpoint->Set(0, String::New(alert.endpoint.address().to_string().c_str()));
        endpoint->Set(1, Integer::New(alert.endpoint.port()));

        obj->Set(String::NewSymbol("endpoint"), endpoint);
        obj->Set(String::NewSymbol("sock_type"), Integer::New(alert.sock_type));
    }

    void PortmapErrorAlert::ExtendObject(const portmap_error_alert &alert, Local<Object> obj) {
        obj->Set(String::NewSymbol("mapping"), Integer::New(alert.mapping));
        obj->Set(String::NewSymbol("map_type"), Integer::New(alert.map_type));
        // TODO error code
    }

    void PortmapAlert::ExtendObject(const portmap_alert &alert, Local<Object> obj) {
        obj->Set(String::NewSymbol("mapping"), Integer::New(alert.mapping));
        obj->Set(String::NewSymbol("external_port"), Integer::New(alert.external_port));
        obj->Set(String::NewSymbol("map_type"), Integer::New(alert.map_type));
    }

    void PortmapLogAlert::ExtendObject(const portmap_log_alert &alert, Local<Object> obj) {
        obj->Set(String::NewSymbol("map_type"), Integer::New(alert.map_type));
        obj->Set(String::NewSymbol("msg"), String::New(alert.msg.c_str()));
    }

    void FastresumeRejectedAlert::ExtendObject(const fastresume_rejected_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        // TODO error code
    }

    void PeerBlockedAlert::ExtendObject(const peer_blocked_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("ip"), String::New(alert.ip.to_string().c_str()));
        obj->Set(String::NewSymbol("reason"), Integer::New(alert.reason));
    }

    void DhtAnnounceAlert::ExtendObject(const dht_announce_alert &alert, Local<Object> obj) {
        obj->Set(String::NewSymbol("ip"), String::New(alert.ip.to_string().c_str()));
        obj->Set(String::NewSymbol("port"), Integer::New(alert.port));
        obj->Set(String::NewSymbol("info_hash"), String::New(alert.info_hash.to_string().c_str()));
    }

    void DhtGetPeersAlert::ExtendObject(const dht_get_peers_alert &alert, Local<Object> obj) {
        obj->Set(String::NewSymbol("info_hash"), String::New(alert.info_hash.to_string().c_str()));
    }

    void StatsAlert::ExtendObject(const stats_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);

        obj->Set(String::NewSymbol("upload_payload"), Integer::New(stats_alert::stats_channel::upload_payload));
        obj->Set(String::NewSymbol("upload_protocol"), Integer::New(stats_alert::stats_channel::upload_protocol));
        obj->Set(String::NewSymbol("download_payload"), Integer::New(stats_alert::stats_channel::download_payload));
        obj->Set(String::NewSymbol("download_protocol"), Integer::New(stats_alert::stats_channel::download_protocol));
        obj->Set(String::NewSymbol("upload_ip_protocol"), Integer::New(stats_alert::stats_channel::upload_ip_protocol));
        obj->Set(String::NewSymbol("upload_dht_protocol"), Integer::New(stats_alert::stats_channel::upload_dht_protocol));
        obj->Set(String::NewSymbol("upload_tracker_protocol"), Integer::New(stats_alert::stats_channel::upload_tracker_protocol));
        obj->Set(String::NewSymbol("download_ip_protocol"), Integer::New(stats_alert::stats_channel::download_ip_protocol));
        obj->Set(String::NewSymbol("download_dht_protocol"), Integer::New(stats_alert::stats_channel::download_dht_protocol));
        obj->Set(String::NewSymbol("download_tracker_protocol"), Integer::New(stats_alert::stats_channel::download_tracker_protocol));
        obj->Set(String::NewSymbol("interval"), Integer::New(alert.interval));
    }

    void AnonymousModeAlert::ExtendObject(const anonymous_mode_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("kind"), Integer::New(alert.kind));
        obj->Set(String::NewSymbol("str"), String::New(alert.str.c_str()));
    }

    void TrackeridAlert::ExtendObject(const trackerid_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("trackerid"), String::New(alert.trackerid.c_str()));
    }

    void RssAlert::ExtendObject(const rss_alert &alert, Local<Object> obj) {
        // TODO feed_handle
        obj->Set(String::NewSymbol("url"), String::New(alert.url.c_str()));
        obj->Set(String::NewSymbol("state"), Integer::New(alert.state));
        // TODO error code
    }

    void TorrentErrorAlert::ExtendObject(const torrent_error_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        // TODO error code
    }

    void TorrentNeedCertAlert::ExtendObject(const torrent_need_cert_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        // TODO error code
    }

    void IncomingConnectionAlert::ExtendObject(const incoming_connection_alert &alert, Local<Object> obj) {
        Local<Array> endpoint = Array::New(2);
        endpoint->Set(0, String::New(alert.ip.address().to_string().c_str()));
        endpoint->Set(1, Integer::New(alert.ip.port()));

        obj->Set(String::NewSymbol("ip"), endpoint);
        obj->Set(String::NewSymbol("socket_type"), Integer::New(alert.socket_type));
    }

    void AddTorrentAlert::ExtendObject(const add_torrent_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        // TODO add torrent params
        // TODO error code
    }

    void StateUpdateAlert::ExtendObject(const state_update_alert &alert, Local<Object> obj) {
        Local<Array> status = Array::New(alert.status.size());

        for(int i = 0; i < alert.status.size(); i++) {
            status->Set(i, TorrentStatus::ToObject(alert.status[i]));
        }

        obj->Set(String::NewSymbol("status"), status);
    }

    void TorrentUpdateAlert::ExtendObject(const torrent_update_alert &alert, Local<Object> obj) {
        TorrentAlert::ExtendObject(alert, obj);
        obj->Set(String::NewSymbol("old_ih"), String::New(alert.old_ih.to_string().c_str()));
        obj->Set(String::NewSymbol("new_ih"), String::New(alert.new_ih.to_string().c_str()));
    }

    void RssItemAlert::ExtendObject(const rss_item_alert &alert, Local<Object> obj) {
        // TODO feed handle
        // TODO feed item
    }

    void DhtErrorAlert::ExtendObject(const dht_error_alert &alert, Local<Object> obj) {
        // TODO error code
        obj->Set(String::NewSymbol("operation"), Integer::New(alert.operation));
    }

    void DhtImmutableItemAlert::ExtendObject(const dht_immutable_item_alert &alert, Local<Object> obj) {
        obj->Set(String::NewSymbol("target"), String::New(alert.target.to_string().c_str()));
        // TODO entry item
    }

    void DhtMutableItemAlert::ExtendObject(const dht_mutable_item_alert &alert, Local<Object> obj) {
        // TODO key
        // TODO signature
        obj->Set(String::NewSymbol("seq"), Integer::New(alert.seq));
        obj->Set(String::NewSymbol("salt"), String::New(alert.salt.c_str()));
        // TODO item
    }

    void DhtPutAlert::ExtendObject(const dht_put_alert &alert, Local<Object> obj) {
        obj->Set(String::NewSymbol("target"), String::New(alert.target.to_string().c_str()));
        // TODO public_key
        // TODO signature
        obj->Set(String::NewSymbol("seq"), Integer::New(alert.seq));
        obj->Set(String::NewSymbol("salt"), String::New(alert.salt.c_str()));
        // TODO item
    }

    void I2pAlert::ExtendObject(const i2p_alert &alert, Local<Object> obj) {
        // TODO error code
    }
}