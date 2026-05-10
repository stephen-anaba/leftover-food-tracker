#ifndef LEFTOVER_REPORT_H_
#define LEFTOVER_REPORT_H_

// Stephen Anaba
// CPSC 121L-16
// 3/22/26
// stevoclock@csu.fullerton.edu
// 3takita

#include <algorithm>
#include <iostream>       // remove
#include <unordered_map>  // for frequency lookups
#include <unordered_set>
#include <vector>  // for vector containers

#include "leftover_record.h"

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
  LeftoverReport();

  // ============= non-default constructor ==============
  LeftoverReport(const std::vector<LeftoverRecord>& record_list);

  // =======================================
  // Postcondition: fills up member objects
  // =======================================
  void FillObjects(const std::vector<LeftoverRecord>& records);

  // ===================================================
  // Postcondition: helper function for FillObjects that tracks
  // key frequency & leaves only keys with max values in container
  // ===================================================
  template <typename T>
  void CountHelper(std::unordered_map<std::string, T>& map,
                   std::vector<std::string>& container, const std::string& key,
                   const T increment, T& max) {
    // guard against empty string
    if (key.empty()) return;
    map[key] += increment;  // increment count or cost in map
    if (map[key] > max) {   // if value > max
      max = map[key];       // then set max to value
      // ensure container is empty before ...
      if (!container.empty()) container.clear();
      container.push_back(key);  // inserting key in it.
    } else if (map[key] == max &&
               (std::find(container.begin(), container.end(), key) ==
                container.end())) {  // if value is same as max
      container.push_back(key);      // then insert its key in container
    }  // std::find() is used to avoid duplicates in container
  }  // end of CountHelper()

  // ============ Helper enum for Strategies() ===========
  enum class Reason { Expired, TastesBad, TooMuchLeftovers, Unknown };

  // ====================================================================
  // Postcondition: suggests strategies to reduce left overs & puts them in
  // suggested_strategies_to_reduce_leftovers_
  // ====================================================================
  void Strategies();

  // =========================================================
  //  Postcondition: prints std::unorderd_map<std::string, T>
  // =========================================================
  template <typename T>
  void PrintMap(const std::unordered_map<std::string, T>& map) const {
    std::cout << "Printing map:\n";
    for (const auto& [key, val] : map) {
      std::cout << "\t" << key << ": " << val << "\n";
    }
    std::cout << "\n";
  }

  // ================================================
  //  Postcondition: prints std::vector<std::string>
  // ================================================
  // print most_costly_leftover_producing_meal - vector
  void PrintVec(const std::vector<std::string>& vec) const;

  // ======================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common leftover name(s)
  // ======================================================
  const std::vector<std::string>& GetMostCommonLeftoverNames() const;

  // ===============================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns the most costly leftover producing meals
  // ================================================================
  const std::vector<std::string>& GetMostCostlyLeftoverProducingMeals() const;

  // ==================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns the total cost of leftovers
  // ==================================================
  double GetTotalCostOfLeftovers() const;

  // =================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common leftover reasons
  // =================================================
  const std::vector<std::string>& GetMostCommonLeftoverReasons() const;

  // ======================================================
  // Precondition: User has created a leftover record
  // Postcondition: Returns most common disposal mechanisms
  // ======================================================
  const std::vector<std::string>& GetMostCommonDisposalMechanisms() const;

  // =======================================================
  // Precondition: User has entered a leftover record
  // Postcondition: Returns most common strategies to reduce leftovers
  // =======================================================
  const std::vector<std::string>& GetSuggestedStrategiesToReduceLeftovers()
      const;
};

#endif
