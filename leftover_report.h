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
  // private member objects 
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
  } // end of non-default constructor

  // =======================================
  // Postcondition: fills up member objects
  // =======================================
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
      CountHelper(name_count_map, most_common_leftover_names_, \
          record.GetName(), 1, name_max); // 1
      
      total_cost_of_leftovers_ += record.GetCost(); // 2. done

      CountHelper(reason_count_map, most_common_leftover_reasons_, \
          record.GetReason(), 1, reason_max); // 3.

      CountHelper(disposal_count_map, most_common_disposal_mechanisms_, \
          record.GetDisposalMechanism(), 1, disposal_max); // 4. 
      
      // input validation to prevent logical errors
      if(record.GetMeal().empty()) {
        std::cout << "ERROR: meal is empty\n";
      } 
      CountHelper(meal_cost_map, most_costly_leftover_producing_meals_, \
          record.GetMeal(), record.GetCost(), meal_max); // 5. 
    } // end of for-loop 
  } // end of FillObjects

    // ===================================================
    // Postcondition: helper function for FillObjects
    // ===================================================
    // TODO: 1. Avoid tight coupling in CountHelper() by coding UpdateMap() &
    // TrackMax() so CountHelper only mutates result container
    // 2. Just pass increment `map[key] += increment` instead of doing 
    // `if(std::is_same_v<T, double>)` to avoid unnecessay type based branching
    // 3. Decouple constructor cos its doing construction, computation,
    // & business logic. Code Compute(records) for `report.Compute(records)`
    template<typename T>
    void CountHelper(std::unordered_map<std::string, T>& map,\
        std::vector<std::string>& container, const std::string& key,\
        const T increment, T& max) {
    // ------------------ when max is double ----------------
    if(std::is_same_v<T, double>) { // if T is a double type 
      map[key] += increment; // add cost to map[key]
      if(map[key] > max) {  // & map[key] > max 
        max = map[key];    // then max becomes map[key]
        if(!container.empty()) { // if container is empty
          container.clear();    // then clear it
        }
        container.push_back(key); // insert key
      } else if(map[key] == max && (std::find(container.begin(), container.end(), key) == container.end())) { 
        container.push_back(key); // just put key in container
      }
    } else { // ------------------ when max is integer ---------------- 
      map[key]++; // bfast:8, lunch:0, dinner:0 
      if(map[key] > max) { //
        max = map[key];   // 
        if(!container.empty()) container.clear(); //
        container.push_back(key); //
      } else if(map[key] == max && (std::find(container.begin(), container.end(), key) == container.end())) { //
        container.push_back(key); //
      }
    } // end of if-else statements
  } // end of CountHelper() 

  // ====================================================================
  // Postcondition: determines suggested_strategies_to_reduce_leftovers_
  // ====================================================================
  void Strategies() {
    for(const std::string& reason: most_common_leftover_reasons_) {
      if(reason != "Expired" &&
          std::find(suggested_strategies_to_reduce_leftovers_.begin(),
            suggested_strategies_to_reduce_leftovers_.end(), 
            reason) == suggested_strategies_to_reduce_leftovers_.end()) { 
        suggested_strategies_to_reduce_leftovers_.\
          push_back("Recycle left overs"); 
      }
      if(reason == "Expired") { // 1. reason == "Expired"
        suggested_strategies_to_reduce_leftovers_.\
          push_back("Donate before expiration");
      } else if (reason == "Tastes bad") { // 2. reasn == "Tasted bad"
        suggested_strategies_to_reduce_leftovers_.push_back("Buy less food");
      } else if(reason == "Too much leftovers") { // 3. "2much leftovers"
        suggested_strategies_to_reduce_leftovers_.push_back("Buy less food");
        suggested_strategies_to_reduce_leftovers_.\
          push_back("Cook small servings");
      }
    }
  }
  
      // =========================================================
      //  Postcondition: prints std::unorderd_map<std::string, T>
      // =========================================================
      template<typename T>
      void PrintMap(const std::unordered_map<std::string, T>& map) const { 
        std::cout << "Printing map:\n";
        for(const auto& [key, val] : map) {  
          std::cout << "\t" << key << ": " << val << "\n";
        }
        std::cout << "\n";
      }

      // ================================================
      //  Postcondition: prints std::vector<std::string>
      // ================================================
      // print most_costly_leftover_producing_meal - vector
      void PrintVec(const std::vector<std::string>& vec) const {
        std::cout << "Printing vec-container:\n";  
        for(const auto& v : vec) {
          std::cout << "\t" << v << ", ";
        }
        std::cout << "\n";
      }

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
