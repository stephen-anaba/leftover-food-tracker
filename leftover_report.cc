// Stephen Anaba
// CPSC 121L-16
// 5/10/26
// stevoclock@csu.fullerton.edu
// 3takita

#include "leftover_report.h"

// initialize total_cost_of_leftovers_ to avoid segmentation fault
LeftoverReport::LeftoverReport() = default;

// ============= non-default constructor ==============
LeftoverReport::LeftoverReport(const std::vector<LeftoverRecord>& record_list)
    : total_cost_of_leftovers_(0.0) {
  FillObjects(record_list);  // fill member objects
  Strategies();              // generate strategies & fill strategy container
}  // end of non-default constructor

// =======================================
// Postcondition: fills up member objects
// =======================================
void LeftoverReport::FillObjects(const std::vector<LeftoverRecord>& records) {
  // reset  member object containers & variable to avoid seg fault
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

  for (const auto& record : records) {
    // Compute values into member object containers:
    CountHelper(name_count_map, most_common_leftover_names_, record.GetName(),
                1, name_max);

    total_cost_of_leftovers_ += record.GetCost();

    CountHelper(reason_count_map, most_common_leftover_reasons_,
                record.GetReason(), 1, reason_max);

    CountHelper(disposal_count_map, most_common_disposal_mechanisms_,
                record.GetDisposalMechanism(), 1, disposal_max);

    // input validation to prevent logical errors
    if (record.GetMeal().empty()) {
      std::cout << "ERROR: meal is empty\n";
    }
    CountHelper(meal_cost_map, most_costly_leftover_producing_meals_,
                record.GetMeal(), record.GetCost(), meal_max);
  }  // end of for-loop
}  // end of FillObjects

// ============ Helper enum for Strategies() ===========
// enum class Reason { Expired, TastesBad, TooMuchLeftovers, Unknown };

// ====================================================================
// Postcondition: suggests strategies to reduce left overs & puts them in
// suggested_strategies_to_reduce_leftovers_
// ====================================================================
void LeftoverReport::Strategies() {
  PrintVec(most_common_leftover_reasons_);            // remove later
  if (most_common_leftover_reasons_.empty()) return;  // guard
  suggested_strategies_to_reduce_leftovers_.clear();  // clear
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
  bool hasExpired =
      active_reasons.find(Reason::Expired) != active_reasons.end();
  bool hasTastesBad =
      active_reasons.find(Reason::TastesBad) != active_reasons.end();
  bool hasTooMuch =
      active_reasons.find(Reason::TooMuchLeftovers) != active_reasons.end();

  // 3. Strategy Logic
  if (hasExpired) {
    suggested_strategies_to_reduce_leftovers_.push_back(
        "Donate before expiration");
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
}  // end of Strategies()

// ================================================
//  Postcondition: prints std::vector<std::string>
// ================================================
// print most_costly_leftover_producing_meal - vector
void LeftoverReport::PrintVec(const std::vector<std::string>& vec) const {
  std::cout << "Printing vec-container:\n";
  for (const auto& v : vec) {
    std::cout << "\t" << v << ", ";
  }
  std::cout << "\n";
}

// ======================================================
// Precondition: User has created a leftover record
// Postcondition: Returns most common leftover name(s)
// ======================================================
const std::vector<std::string>& LeftoverReport::GetMostCommonLeftoverNames()
    const {
  return most_common_leftover_names_;
}

// ===============================================================
// Precondition: User has created a leftover record
// Postcondition: Returns the most costly leftover producing meals
// ================================================================
const std::vector<std::string>&
LeftoverReport::GetMostCostlyLeftoverProducingMeals() const {
  return most_costly_leftover_producing_meals_;
}

// ==================================================
// Precondition: User has created a leftover record
// Postcondition: Returns the total cost of leftovers
// ==================================================
double LeftoverReport::GetTotalCostOfLeftovers() const {
  return total_cost_of_leftovers_;
}

// =================================================
// Precondition: User has created a leftover record
// Postcondition: Returns most common leftover reasons
// =================================================
const std::vector<std::string>& LeftoverReport::GetMostCommonLeftoverReasons()
    const {
  return most_common_leftover_reasons_;
}

// ======================================================
// Precondition: User has created a leftover record
// Postcondition: Returns most common disposal mechanisms
// ======================================================
const std::vector<std::string>&
LeftoverReport::GetMostCommonDisposalMechanisms() const {
  return most_common_disposal_mechanisms_;
}

// =======================================================
// Precondition: User has entered a leftover record
// Postcondition: Returns most common strategies to reduce leftovers
// =======================================================
const std::vector<std::string>&
LeftoverReport::GetSuggestedStrategiesToReduceLeftovers() const {
  return suggested_strategies_to_reduce_leftovers_;
}
