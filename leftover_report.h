#ifndef LEFTOVER_REPORT_H_
#define LEFTOVER_REPORT_H_

// Please fill in below.
// <Your name>
// <Your section number> (e.g. CPSC 121L-01)
// <Date>
// <Your csu.fullerton.edu email>
// <Your GitHub username>

#include <vector> // for vector containers
#include <unordered_map> // for frequency lookups

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
  LeftoverReport() : record_list_{}, most_common_leftover_names_{}, most_costly_leftover_producing_meals_{}, total_cost_of_leftovers_{}, most_common_leftover_reasons_{}, most_common_disposal_mechanisms_{}, suggested_strategies_to_reduce_leftovers_{} {
    // variable & std::unodered_map container declarations
    double max_meal_cost = 0.0; 
    int top_meal = 0;
    std::unordered_map<std::string, int> counter_map;
    
    // extract from record_list_ components for object variables
    for(const LeftoverRecord& record : record_list_) {
      // 1. compute the frequency of each leftover name. // DONE
      Counter(counter_map, record.GetName());
      if(counter_map[record.GetName()] > top_meal) {
        top_meal = counter_map[record.GetName()];
      }
      // 2. compute the cumulative cost of each meal. // DONE
      counter_map[record.GetMeal()] += record.GetCost(); 
      if(counter_map[record.GetMeal()] > max_meal_cost) {
        max_meal_cost = counter_map[record.GetMeal()];
      } 
      // 3. add up cost to total_cost_of_leftovers. // DONE
      total_cost_of_leftovers_ += record.GetCost(); 
      // 4. TODO: compute frequency of each reason in record_list_
      Counter(counter_map, record.GetReason());
      // 5. TODO: compute frequency of each diposal mechanism
      Counter(counter_map, record.GetDisposalMechanism());
    } // end of for-loop
  
    // Use inverse lookup to put values in their containers 
    for(const auto& [key, value] : counter_map) {
      // put costly meal(s) in most_costly_leftover_producing_meals
      if(value == max_meal_cost) {
        most_costly_leftover_producing_meals.push_back(key);
      }
      // put meal(s) with the highest frequency in most_common_leftover_names_
      if(value == top_meal) {
        most_common_leftover_names_.push_back(key);
      }
      // TODO: do same for 4. and 5. above
    }
    
    
    //   use the conditions to determine leftover reduction
    //   strategies. Put them in the right container.
  
  } // end of default constructor 

  // Precondition: arguments passed to it come from a loop
  // Postcondition: counts how many times a string is passed to it  
  void Counter(std::unordered_map<std::string, int>& value_counter, const std::string& value) { // Counter(map, value);
    value_counter[value]++; 
  }
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common leftover name(s)
  const std::vector<std::string>& GetMostCommonLeftoverNames() const {
    return most_common_leftover_names_;
  }
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns the most costly leftover producing meals
  const std::vector<std::string>& GetMostCostlyLeftoverProducingMeals() const {
    return most_costly_leftover_producing_meals_;
  }
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns the total cost of leftovers
  double GetTotalCostOfLeftovers() const {
    return total_cost_of_leftovers_;
  }
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common leftover reasons
  const std::vector<std::string>& GetMostCommonLeftoverReasons() const {
    return most_common_leftover_reasons_;
  }
  
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common disposal mechanisms
  const std::vector<std::string>& GetMostCommonDisposalMechanisms() const {
    return most_common_disposal_mechanisms_;
  }
  
  // Precondition: User has entered a leftover record
  // Postcondition: Returns most common strategies to reduce leftovers
  const std::vector<std::string>& GetSuggestedStrategiesToReduceLefotvers() const {
    return most_common_strategies_to_reduce_leftovers_;
  } 
};

#endif
