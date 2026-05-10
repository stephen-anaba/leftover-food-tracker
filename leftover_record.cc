// Stephen Anaba
// <Your section number> (e.g. CPSC 121L-01)
// <Date>
// <Your csu.fullerton.edu email>
// <Your GitHub username>

#include "leftover_record.h"

// ========================= YOUR CODE HERE =========================
// This implementation file is where you should implement
// the member functions declared in the header (leftover_record.h), only
// if you didn't implement them inline within leftover_record.h.
//
// Remember to specify the name of the class with :: in this format:
//     <return type> MyClassName::MyFunction() {
//        ...
//     }
// to tell the compiler that each function belongs to the LeftLeftoverRecord
// class.
// ===================================================================
LeftoverRecord::LeftoverRecord() : quantity_(0.0), cost_(0.0) {}

// setters
void LeftoverRecord::SetDate(const std::string& date) { date_ = date; }
void LeftoverRecord::SetMeal(const std::string& meal) { meal_ = meal; }
void LeftoverRecord::SetName(const std::string& name) { name_ = name; }
void LeftoverRecord::SetQuantity(double quantity) { quantity_ = quantity; }
void LeftoverRecord::SetReason(const std::string& reason) { reason_ = reason; }
void LeftoverRecord::SetDisposalMechanism(
    const std::string& disposal_mechanism) {
  disposal_mechanism_ = disposal_mechanism;
}
void LeftoverRecord::SetCost(double cost) { cost_ = cost; }

// getters
std::string LeftoverRecord::GetDate() const { return date_; }
std::string LeftoverRecord::GetMeal() const { return meal_; }
std::string LeftoverRecord::GetName() const { return name_; }
double LeftoverRecord::GetQuantity() const { return quantity_; }
std::string LeftoverRecord::GetReason() const { return reason_; }
std::string LeftoverRecord::GetDisposalMechanism() const {
  return disposal_mechanism_;
}
double LeftoverRecord::GetCost() const { return cost_; }

// overload function for `== operator`
bool LeftoverRecord::operator==(const LeftoverRecord& other) const {
  return (date_ == other.GetDate() && meal_ == other.GetMeal() &&
          name_ == other.GetName() && quantity_ == other.GetQuantity() &&
          reason_ == other.GetReason() &&
          disposal_mechanism_ == other.GetDisposalMechanism() &&
          cost_ == other.GetCost());
}
