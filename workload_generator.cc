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
#include <time.h>
#include <fstream>

#include "args.hxx"
#include "workload_generator.h"

using namespace std;


/*
 * DEFINITIONS 
 * 
 */

long long WorkloadGenerator::KEY_DOMAIN_SIZE = 100000; 

int WorkloadGenerator::generateWorkload(long insert_count, long entry_size) {
  
  ofstream workload_file;
  workload_file.open("workload.txt");

  for (long i=0; i<insert_count; ++i) {
    string sortkey = generateKey();
    long value_size = entry_size - sizeof(long);
    string value = generateValue(value_size);
    workload_file << "I " << sortkey << " " << value << std::endl;
  }
  
  workload_file.close();

  return 1;
}


string WorkloadGenerator::generateKey() {
  //srand(time(0));
  unsigned long long randomness = rand() %  KEY_DOMAIN_SIZE;
  string key = std::to_string(randomness);
  return key;
}

string WorkloadGenerator::generateValue(long value_size) {
  string value = std::string(value_size, 'a' + (rand() % 26));
  return value;
}

