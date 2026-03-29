#ifndef LEFTOVER_REPORT_H_
#define LEFTOVER_REPORT_H_

// Stephen Anaba
// CPSC 121L-16
// 3/22/26
// stevoclock@csu.fullerton.edu
// 3takita

#include "leftover_record.h"
#include <vector> // for vector containers
#include <unordered_map> // for frequency lookups
#include <algorithm>

class LeftoverReport {
private:
  // collection of all leftover record from memory
  // std::vector<LeftoverRecord> record_list_;
  // computed values to be used to prepare leftover report
  std::vector<std::string> most_common_leftover_names_;
  std::vector<std::string> most_costly_leftover_producing_meals_;
  double total_cost_of_leftovers_;
  std::vector<std::string> most_common_leftover_reasons_;
  std::vector<std::string> most_common_disposal_mechanisms_;
  std::vector<std::string> suggested_strategies_to_reduce_leftovers_;

public:
  // default constructor
  LeftoverReport() = default;
  
  // ============= non-default constructor ==============
  LeftoverReport(const std::vector<LeftoverRecord>& record_list) : total_cost_of_leftovers_(0.0) { 
    // --------- variable & map container declarations -----------
    std::unordered_map<std::string, int> name_count;
    int name_max = 1;
    std::string name_key = "";
    std::unordered_map<std::string, double> meal_cost;
    double meal_max = 0.0;
    std::string meal_key = "";
    std::unordered_map<std::string, int> reason_count;
    int reason_max = 1;
    std::string reason_key = "";
    std::unorderd_map<std::string, int> disposal_count;
    int disposal_max = 1;
    std::string disposal_key = ""; 

    // =========================================== 
    //  compute values into all member objects
    // ===========================================
    for(const LeftoverRecord& record : record_list) {
      LeftoverRecord record = record_list[i];
      // -------- for most_common_leftover_names_ ---------
      name_count[record.GetName()]++; // count
      // put food with most count in most_common_leftover_names
      if(name_count[record.GetName()] > name_max) { // found  new max
        if(most_common_leftover_names_.empty()) { // & container empty
          most_common_leftover_names_.push_back(record.GetName()); // push
        }
        most_common_leftover_names_.erase(); // else, erase container first
        most_common_leftover_names_.push_back(record.GetName()); // push   
        name_max = name_count[record.GetName()]; // & record new max
      } else if(name_count[record.GetName()] == name_max && name_max > 1) {
        most_common_leftover_names_.push_back(record.GetName()); // push
      }
      // ---------- for most_costly_leftover_producing_meals_ ---------
      meal_cost[record.GetMeal()] += record.GetCost(); // count
      // put meal wit most count in  most_constly_leftover_producing_meals_
      if(meal_cost[record.GetMeal()] > meal_max) {
        if(most_costly_leftover_producing_meals_.empty()) {
          most_costly_leftover_producing_meals_.push_back(record.GetMeal());
        }
        most_costly_leftover_producing_meals_.erase();
        most_costly_leftover_producing_meals_.push_back(record.GetMeal());
        meal_max = meal_cost[record.GetMeal()];
      } else if(meal_cost[record.GetMeal()] == meal_max) {
        most_costly_leftover_producing_meals_.push_back(record.GetMeal());
      }
      // --------- for total_cost_of_leftovers_ ----------
      total_cost_of_leftovers_ += record.GetCost();
      // ----------- for most_common_leftover_reasons_ ----------
      reason_count[record.GetReason()]++;
      // determin key for most common leftover reason
      if(reason_count[record.GetReason()] > reason_max) {
        if(most_common_leftover_reasons_.empty()) {
          most_common_leftover_reasons_.push_back(record.GetReason());
        }
        most_common_leftover_reasons_.erase();
        most_common_leftover_reasons_.push_back(record.GetReason());
        reason_max = reason_count[record.GetReason()];
      } else if(reason_count[record.GetReason()] == reason_max) {
        most_common_leftover_reasons_.push_back(record.GetReason());
      }
      // ----------- for most_common_disposal_mechanisms_ -----------
      disposal_count[record.GetDisposalMechanism()]++;
     // determine key for most common disposal mechanism
     if(disposal_count[record.GetDisposalMechanism()] > disposal_max) {
       if(most_common_disposal_mechanisms_.empty()) {
          most_common_disposal_mechanisms_.push_back(record.GetDisposalMechanism());
       }
       most_common_disposal_mechanisms_.erase();
       most_common_disposal_mechanisms_.push_back(record.GetDisposalMechanism());
       disposal_max = disposal_count[record.GetDisposalMechanism()]; 
     } 
    } // end of 1st for-loop 
    
    // --------- for suggested_strategies_to_reduce_leftovers_ ---------
    for(const std::string& reason: most_common_leftover_reasons_) {
      if(reason != "Expired" && std::find(suggested_strategies_to_reduce_leftovers_.begin(), suggested_strategies_to_reduce_leftovers_.end(), reason) == suggested_strategies_to_reduce_leftovers_.end()) { // 4. reason != "Expired"
        suggested_strategies_to_reduce_leftovers_.push_back("Recycle left overs"); 
      }
      if(reason == "Expired") { // 1. reason == "Expired"
        suggested_strategies_to_reduce_leftovers_.push_back("Donate before expiration");
      } else if (reason == "Tastes bad") { // 2. reasn == "Tasted bad"
        suggested_strategies_to_reduce_leftovers_.push_back("Buy less food");
      } else if(reason == "Too much leftovers") { // 3. "2much leftovers"
        suggested_strategies_to_reduce_leftovers_.push_back("Buy less food");
        suggested_strategies_to_reduce_leftovers_.push_back("Cook small servings");
      }
    } // end of 2nd for-loop
  } // end of non-default constructor
  
  // TODO: helper function for putting values with max count in containers
  /* template<typename S, typename i>
  void FillVectors(const std::unordered_map<S, i>& map, int max, std::vector<S>& container) {
    if(map[record.GetReason()] > reason_max) {
        if(most_common_leftover_reasons_.empty()) {
          most_common_leftover_reasons_.push_back(record.GetReason());
        }
        most_common_leftover_reasons_.erase();
        most_common_leftover_reasons_.push_back(record.GetReason());
        reason_max = reason_count[record.GetReason()];
      } else if(reason_count[record.GetReason()] == reason_max) {
        most_common_leftover_reasons_.push_back(record.GetReason());
      }
  } */

  // ======================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common leftover name(s)
  // ======================================================
  const std::vector<std::string>& GetMostCommonLeftoverNames() const {
    return most_common_leftover_names_;
  }
  
  // ===============================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns the most costly leftover producing meals
  // ================================================================
  const std::vector<std::string>& GetMostCostlyLeftoverProducingMeals() const {
    return most_costly_leftover_producing_meals_;
  }
  
  // ==================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns the total cost of leftovers
  // ==================================================
  double GetTotalCostOfLeftovers() const {
    return total_cost_of_leftovers_;
  }
  
  // =================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common leftover reasons
  // =================================================
  const std::vector<std::string>& GetMostCommonLeftoverReasons() const {
    return most_common_leftover_reasons_;
  }
  
  // ======================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common disposal mechanisms
  // ======================================================
  const std::vector<std::string>& GetMostCommonDisposalMechanisms() const {
    return most_common_disposal_mechanisms_;
  }
  
  // =======================================================
  // Precondition: User has entered a leftover record
  // Postcondition: Returns most common strategies to reduce leftovers
  // =======================================================
  const std::vector<std::string>& GetSuggestedStrategiesToReduceLeftovers() const {
    return suggested_strategies_to_reduce_leftovers_;
  } 
};

#endif
