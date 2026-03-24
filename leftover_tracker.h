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
    // TESTING
    for (const LeftoverRecord& existing_record : record_list_) {
        if (existing_record == new_record) {
            std::cout << "Duplicate found:\n";
            std::cout << "Existing date: " << existing_record.GetDate() << "\n";
            std::cout << "New date: " << new_record.GetDate() << "\n";
            return false;
        }
    }

    std::cout << "Adding record with date: " << new_record.GetDate() << "\n";
    record_list_.push_back(new_record);
    return true;
    
    
    
    // if new_record already exists, don't add. Return false 
    /* for(const LeftoverRecord& existing_record : record_list_) {
      if(existing_record == new_record) {
        return false;
      }
    }
    // otherwise, add new_record
    record_list_.push_back(new_record);
    return true; */
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
    LeftoverReport leftover_report_{record_list_}; 
    return leftover_report_;

    /*if(!record_list_.empty()) {
      // display most common leftover names 
      std::cout << "Most common leftovers:\n";
      if(leftover_report_.GetMostCommonLeftoversNames().size() > 1) {
        for(const auto& name : \
            leftover_report_.GetMostCommonLeftoversNames()) {
          std::cout << name << "\n";
        }
      } else {
        std::cout << name;
      } 

      // display most costly leftover meal(s)
      std::cout << "Most costly leftover meal(s):\n";
      if(leftover_report_.GetMostCostlyLeftoverProducingMeals().size() > 1) {
        for(const auto& meal : leftover_report_.GetMostCostlyLeftoverProducingMeals()) {
          std::cout << meal << "\n";
        }
      } else {
        std::cout << meal;
      } 
    
      // display total cost of leftovers
      std::cout << "Total leftover food cost:\n";
      std::cout << leftover_report_.GetTotalCostOfLeftovers();
    
      // display most common leftover reasons
      std::cout << "Most common leftover reason:\n";
      if(leftover_report_.GetMostCommonLeftoverReasons().size() > 1) {
        for(const auto& reason : \
            leftover_report_.GetMostCommonLeftoverReasons()) {
          std::cout << reason << "\n";
        }
      } else {
        std::cout << reason;
      } 
    
      // display most common disposal mechanisms
      std::cout << "Most common disposal mechanism:\n";
      if(leftover_report_.GetMostCommonDisposalMechanisms().size() > 1) {
        for(const auto& disposal : \
            leftover_report_.GetMostCommonDisposalMechanisms()) {
          std::cout << disposal << "\n";
        }
      } else {
        std::cout << disposal;
      }  
    
      // display suggested strategies for reducing leftover
      std::cout << "Suggested strategies to reduce leftover:\n";
      if(leftover_report_.GetSuggestedStrategiesToReduceLeftovers().size() > 1) {
        for(const auto& strategy : \
            leftover_report_.GetSuggestedStrategiesToReduceLeftovers()) {
          std::cout << strategy << "\n";
        }
      } else {
        std::cout << strategy;
      } 
    }*/ // end of if-statement 
  } 
};

#endif
