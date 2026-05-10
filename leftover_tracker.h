#ifndef LEFTOVER_TRACKER_H_
#define LEFTOVER_TRACKER_H_

// Stephen Anaba
// CPSC 121L-16
// 3/16/2026
// stevoclock@csu.fullerton.edu
// 3takita

#include <algorithm>  // for std::find()
#include <iostream>   // TODO: remove after test
#include <vector>     // for dynamic container

#include "leftover_record.h"
#include "leftover_report.h"

class LeftoverTracker {
 private:
  // container for leftover records created by user
  std::vector<LeftoverRecord> record_list_;

 public:
  // default constructor
  LeftoverTracker();  // = default;
  // non-default constructor
  LeftoverTracker(const std::vector<LeftoverRecord>& record_list);

  // =================================================================
  // Precondition: User has created a leftover record
  // Postcondition: Adds new record_list_ & return true if successful,
  // else returns false. Avoids duplicate records
  // ==================================================================
  bool AddRecord(const LeftoverRecord& new_record);

  // ===================================================================
  // Precondition: User has created leftover record(s)
  // Postcondition: Delete `record` from record_list_ & return true, else
  // returns false
  // ==================================================================
  bool DeleteRecord(const LeftoverRecord& record);

  // ====================================================================
  // Precondition: User has entered leftover record(s)
  // Postcondition: Provides external classes or functions the means to access
  // list of leftover record from memory
  // ====================================================================
  std::vector<LeftoverRecord> GetRecords() const;

  // ====================================================================
  // Precondition: User has created leftover record(s)
  // Postcondition: Generates and returns the leftover report
  // ====================================================================
  LeftoverReport GenerateLeftoverReport() const;
};

#endif
