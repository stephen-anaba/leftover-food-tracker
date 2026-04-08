#ifndef LEFTOVER_TRACKER_H_
#define LEFTOVER_TRACKER_H_

// Stephen Anaba
// CPSC 121L-16
// 3/16/2026
// stevoclock@csu.fullerton.edu
// 3takita

#include "leftover_record.h"
#include "leftover_report.h"
#include <algorithm> // for std::find()
#include <vector> // for dynamic container
#include <iostream> // TODO: remove after test

class LeftoverTracker {
private:
  // container for leftover records created by user 
  std::vector<LeftoverRecord> record_list_; 

public:
  // default constructor
  LeftoverTracker() = default;
  // non-default constructor
  LeftoverTracker(const std::vector<LeftoverRecord>& record_list) : record_list_(record_list) {}
  
  // =================================================================
  // Precondition: User has created a leftover record
  // Postcondition: Adds new record_list_ & return true if successful,
  // else returns false. Avoids duplicate records 
  // ==================================================================
  bool AddRecord(const LeftoverRecord& new_record) { // DONE
    // input validation
    if(new_record.GetDate().empty() || new_record.GetMeal().empty() || new_record.GetName().empty()) {
      std::cout << "ERROR: Incomplete record\n";
      return false;
    }
    
    // TODO: Fix bug here that fails to add record with different date
    for (const LeftoverRecord& existing_record : record_list_) {
        if (existing_record == new_record) {
            // remove debug print statements
            std::cout << "Comparing records:\n";
            std::cout << "Existing: " 
                      << existing_record.GetDate() << ", "
                      << existing_record.GetMeal() << ", "
                      << existing_record.GetName() << "\n";

            std::cout << "New: [" 
                      << new_record.GetDate() << ", "
                      << new_record.GetMeal() << ", "
                      << new_record.GetName() << "]\n";
            
            if(existing_record == new_record) {
              std::cout << "Duplicate detected\n";
              return false;
            }
        }
    }
    // std::cout << "Adding record with date: " << new_record.GetDate() << "\n";
    record_list_.push_back(new_record);
    return true; 
  } // end of AddRecord() 
  
  // ===================================================================
  // Precondition: User has created leftover record(s)
  // Postcondition: Delete `record` from record_list_ & return true, else returns false
  // ==================================================================
  bool DeleteRecord(const LeftoverRecord& record) { // DONE 
    // find the iterator 'it' of  matching record. 
    auto it = std::find(record_list_.begin(), record_list_.end(), record); 
    // if the target record does not exists, just return false
    if(it == record_list_.end()) {
      return false;
    }
    // but if it exists, erase it
    record_list_.erase(it); 
    return true; // return true
  } 

  // ====================================================================
  // Precondition: User has entered leftover record(s)
  // Postcondition: Provides external classes or functions the means to access list of leftover record from memory
  // ====================================================================
  std::vector<LeftoverRecord> GetRecords() const { // DONE
    return record_list_;
  }

  // ====================================================================
  // Precondition: User has created leftover record(s)
  // Postcondition: Generates and returns the leftover report
  // ====================================================================
  LeftoverReport GenerateLeftoverReport() const {
    // instantiate a LeftoverReport object using record_list_
    return LeftoverReport(record_list_);  
  } 
};

#endif
