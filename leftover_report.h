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
#include <unordered_set>
#include <algorithm> 
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
  double total_cost_of_leftovers_ = 0.0;
  std::vector<std::string> most_common_leftover_reasons_;
  std::vector<std::string> most_common_disposal_mechanisms_;
  std::vector<std::string> suggested_strategies_to_reduce_leftovers_;

public:
  // initialize total_cost_of_leftovers_ to avoid segmentation fault
  LeftoverReport() = default;
  
  // ============= non-default constructor ==============
  LeftoverReport(const std::vector<LeftoverRecord>& record_list) : total_cost_of_leftovers_(0.0) { 
    if(record_list.empty()) return; // guard
    FillObjects(record_list);
    Strategies();
  } // end of non-default constructor

  // =======================================
  // Postcondition: fills up member objects
  // =======================================
  void FillObjects(const std::vector<LeftoverRecord>& records) {
    // reset all member object containers & variable to avoid seg fault
    most_common_leftover_names_.clear();
    most_costly_leftover_producing_meals_.clear();
    most_common_leftover_reasons_.clear();
    most_common_disposal_mechanisms_.clear();
    suggested_strategies_to_reduce_leftovers_.clear();
    total_cost_of_leftovers_ = 0.0;
    
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
    // Postcondition: helper function for FillObjects that tracks
    // key frequency & leaves only keys with max values in container
    // =================================================== 
    template<typename T>
    void CountHelper(std::unordered_map<std::string, T>& map,\
        std::vector<std::string>& container, const std::string& key,\
        const T increment, T& max) {
      // guard against empty string
      if(key.empty()) return;
      map[key] += increment; // increment count or cost in map
      if(map[key] > max) { // if value > max
        max = map[key]; // then set max to value
        // ensure container is empty before ...
        if(!container.empty()) container.clear();
        container.push_back(key); // inserting key in it.
      } else if(map[key] == max && (std::find(container.begin(), container.end(), key) == container.end())) { // if value is same as max
        container.push_back(key); // then insert its key in container
      } // std::find() is used to avoid duplicates in container 
  } // end of CountHelper() 

  // ============ Helper enum for Strategies() ===========
    enum class Reason {
    Expired,
    TastesBad,
    TooMuchLeftovers,
    Unknown
  };

  // ====================================================================
  // Postcondition: suggests strategies to reduce left overs & puts them in suggested_strategies_to_reduce_leftovers_
  // ====================================================================
  void Strategies() {
    PrintVec(most_common_leftover_reasons_); // remove later
    if(most_common_leftover_reasons_.empty()) return; // guard
    suggested_strategies_to_reduce_leftovers_.clear(); // clear
    // 1. Map strings to a set of enums once
    std::unordered_set<Reason> active_reasons;
    for (const std::string& reason_str : most_common_leftover_reasons_) {
        if (reason_str == "Expired") {
            active_reasons.insert(Reason::Expired);
        } else if (reason_str == "Tastes bad") {
            active_reasons.insert(Reason::TastesBad);
        } else if (reason_str == "Too much left overs") {
            active_reasons.insert(Reason::TooMuchLeftovers);
        }
    }

    // 2. Extract state for cleaner logic
    bool hasExpired = active_reasons.find(Reason::Expired) != active_reasons.end();
    bool hasTastesBad = active_reasons.find(Reason::TastesBad) != active_reasons.end();
    bool hasTooMuch = active_reasons.find(Reason::TooMuchLeftovers) != active_reasons.end();

    // 3. Strategy Logic
    if (hasExpired) {
        suggested_strategies_to_reduce_leftovers_.push_back("Donate before expiration");
    }

    if (hasTastesBad || hasTooMuch) {
        suggested_strategies_to_reduce_leftovers_.push_back("Buy less food");
    }

    if (hasTooMuch) {
        suggested_strategies_to_reduce_leftovers_.push_back("Cook small servings");
    }

    if (!hasExpired) {
        suggested_strategies_to_reduce_leftovers_.push_back("Recycle left overs");
    }


    /* suggested_strategies_to_reduce_leftovers_.clear();
    bool hasExpired = false;
    bool hasTastesBad = false;
    bool hasTooMuch = false;

    for (const std::string& reason : most_common_leftover_reasons_) {
        if (reason == "Expired") hasExpired = true;
        else if (reason == "Tastes bad") hasTastesBad = true;
        else if (reason == "Too much left overs") hasTooMuch = true;
    }

    if (hasExpired) {
        suggested_strategies_to_reduce_leftovers_.push_back("Donate before expiration");
    }

    if (hasTastesBad || hasTooMuch) {
        suggested_strategies_to_reduce_leftovers_.push_back("Buy less food");
    }

    if (hasTooMuch) {
        suggested_strategies_to_reduce_leftovers_.push_back("Cook small servings");
    }

    if (!hasExpired) {
        suggested_strategies_to_reduce_leftovers_.push_back("Recycle left overs");
    } */ 
  } // end of Strategies()
  
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
