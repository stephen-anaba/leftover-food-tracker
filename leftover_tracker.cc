// Stephen Anaba
// CPSC 121L-16
// 5/10/26
// stevoclock@csu.fullerton.edu
// 3takita

#include "leftover_tracker.h"

LeftoverTracker::LeftoverTracker() = default;
// non-default constructor
LeftoverTracker::LeftoverTracker(const std::vector<LeftoverRecord>& record_list)
    : record_list_(record_list) {}

// =================================================================
// Precondition: User has created a leftover record
// Postcondition: Adds new record_list_ & return true if successful,
// else returns false. Avoids duplicate records
// ==================================================================
bool LeftoverTracker::AddRecord(const LeftoverRecord& new_record) {  // DONE
  // input validation
  if (new_record.GetDate().empty() || new_record.GetMeal().empty() ||
      new_record.GetName().empty()) {
    std::cout << "ERROR: Incomplete record\n";
    return false;
  }

  for (const LeftoverRecord& existing_record : record_list_) {
    if (existing_record == new_record) {
      return false;
    }
  }
  record_list_.push_back(new_record);
  return true;
}  // end of AddRecord()

// ===================================================================
// Precondition: User has created leftover record(s)
// Postcondition: Delete `record` from record_list_ & return true, else
// returns false
// ==================================================================
bool LeftoverTracker::DeleteRecord(const LeftoverRecord& record) {  // DONE
  // find the iterator 'it' of  matching record.
  auto it = std::find(record_list_.begin(), record_list_.end(), record);
  // if the target record does not exists, just return false
  if (it == record_list_.end()) {
    return false;
  }
  // but if it exists, erase it
  record_list_.erase(it);
  return true;  // return true
}

// ====================================================================
// Precondition: User has entered leftover record(s)
// Postcondition: Provides external classes or functions the means to access
// list of leftover record from memory
// ====================================================================
std::vector<LeftoverRecord> LeftoverTracker::GetRecords() const {  // DONE
  return record_list_;
}

// ====================================================================
// Precondition: User has created leftover record(s)
// Postcondition: Generates and returns the leftover report
// ====================================================================
LeftoverReport LeftoverTracker::GenerateLeftoverReport() const {
  // instantiate a LeftoverReport object using record_list_
  return LeftoverReport(record_list_);
}
