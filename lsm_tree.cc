/*
 *  Created on: October 24, 2019
 *  Author: Papon
 */
 
#include <sstream>
#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <cmath>
#include <unistd.h>
#include <assert.h>
#include <fstream>

#include "args.hxx"
#include "parameter.h"
#include "tree_generator.h"
#include "workload_generator.h"

using namespace std;
using namespace awesome;

/*
 * DECLARATIONS
*/

int parse_arguments2(int argc, char *argvx[], EmuEnv* _env);
void printEmulationOutput(EmuEnv* _env);
int runWorkload(EmuEnv* _env);


int main(int argc, char *argvx[]) {

  // check emu_environment.h for the contents of EmuEnv and also the definitions of the singleton experimental environment 
  EmuEnv* _env = EmuEnv::getInstance();
  
  //parse the command line arguments
  if (parse_arguments2(argc, argvx, _env)){
    exit(1);
  }
  
  if (_env->num_inserts > 0) 
  {
    // if (_env->verbosity >= 1) 
      std::cerr << "Issuing inserts ... " << std::endl << std::flush; 
    
    WorkloadGenerator workload_generator;
    workload_generator.generateWorkload((long)_env->num_inserts, (long)_env->entry_size);
    int s = runWorkload(_env); 
    
    DiskMetaFile::printAllEntries();
    MemoryBuffer::getCurrentBufferStatistics();
    DiskMetaFile::getMetaStatistics();
    //WorkloadExecutor::getWorkloadStatictics(_env);
    //assert(_env->num_inserts == inserted); 
  }

  printEmulationOutput(_env);

  return 0;
}

int runWorkload(EmuEnv* _env) {

  MemoryBuffer* buffer_instance = MemoryBuffer::getBufferInstance(_env);
  awesome::WorkloadExecutor workload_executer;
  ifstream workload_file;
  workload_file.open("workload.txt");
  assert(workload_file);

  while(!workload_file.eof()) {
    char instruction;
    long sortkey;
    string value;
    workload_file >> instruction >> sortkey >> value;
    switch (instruction)
    {
      case 'I':
        //std::cout << instruction << " " << sortkey << " " << value << std::endl;
        workload_executer.insert(sortkey, value);
        break;
    }
    instruction='\0';
  }
  return 1;
}


int parse_arguments2(int argc,char *argvx[], EmuEnv* _env) {
  args::ArgumentParser parser("LSM-Tree Creator.", "");

  args::Group group1(parser, "This group is all exclusive:", args::Group::Validators::DontCare);

  args::ValueFlag<int> size_ratio_cmd(group1, "T", "Size Ratio of the LSM Tree [def: 2]", {'T', "size_ratio"});
  args::ValueFlag<int> buffer_size_in_pages_cmd(group1, "P", "The size of the memory buffer in terms of pages [def: 128]", {'P', "buffer_size_in_pages"});
  args::ValueFlag<int> entries_per_page_cmd(group1, "B", "No of entries that can fit in one page [def: 128]", {'B', "entries_per_page"});
  args::ValueFlag<int> entry_size_cmd(group1, "E", "Size of each entry in bytes [def: 128 B]", {'E', "entry_size"});
  args::ValueFlag<int> num_inserts_cmd(group1, "#Inserts", "The number of inserts to issue in the experiment [def: 0]", {'I', "num_inserts"});
  args::ValueFlag<int> verbosity_cmd(group1, "Verbosity", "The verbosity level of execution [0,1,2; def:0]", {'V', "verbosity"});

  try
  {
      parser.ParseCLI(argc, argvx);
  }
  catch (args::Help&)
  {
      std::cout << parser;
      exit(0);
      // return 0;
  }
  catch (args::ParseError& e)
  {
      std::cerr << e.what() << std::endl;
      std::cerr << parser;
      return 1;
  }
  catch (args::ValidationError& e)
  {
      std::cerr << e.what() << std::endl;
      std::cerr << parser;
      return 1;
  }

  _env->size_ratio = size_ratio_cmd ? args::get(size_ratio_cmd) : 2;
  _env->buffer_size_in_pages = buffer_size_in_pages_cmd ? args::get(buffer_size_in_pages_cmd) : 128;
  _env->entries_per_page = entries_per_page_cmd ? args::get(entries_per_page_cmd) : 128;
  _env->entry_size = entry_size_cmd ? args::get(entry_size_cmd) : 128;
  _env->buffer_size = _env->buffer_size_in_pages * _env->entries_per_page * _env->entry_size;
  _env->num_inserts = num_inserts_cmd ? args::get(num_inserts_cmd) : 0;
  _env->verbosity = verbosity_cmd ? args::get(verbosity_cmd) : 0;

  return 0;
}

void printEmulationOutput(EmuEnv* _env) {
  //if (_env->verbosity >= 1) 
  std::cout << "T, P, B, E, M, #I \n";
  std::cout << _env->size_ratio << ", ";
  std::cout << _env->buffer_size_in_pages << ", ";  
  std::cout << _env->entries_per_page << ", ";
  std::cout << _env->entry_size << ", ";
  std::cout << _env->buffer_size << ", ";
  std::cout << _env->num_inserts ;

  std::cout << std::endl;
}
