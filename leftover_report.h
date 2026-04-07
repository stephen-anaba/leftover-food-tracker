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
#include <type_traits> // to determine int or double data type
#include <iostream> // remove

// ================== TODO ===================
// 1. Write/use helper functions/generic helpers using following pattern:
//    if(map[key] > max) {
//      container.push_back(...)
//    }
//    container.clear()
//    container.push_back(...)
//    max = ... // update max
// 2. Use consistent patterns: clear(), empty(), max, etc
// 3. Implement separation of concerns
// 4. Don't update map, vector & max inside the loop all at once to 
//    avoid tight coupling & difficult debugging
// 5. Separate computation from construction. Use a void function to do the
//    computation & call it in the constructor. Easy to test/debug/reuse
// 6. Move PrintMap & PrintVec to a debug utility or test layer
// ===========================================

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
    FillObjects(record_list);
    Strategies();
    // --------- variable & map container declarations -----------
    /* std::unordered_map<std::string, int> name_count_map;
    int name_max = 0;
    std::string name_key = "";
    std::unordered_map<std::string, double> meal_cost_map;
    double meal_max = 0;
    std::string meal_key = "";
    std::unordered_map<std::string, int> reason_count_map;
    int reason_max = 1;
    std::string reason_key = "";
    std::unordered_map<std::string, int> disposal_count_map;
    int disposal_max = 0;
    std::string disposal_key = ""; 

    // =========================================== 
    //  compute values into all member objects
    // ===========================================
    for(const LeftoverRecord& record : record_list) { 
      // -------- for most_common_leftover_names_ ---------
      name_count_map[record.GetName()]++; // count
      // put food with most count in most_common_leftover_names
      if(name_count_map[record.GetName()] > name_max) { // found  new max
        if(most_common_leftover_names_.empty()) { // & container empty
          most_common_leftover_names_.push_back(record.GetName()); // push
        }
        most_common_leftover_names_.clear(); // else, clear container first
        most_common_leftover_names_.push_back(record.GetName()); // push   
        name_max = name_count_map[record.GetName()]; // & record new max
      } else if(name_count_map[record.GetName()] == name_max && name_max > 1) {
        most_common_leftover_names_.push_back(record.GetName()); // push
      } 
      // TODO: FIX---------- for most_costly_leftover_producing_meals_ ---------
      // ISSUE: record.GetMeal() not entered  in meal_cost_map.
      meal_cost_map[record.GetMeal()] += record.GetCost(); // sum cost
      // std::cout << record.GetCost() << " added for " << record.GetMeal() << "\n"; // remove - << 136 >>
      if(meal_cost_map[record.GetMeal()] > meal_max) { // found  new max
        if(most_costly_leftover_producing_meals_.empty()) { // & container empty
          most_costly_leftover_producing_meals_.push_back(record.GetMeal());
        }
        most_costly_leftover_producing_meals_.clear();
        most_costly_leftover_producing_meals_.push_back(record.GetMeal());   
        meal_max = meal_cost_map[record.GetName()]; // & record new max
      } else if(meal_cost_map[record.GetMeal()] == meal_max) {
        most_costly_leftover_producing_meals_.push_back(record.GetMeal());
      } 
      
      // --------- for total_cost_of_leftovers_ ----------
      total_cost_of_leftovers_ += record.GetCost(); 
      // ----------- for most_common_leftover_reasons_ ----------
      reason_count_map[record.GetReason()]++;
      // determin key for most common leftover reason
      if(reason_count_map[record.GetReason()] > reason_max) { // [174]
        if(most_common_leftover_reasons_.empty()) {
          most_common_leftover_reasons_.push_back(record.GetReason());
        }
        most_common_leftover_reasons_.clear();
        most_common_leftover_reasons_.push_back(record.GetReason());
        reason_max = reason_count_map[record.GetReason()];
      } else if(reason_count_map[record.GetReason()] == reason_max) {
        most_common_leftover_reasons_.push_back(record.GetReason());
      }
      // ----------- for most_common_disposal_mechanisms_ -----------
      disposal_count_map[record.GetDisposalMechanism()]++; // count
     // if count for this disposal mechanism > disposal_max
     if(disposal_count_map[record.GetDisposalMechanism()] > disposal_max) {
       // make sure most_common_disposal_mechanisms_ is empty && put ...
       if(most_common_disposal_mechanisms_.empty()) {
          most_common_disposal_mechanisms_.push_back(record.GetDisposalMechanism());
       } // this disposal mechanism in most_common_disposal_mechanism_
       most_common_disposal_mechanisms_.clear();
       most_common_disposal_mechanisms_.push_back(record.GetDisposalMechanism());
       disposal_max = disposal_count_map[record.GetDisposalMechanism()]; 
     } else if(disposal_count_map[record.GetDisposalMechanism()] == disposal_max) {
        most_common_disposal_mechanisms_.push_back(record.GetDisposalMechanism());
     } 
    }*/ // end of 1st for-loop 

    /*std::cout << "most_costly_leftover_producing_meal.size() = " << most_costly_leftover_producing_meals_.size() << "\n";
    std::cout << "meal_cost_map.size() = " << meal_cost_map.size() << "\n"; // remove
    PrintMap(meal_cost_map); // print meal_cost_map - remove
    PrintVec(most_costly_leftover_producing_meals_);*/ // print most_costly_leftover_producing_meal - remove
   
    // --------- for suggested_strategies_to_reduce_leftovers_ ---------
    /*for(const std::string& reason: most_common_leftover_reasons_) {
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
    }*/ // end of 2nd for-loop
  } // end of non-default constructor


  // Postcondition: fills up member objects
  void FillObjects(const std::vector<LeftoverRecord>& records) {
    // variables and maps
    std::unordered_map<std::string, int> name_count_map;
    int name_max = 0;
    std::unordered_map<std::string, int> reason_count_map;
    int reason_max = 0;
    std::unordered_map<std::string, int> disposal_count_map;
    int disposal_max = 0;
    std::unordered_map<std::string, double> meal_cost_map;
    double meal_max = 0; 
    
    for(const auto& record : records) { 
      // Compute values into member object containers:
      CountHelper(name_count_map, most_common_leftover_names_, record.GetName(), 1, name_max); // 1
      
      total_cost_of_leftovers_ += record.GetCost(); // 2. done

      CountHelper(reason_count_map, most_common_leftover_reasons_, record.GetReason(), 1, reason_max); // 3.

      CountHelper(disposal_count_map, most_common_disposal_mechanisms_, record.GetDisposalMechanism(), 1, disposal_max); // 4. 
    
      CountHelper(meal_cost_map, most_costly_leftover_producing_meals_, record.GetMeal(), record.GetCost(), meal_max); // 5.
      // Strategies(); // 6. Compute strategies
    } // end of for-loop 
  } // end of FillObjects

  // Postcondition: helper function for FillObjects
  template<typename T>
  void CountHelper(std::unordered_map<std::string, T>& map, std::vector<std::string>& container, const std::string& key, const T increment, T& max) {
    if(std::is_same_v<T, double>) { // double
      std::cout << "(" << increment << " & " << max << " are doubles):\n"; // remove
      if(map[key] > max) {
        std::cout << "\t(" << map[key] << " > " << max << "):\n"; // remove
        map[key] += increment;
        std::cout << "\t\tmap[" << key << "] += " << increment << "\n"; // remove
        std::cout << "\t\tmax = " << map[key] << "\n"; // remove
        max = map[key];
        if(!container.empty()) container.clear();
        container.push_back(key);
        std::cout << "\t\tAfter push, container.size = " << container.size() << "\n"; //remove
      } else if(map[key] == max) {
        std::cout << "\t(" << map[key] << " == " << max << ")\n"; // remove
        container.push_back(key);
        std::cout << "\t\tAfter push, container.size = " << container.size() << "\n"; // remove 
      }
    } else { // int
      std::cout << "(" <<increment<< " & " <<max<< " are integers\n"; //remove
      if(map[key] > max) {
        std::cout << "\t(" << map[key] << " > "<< max << "):\n"; // remove
        std::cout << "\t\t" << map[key] << " ++\n"; // remove
        std::cout << "\t\t" << map[key] << " ++\n"; // remove
        map[key]++;
        std::cout << "\t\tmax = " << map[key] << "\n"; // remove
        max = map[key];
        if(!container.empty()) container.clear();
        container.push_back(key);
        std::cout << "\t\tAfter push, container.size = " << container.size() << "\n\n"; // remove
      } else if(map[key] == max) {
        std::cout << "\t(" << map[key]<< " = " << max << ")\n"; // remove
        container.push_back(key);
        std::cout << "\t\tAfter push, container.size = " << container.size() << "\n\n"; // remove
      }
    }
    
    // execute block only when max is ...
    /*if(std::is_same<T, double>::value && map[key] > max) { // ... double
      map[key] += increment;
      max = map[key];
      if(!container.empty()) container.clear();
      container.push_back(key); 
    } else if(floor(max) != ceil(max) && map[key] > max) { // ... int
      map[key]++;
      max = map[key];
      if(!container.empty()) container.clear();
      container.push_back(key); 
    } else if(floor(max) != ceil(max) && map[key] == max) {
      //
    } */ 

  } // end of CountHelper() 

  // Postcondition: determines suggested_strategies_to_reduce_leftovers_
  void Strategies() {
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
    }
  }
  
  // -------------------------------------------------------------
  //  PRINT MAP AND VECTOR FOR TROUBLESHOOTING : << 84 >>
      // printMealCostMap(); // print meal_cost_map - map
      void PrintMap(const std::unordered_map<std::string, double>& map) const { 
        std::cout << "Printing meal_cost_map:\n";
        for(const auto& [key, val] : map) {  
          std::cout << "\t" << key << ": " << val << "\n";
        }
        std::cout << "\n";
      }

      // print most_costly_leftover_producing_meal - vector
      void PrintVec(const std::vector<std::string>& vec) const {
        std::cout << "Printing most_costly_leftover_producing_meal\n";  
        for(const auto& v : vec) {
          std::cout << "\t" << v << ", ";
        }
        std::cout << "\n";
      }
      
  // -------------------------------------------------------------

  // TODO: helper function for putting values with max count in containers
  /* template<typename S, typename i>
  void FillVectors(const std::unordered_map<S, i>& map, int max, std::vector<S>& container) {
    if(map[record.GetReason()] > reason_max) {
        if(most_common_leftover_reasons_.empty()) {
          most_common_leftover_reasons_.push_back(record.GetReason());
        }
        most_common_leftover_reasons_.clear();
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
