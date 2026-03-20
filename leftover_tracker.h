#ifndef LEFTOVER_TRACKER_H_
#define LEFTOVER_TRACKER_H_

// Stephen Anaba
// CPSC 121L-01
// 3/16/2026
// stevoclock@csu.fullerton.edu
// 3takita

#include <algorithm> // for std::find()
#include <vector> // for dynamic container
// #include <unordered_set> // for set

class LeftoverTracker {
private:
  // container for leftover records created by user to be used to construct leftover report
  std::vector<LeftoverRecord> record_list_;
  // instance of LeftoverReport class
  LeftoverReport leftover_report_;
  // std::unordered_set set; // for efficient lookup
public:
  // default constructor
  LeftoverTracker() = default;
  
  // TODO: Use std::unordered_set for efficient lookup
  // Precondition: User has made a leftover record
  // Postcondition: Adds a record to record_list_, returns true if add is successful, else returns false. No duplicate records 
  bool AddRecord(const LeftoverRecord& leftover_record) {
    // if leftover_record is not in record_list, add it & 
    // return true. Else return false
    if(ContainsRecord(leftover_record) == -1) {  
      record_list_.push_back(leftover_record);
      return true;
    }
    return false; 
  } // end of AddRecord()

  // Precondition: Target must be LeftoverRecord type & record_list_ must not be empty
  // Postcondition: Returns true when target record exists in record_list_, elser returns false
  int ContainsRecord(const LeftoverRecord& target) {
    for(int i = 0; i < record_list_.size(); i++) {
      if(
          record_list_[i].GetDate() == target.GetDate() &&
          record_list_[i].GetMeal() == target.GetMeal() &&
          record_list_[i].GetName() == target.GetName() &&
          record_list_[i].GetQuantity() == target.GetQuantity() &&
          record_list_[i].GetReason() == target.GetReason() &&
          record_list_[i].GetDisposalMechanism() == target.GetDisposalMechanism() &&
          record_list_[i].GetCost() == target.GetCost()
          ) {
        return i;
      }
    }
    return -1;
  } // end of ContainsRecord(target)
  
  // Precondition: User has created leftover record(s)
  // Postcondition: Delete a record from record_list_. Return true if delete is successful, false if record not founde
  bool DeleteRecord(const LeftoverRecord& record) {
    // if not found, return false
    int found_index = ContainsRecord(record);
    if(found_index == -1) {
      return false;
    } // if found, erase record at matching index & return true
    if(record_list_.size() >= found_index) {
      record_list.erase(record_list_.begin() + found_index); 
    }
    return true;
  }

  // Precondition: User has entered leftover record(s)
  // Postcondition: Provides external classes or functions the means to access list of leftover record from memory
  std::vector<LeftoverRecord> GetRecords() const {
    return record_list_;
  }

  // Precondition: User has created leftover record(s)
  // Postcondition: Generates and returns the leftover report
  LeftoverReport GenerateLeftoverReport() const {
    // iterate leftover_report_.GetMostCommonLeftovers(), leftover_report_.GetMostLeftoverProducingMeals(), leftover_report_.GetTotalCostOfLeftovers(), leftover_report_.GetMostCommonReasonsForLeftovers(), leftover_report_.GetCommonDisposalMechanism(), leftover_report_.GetSuggestedStrategiesToReduceLeftovers()
  } 
};

#endif
