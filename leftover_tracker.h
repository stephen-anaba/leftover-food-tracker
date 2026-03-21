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
  std::unordered_set<LeftoverRecord> record_set_; // for efficient lookup
public:
  // default constructor
  LeftoverTracker() = default;
  
  // Precondition: User has created a leftover record
  // Postcondition: Adds new record_list_ & return true if successful, else returns false. Avoids duplicate records 
  bool AddRecord(const LeftoverRecord& new_record) { // DONE
    int set_size = record_set_.size(); // get initial record_set size
    record_set_.insert(new_record); // try adding new_record to record_set_
    if(record_set_.size() > set_size) { // if successful...
      record_list_.push_back(new_record); // then add it to record_list_
      return true; // and return true
    }// ContainsRecord(leftover_record) == -1
    return false; // otherwise, return false
  } // end of AddRecord() 
  
  // Precondition: User has created leftover record(s)
  // Postcondition: Delete `record` from record_list_ & return true, else returns false
  bool DeleteRecord(const LeftoverRecord& record) { // DONE
    // if record is not in record_set, just return false
    if(!record_set_.contains(record)) {
      return false;
    } 
    // get record index, use it to erase record & return true
    int record_index = std::find(record_list_.begin(), record_list_.end(), record); 
    record_list_.erase(record_list_.begin() + record_index);  
    return true;
  }

  // Precondition: User has entered leftover record(s)
  // Postcondition: Provides external classes or functions the means to access list of leftover record from memory
  std::vector<LeftoverRecord> GetRecords() const { // DONE
    return record_list_;
  }

  // Precondition: User has created leftover record(s)
  // Postcondition: Generates and returns the leftover report
  LeftoverReport GenerateLeftoverReport() const { 
    // TODO: display most common leftover names
    std::vector<std::string> names = leftover_report_.GetMostCommonLeftoversNames();
    
    // TODO: display most costly leftover meal(s)
    std::vector<std::string> costly_meal = leftover_report_.GetMostCostlyLeftoverProducingMeals();
    
    // TODO: display total cost of leftovers
    std::vector<std::string> total_cost =eftover_report_.GetTotalCostOfLeftovers();
    
    // TODO: display most common leftover reasons
    std::vector<std::string> reasons = eftover_report_.GetMostCommonLeftoverReasons();
    
    // TODO: display most common disposal mechanisms
    leftover_report_.GetMostCommonDisposalMechanisms();
    
    // TODO: display suggested strategies for reducing leftover
    leftover_report_.GetSuggestedStrategiesToReduceLeftovers();
  } 
};

#endif
