#ifndef LEFTOVER_REPORT_H_
#define LEFTOVER_REPORT_H_

// Please fill in below.
// <Your name>
// <Your section number> (e.g. CPSC 121L-01)
// <Date>
// <Your csu.fullerton.edu email>
// <Your GitHub username>

#include <vector> // for vector containers

class LeftoverReport {
private:
  // collection of all leftover record from memory
  std::vector<LeftoverRecord> record_list_;
  // computed values to be used to prepare leftover report
  std::vector<std::string> most_common_leftover_names_;
  std::vector<std::string> most_costly_leftover_producing_meals_;
  double total_cost_of_leftovers_;
  std::vector<std::string> most_common_leftover_reasons_;
  std::vector<std::string> most_common_disposal_mechanisms_;
  std::vector<std::string> suggested_stragegies_to_reduce_leftovers_;
public:
  // default constructor. This class gets records by calling the GetRecords() func of LeftoverTracker class
  LeftoverReport() = default;
  // non-default constructor
  /* LeftoverReport(const std::vector<LeftoverRecord>& record_list) : record_list_(record_list) {
    // this is where record_list_ will be iterated as i, & from each i the private member variables of the LeftoverRecord object it represents will be extracted using getters, evaluated for frequency using dictionay or summed up for total as the case may be, and computed results put in corresponding containers/value expressed above as private member variables 
  } */
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common leftover name(s)
  std::vector<std::string> GetMostCommonLeftoverNames() const {
    return most_common_leftover_names_;
  }
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns the most costly leftover producing meals
  std::vector<std::string> GetMostCostlyLeftoverProducingMeals() const {
    return most_costly_leftover_producing_meals_;
  }
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns the total cost of leftovers
  double GetTotalCostOfLeftovers() const {
    return total_cost_of_leftovers_;
  }
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common leftover reasons
  std::vector<std::string> GetMostCommonLeftoverReasons() const {
    return most_common_leftover_reasons_;
  }
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common disposal mechanisms
  std::vector<std::string> GetMostCommonDisposalMechanisms() const {
    return most_common_disposal_mechanisms_;
  }
  
  // Precondition: User has entered a leftover record
  // Postcondition: Returns most common strategies to reduce leftovers
  std::vector<std::string> GetSuggestedStrategiesToReduceLefotvers() const {
    return most_common_strategies_to_reduce_leftovers_;
  } 
};

#endif
