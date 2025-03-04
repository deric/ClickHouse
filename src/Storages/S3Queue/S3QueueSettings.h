#pragma once

#include <Core/BaseSettings.h>
#include <Core/Settings.h>
#include <Core/SettingsEnums.h>


namespace DB
{
class ASTStorage;


#define S3QUEUE_RELATED_SETTINGS(M, ALIAS) \
    M(S3QueueMode, \
      mode, \
      S3QueueMode::ORDERED, \
      "With unordered mode, the set of all already processed files is tracked with persistent nodes in ZooKepeer." \
      "With ordered mode, only the max name of the successfully consumed file stored.", \
      0) \
    M(S3QueueAction, after_processing, S3QueueAction::KEEP, "Delete or keep file in S3 after successful processing", 0) \
    M(String, keeper_path, "", "Zookeeper node path", 0) \
    M(UInt64, s3queue_loading_retries, 0, "Retry loading up to specified number of times", 0) \
    M(UInt64, s3queue_polling_min_timeout_ms, 1000, "Minimal timeout before next polling", 0) \
    M(UInt64, s3queue_polling_max_timeout_ms, 10000, "Maximum timeout before next polling", 0) \
    M(UInt64, s3queue_polling_backoff_ms, 0, "Polling backoff", 0) \
    M(UInt64, s3queue_tracked_files_limit, 1000, "Max set size for tracking processed files in unordered mode in ZooKeeper", 0) \
    M(UInt64, \
      s3queue_tracked_file_ttl_sec, \
      0, \
      "Maximum number of seconds to store processed files in ZooKeeper node (store forever by default)", \
      0) \
    M(UInt64, s3queue_polling_size, 50, "Maximum files to fetch from S3 with SELECT", 0)

#define LIST_OF_S3QUEUE_SETTINGS(M, ALIAS) \
    S3QUEUE_RELATED_SETTINGS(M, ALIAS) \
    FORMAT_FACTORY_SETTINGS(M, ALIAS)

DECLARE_SETTINGS_TRAITS(S3QueueSettingsTraits, LIST_OF_S3QUEUE_SETTINGS)


struct S3QueueSettings : public BaseSettings<S3QueueSettingsTraits>
{
    void loadFromQuery(ASTStorage & storage_def);
};

}
