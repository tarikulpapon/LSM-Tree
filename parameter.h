/*
 *  Created on: October 24, 2019
 *  Author: Papon
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_
 

#include <iostream>

using namespace std;


class EmuEnv
{
private:
  EmuEnv(); 
  static EmuEnv *instance;

public:
  static EmuEnv* getInstance();

  int size_ratio; // T

  int buffer_size_in_pages; // P
  int entries_per_page; // B
  int entry_size; // E ; in Bytes
  long buffer_size; // M = P*B*E ; in Bytes

  float buffer_flush_threshold;
  float disk_run_flush_threshold;

  int num_inserts;
  int verbosity;

};

#endif /*PARAMETER_H_*/

