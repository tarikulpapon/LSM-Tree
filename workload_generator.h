/*
 *  Created on: October 24, 2019
 *  Author: Papon
 */

#include <iostream>
using namespace std;

class WorkloadGenerator
{
  public:
  static long long KEY_DOMAIN_SIZE;
  static int generateWorkload(long insert_count, long entry_size);
  static string generateKey();
  static string generateValue(long value_size);
};