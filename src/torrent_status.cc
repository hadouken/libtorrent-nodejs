#include <node.h>

#include "torrent_handle.h"
#include "torrent_status.h"

using namespace v8;

namespace lt {
    Handle<Value> TorrentStatus::ToObject(const libtorrent::torrent_status &status) {
        HandleScope handle_scope;
        Local<Object> obj = Object::New();

        obj->Set(String::NewSymbol("handle"), TorrentHandle::New(status.handle), v8::ReadOnly);
        obj->Set(String::NewSymbol("error"), String::New(status.error.c_str()), v8::ReadOnly);
        obj->Set(String::NewSymbol("save_path"), String::New(status.save_path.c_str()), v8::ReadOnly);
        obj->Set(String::NewSymbol("name"), String::New(status.name.c_str()), v8::ReadOnly);
        obj->Set(String::NewSymbol("next_announce"), Number::New(status.next_announce.total_seconds()), v8::ReadOnly);
        obj->Set(String::NewSymbol("announce_interval"), Number::New(status.announce_interval.total_seconds()), v8::ReadOnly);
        obj->Set(String::NewSymbol("current_tracker"), String::New(status.current_tracker.c_str()), v8::ReadOnly);
        obj->Set(String::NewSymbol("total_download"), Number::New(status.total_download), v8::ReadOnly);
        obj->Set(String::NewSymbol("total_upload"), Number::New(status.total_upload), v8::ReadOnly);
        obj->Set(String::NewSymbol("total_payload_download"), Number::New(status.total_payload_download), v8::ReadOnly);
        obj->Set(String::NewSymbol("total_payload_upload"), Number::New(status.total_payload_upload), v8::ReadOnly);
        obj->Set(String::NewSymbol("total_failed_bytes"), Number::New(status.total_failed_bytes), v8::ReadOnly);
        obj->Set(String::NewSymbol("total_redundant_bytes"), Number::New(status.total_redundant_bytes), v8::ReadOnly);
        obj->Set(String::NewSymbol("total_download"), Number::New(status.total_download), v8::ReadOnly);
        // pieces obj->Set(String::NewSymbol("total_download"), Number::New(status.total_download));
        // verified_pieces obj->Set(String::NewSymbol("total_download"), Number::New(status.total_download));
        obj->Set(String::NewSymbol("total_done"), Integer::New(status.total_done), v8::ReadOnly);
        obj->Set(String::NewSymbol("total_wanted_done"), Integer::New(status.total_wanted_done), v8::ReadOnly);
        obj->Set(String::NewSymbol("total_wanted"), Integer::New(status.total_wanted), v8::ReadOnly);
        obj->Set(String::NewSymbol("all_time_upload"), Integer::New(status.all_time_upload), v8::ReadOnly);
        obj->Set(String::NewSymbol("all_time_download"), Integer::New(status.all_time_download), v8::ReadOnly);
        obj->Set(String::NewSymbol("added_time"), Date::New(((double)status.added_time)*1000), v8::ReadOnly);
        obj->Set(String::NewSymbol("completed_time"), Date::New(((double)status.completed_time)*1000), v8::ReadOnly);
        obj->Set(String::NewSymbol("last_seen_complete"), Date::New(((double)status.last_seen_complete)*1000), v8::ReadOnly);
        // storage mode obj->Set(String::NewSymbol("progress"), Number::New(status.progress));
        obj->Set(String::NewSymbol("progress"), Number::New(status.progress), v8::ReadOnly);
        obj->Set(String::NewSymbol("progress_ppm"), Integer::New(status.progress_ppm), v8::ReadOnly);
        obj->Set(String::NewSymbol("queue_position"), Integer::New(status.queue_position), v8::ReadOnly);
        obj->Set(String::NewSymbol("download_rate"), Integer::New(status.download_rate), v8::ReadOnly);
        obj->Set(String::NewSymbol("upload_rate"), Integer::New(status.upload_rate), v8::ReadOnly);
        obj->Set(String::NewSymbol("download_payload_rate"), Integer::New(status.download_payload_rate), v8::ReadOnly);
        obj->Set(String::NewSymbol("upload_payload_rate"), Integer::New(status.upload_payload_rate), v8::ReadOnly);
        obj->Set(String::NewSymbol("num_seeds"), Integer::New(status.num_seeds), v8::ReadOnly);
        obj->Set(String::NewSymbol("num_peers"), Integer::New(status.num_peers), v8::ReadOnly);
        obj->Set(String::NewSymbol("num_complete"), Integer::New(status.num_complete), v8::ReadOnly);
        obj->Set(String::NewSymbol("num_incomplete"), Integer::New(status.num_incomplete), v8::ReadOnly);
        obj->Set(String::NewSymbol("list_seeds"), Integer::New(status.list_seeds), v8::ReadOnly);
        obj->Set(String::NewSymbol("list_peers"), Integer::New(status.list_peers), v8::ReadOnly);
        obj->Set(String::NewSymbol("connect_candidates"), Integer::New(status.connect_candidates), v8::ReadOnly);
        obj->Set(String::NewSymbol("num_pieces"), Integer::New(status.num_pieces), v8::ReadOnly);
        obj->Set(String::NewSymbol("distributed_full_copies"), Integer::New(status.distributed_full_copies), v8::ReadOnly);
        obj->Set(String::NewSymbol("distributed_fraction"), Integer::New(status.distributed_fraction), v8::ReadOnly);
        obj->Set(String::NewSymbol("distributed_copies"), Number::New(status.distributed_copies), v8::ReadOnly);
        obj->Set(String::NewSymbol("block_size"), Integer::New(status.block_size), v8::ReadOnly);
        obj->Set(String::NewSymbol("num_uploads"), Integer::New(status.num_uploads), v8::ReadOnly);
        obj->Set(String::NewSymbol("num_connections"), Integer::New(status.num_connections), v8::ReadOnly);
        obj->Set(String::NewSymbol("uploads_limit"), Integer::New(status.uploads_limit), v8::ReadOnly);
        obj->Set(String::NewSymbol("connections_limit"), Integer::New(status.connections_limit), v8::ReadOnly);
        obj->Set(String::NewSymbol("up_bandwidth_queue"), Integer::New(status.up_bandwidth_queue), v8::ReadOnly);
        obj->Set(String::NewSymbol("down_bandwidth_queue"), Integer::New(status.down_bandwidth_queue), v8::ReadOnly);
        obj->Set(String::NewSymbol("time_since_upload"), Integer::New(status.time_since_upload), v8::ReadOnly);
        obj->Set(String::NewSymbol("time_since_download"), Integer::New(status.time_since_download), v8::ReadOnly);
        obj->Set(String::NewSymbol("active_time"), Integer::New(status.active_time), v8::ReadOnly);
        obj->Set(String::NewSymbol("finished_time"), Integer::New(status.finished_time), v8::ReadOnly);
        obj->Set(String::NewSymbol("seeding_time"), Integer::New(status.seeding_time), v8::ReadOnly);
        obj->Set(String::NewSymbol("seed_rank"), Integer::New(status.seed_rank), v8::ReadOnly);
        obj->Set(String::NewSymbol("last_scrape"), Integer::New(status.last_scrape), v8::ReadOnly);
        obj->Set(String::NewSymbol("sparse_regions"), Integer::New(status.sparse_regions), v8::ReadOnly);
        obj->Set(String::NewSymbol("priority"), Integer::New(status.priority), v8::ReadOnly);
        // state obj->Set(String::NewSymbol("upload_payload_rate"), Integer::New(status.upload_payload_rate));
        obj->Set(String::NewSymbol("need_save_resume"), Boolean::New(status.need_save_resume), v8::ReadOnly);
        obj->Set(String::NewSymbol("ip_filter_applies"), Boolean::New(status.ip_filter_applies), v8::ReadOnly);
        obj->Set(String::NewSymbol("upload_mode"), Boolean::New(status.upload_mode), v8::ReadOnly);
        obj->Set(String::NewSymbol("share_mode"), Boolean::New(status.share_mode), v8::ReadOnly);
        obj->Set(String::NewSymbol("super_seeding"), Boolean::New(status.super_seeding), v8::ReadOnly);
        obj->Set(String::NewSymbol("paused"), Boolean::New(status.paused), v8::ReadOnly);
        obj->Set(String::NewSymbol("auto_managed"), Boolean::New(status.auto_managed), v8::ReadOnly);
        obj->Set(String::NewSymbol("sequential_download"), Boolean::New(status.sequential_download), v8::ReadOnly);
        obj->Set(String::NewSymbol("is_seeding"), Boolean::New(status.is_seeding), v8::ReadOnly);
        obj->Set(String::NewSymbol("is_finished"), Boolean::New(status.is_finished), v8::ReadOnly);
        obj->Set(String::NewSymbol("has_metadata"), Boolean::New(status.has_metadata), v8::ReadOnly);
        obj->Set(String::NewSymbol("has_incoming"), Boolean::New(status.has_incoming), v8::ReadOnly);
        obj->Set(String::NewSymbol("seed_mode"), Boolean::New(status.seed_mode), v8::ReadOnly);
        obj->Set(String::NewSymbol("moving_storage"), Boolean::New(status.moving_storage), v8::ReadOnly);

        return handle_scope.Close(obj);
    }
}