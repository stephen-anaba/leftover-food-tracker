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
  std::vector<std::string> suggested_strategies_to_reduce_leftovers_;
public:
  // default constructor
  LeftoverReport() = default;
  // non-default constructor
  LeftoverReport(const std::vector<LeftoverRecord>& record_list) : record_list_{}, most_common_leftover_names_{}, most_costly_leftover_producing_meals_{}, total_cost_of_leftovers_{}, most_common_leftover_reasons_{}, most_common_disposal_mechanisms_{}, suggested_strategies_to_reduce_leftovers_{} {
    
    // variable & std::unodered_map container declarations
    double cost_max = 0.0;
    std::string most_costly_meal = ""; // most costly meal holder
    int name_max = 1;
    std::string name = ""; // name holder
    //std::string prev_name = record_list_[0].GetName(); // previous name
    int reason_max = 1;
    std::string reason = ""; // reason holder
    //std::string prev_reason = record_list_[0].GetReason(); // prev reason
    int disposal_max = 1;
    std::string disposal = ""; // disposal mech holder
    //std::string prev_disposal = record_list_[0].GetDisposalMechanism(); // prev disposal
    std::unordered_map<std::string, int> counter_map; // one map option
    std::unordered_map<std::string, double> meal_cost_map; // continue..

    // From record_list_, compute values for all object variables
    for(int i = 0; i < record_list_.size(); i++) {
      LeftoverRecord record = record_list_[i];
      // for(const LeftoverRecord& record : record_list_) {
      
      // 1. count occurence(s) of leftover name
      // store max count & corresponding leftover name. // DONE
      // get name(s) with max count. Put it/them in container
      counter_map[record.GetName()]++;// Counter(counter_map, record.GetName()); // name-count
      // if new max for name count is found 
      if((i > 0) && counter_map[record.GetName()] > name_max) {
       // ensure container is empty 
        if(!most_common_leftover_names_.empty()) {
          most_common_leftover_names_.erase();
        }
        name_max = counter_map[record.GetName()]; // note the max count
        name = record.GetName(); // note corresponding name
        most_common_leftover_names_.push_back(name); // contain the name
      }
      // if another leftover name shares max count, contain it too
      if(name_max > 1 && (name_max == counter_map[record.GetName()])) {
        most_common_leftover_names_.push_back(record.GetName());
      } 

      // 2. add up cost of meals & contain the corresponding meals. 
      meal_cost_map[record.GetMeal()] += record.GetCost(); // meal-cost 
      if(meal_cost_map[record.GetMeal()] > cost_max) { // DONE
        // ensure container is empty
        if(!most_costly_leftover_producing_meals_.empty()) {
          mmost_costly_leftover_producing_meals_.erase();
        }
        cost_max = meal_cost_map[record.GetMeal()]; // note the max
        most_costly_meal = record.GetMeal(); // note corresponding meal
        most_costly_leftover_producing_meals_.push_back(most_costly_meal); 
      }
      // if another meal shares max cost, contain it too
      if(cost_max > 0 && cost_max == meal_cost_map[record.GetName()]) {
        most_costly_leftover_producing_meals_.push_back(record.GetMeal());
      }

      // 3. add up all the cost to total_cost_of_leftovers. // DONE 
      total_cost_of_leftovers_ += record.GetCost(); 
      
      // 4. count frequency for reason & get most common leftover reason 
      // Counter(counter_map, record.GetReason());
      counter_map[record.GetReason]++; // count each reason
      if(counter_map[record.GetReason()] > reason_max) { // reason-count
        // ensrure container is empty
        if(!most_common_leftover_reasons_.empty()) { // DONE
          most_common_leftover_reasons_.erase();
        }
        reason_max = counter_map[record.GetReason()]; // note the max
        reason = record.GetReason(); // note corresponding reason
        most_common_leftover_reasons_.push_back(reason); // contain reason
      }
      // if another reason shares reason_max, contain it too
      if(reason_max > 1 && reason_max == counter_map[record.GetReason()]) {
        most_common_leftover_reasons_.push_back(record.GetReason());
      }
      
      // 5. get max disp mech frequency & contain its diposal mechanism //
      // Counter(counter_map, record.GetDisposalMechanism());
      counter_map[record.GetDisposalMechanism()]++; // count disp mech
      if(counter_map[record.GetDisposalMechanism()] > disposal_max) {
        // ensure container is empty
        if(!most_common_disposal_mechanisms_.empty()) { // DONE
          most_common_disposal_mechanisms_.erase();
        }
        disposal_max = counter_map[record.GetDisposalMechanism()];
        disposal = record.GetDisposalMechanism(); // note disposal mech
        most_common_disposal_mechanisms_.push_back(disposal); // contain it
      }
      // if another disposal shares disposal_max, contain it too
      if(disposal_max > 1 && disposal_max == counter_map[record.GetDisposalMechanism()]) {
        most_common_disposal_mechanisms_.push_back(record.GetDisposalMechanism());
      } 
    } // end of 1st for-loop
  
    // • Use inverse lookup to put values in their containers 
    /* for(const auto& [key, value] : counter_map) {
      // put costly meal(s) in most_costly_leftover_producing_meals
      if(value == cost_max) { // 2.
        most_costly_leftover_producing_meals.push_back(key);
      }
      // put highest frequency meal(s) in most_common_leftover_names_
      if(value == name_max) { // 1.
        most_common_leftover_names_.push_back(key);
      }
      // put highest freq reason in most_common_leftover_reasons_
      if(value == reason_max) { // 4.
        most_common_leftover_reasons_.push_back(key);
      } 
      // put highest freq disp mech in most_common_disposal_mechanisms_
      if(value == disposal_max) { // 5.
        most_common_disposal_mechanisms_.push_back(key);
      }
    } */ // end of 2nd for-loop
    
    // • Use the conditions to determine leftover reduction
    // strategies. Put them in the right container.
    for(const std::string& reason: most_common_disposal_mechanisms_) {
      if(reason != "Expired" && std::find(suggested_strategies_to_reduce_leftovers_.begin(), suggested_strategies_to_reduce_leftovers_.end(), reason) == suggested_strategies_to_reduce_leftovers_.end() { // 4. reason != "Expired"
        suggested_strategies_to_reduce_leftovers_.push_back("Recycle lefto overs"); 
      }
      if(reason == "Expired") { // 1. reason == "Expired"
        suggested_strategies_to_reduce_leftovers_.push_back("Donate before expiration");
      } else if (reason == "Tastes bad") { // 2. reasn == "Tasted bad"
        suggested_strategies_to_reduce_leftovers_.push_back("Buy less food");
      } else if(reason == "Too much left overs") { // 3. "2much leftovers"
        suggested_strategies_to_reduce_leftovers_.push_back("Buy less food");;
        suggested_strategies_to_reduce_leftovers_.push_back("Cook small servings");
      }
    } // end of for-loop
  } // end of default constructor 

  // Precondition: arguments passed to it come from a loop
  // Postcondition: counts how many times a string is passed to it  
  template <typename T, typename S>>
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
