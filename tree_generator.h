/*
 *  Created on: October 24, 2019
 *  Author: Papon
 */
 
#include "parameter.h"

#include <iostream>
#include <vector>

using namespace std;

namespace awesome {

  class MemoryBuffer {
    private:
    MemoryBuffer(EmuEnv* _env);
    static MemoryBuffer* buffer_instance;
    static long max_buffer_size;

    public:
    static float buffer_flush_threshold; 
    static long current_buffer_entry_count;
    static long current_buffer_size;
    static float current_buffer_saturation;
    static int buffer_flush_count;
    static vector < pair < long, string > > buffer;
    static int verbosity;

    static MemoryBuffer* getBufferInstance(EmuEnv* _env);
    static int getCurrentBufferStatistics();
    static int setCurrentBufferStatistics(int entry_count_change, int buffer_flush_threshold);
    static int initiateBufferFlush(int level_to_flush_in);     
    static int printBufferEntries();
  };


  class Page {
    public: 
    long min_sort_key;
    long max_sort_key;
    vector < pair < long, string > > kv_vector;
    static struct vector<Page> createNewPages(int page_count);
  };

  class SSTFile {

  public: 
  int file_level;
  string file_id;
  long min_sort_key;
  long max_sort_key;

  vector < Page > page_vector;
  struct SSTFile* next_file_ptr;
  static SSTFile* createNewSSTFile(int level_to_flush_in);

  }; 


  class DiskMetaFile {
    private: 
    public:
    // static SSTFile* head_level_1;
    static int checkAndAdjustLevelSaturation(int level);
    static long getLevelEntryCount(int level);
    static int getLevelFileCount(int level);
    static int getTotalLevelCount();
    
    static int setSSTFileHead(SSTFile* arg, int level);
    static SSTFile* getSSTFileHead(int level);

    static int getMetaStatistics();
    static int printAllEntries();

    static SSTFile* level_head[32];

    static long level_min_key[32];
    static long level_max_key[32];
    static long level_file_count[32];
    static long level_entry_count[32];
    static long level_current_size[32];

    static long level_max_size[32];
    static long global_level_file_counter[32];
    static float disk_run_flush_threshold[32];

    static int compaction_counter[32];
    static int compaction_through_sortmerge_counter[32];
    static int compaction_through_point_manipulation_counter[32];
    static int compaction_file_counter[32];

  };


  class WorkloadExecutor {
    private:
    
    public:
    static long total_insert_count;
    static long buffer_update_count;
    static long buffer_insert_count;

    static int insert(long sortkey, string value);
    static int getWorkloadStatictics(EmuEnv* _env);

  };

}
