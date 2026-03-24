#ifndef LEFTOVER_RECORD_H_
#define LEFTOVER_RECORD_H_

// Stephen Anaba
// CPSC 121L-16
// 3/16/2026
// stevoclock@csu.fullerton.edu
// 3takita

#include <string> // for the std::string class

class LeftoverRecord {
private:
  // private member variables
  std::string date_;
  std::string meal_;
  std::string name_;
  double quantity_;
  std::string reason_;
  std::string disposal_mechanism_;
  double cost_;

public:
  // default constructor
  LeftoverRecord() = default;
  
  // setters
  void SetDate(const std::string& date) { date_ = date; }
  void SetMeal(const std::string& meal) { meal_ = meal; }
  void SetName(const std::string& name) { name_ = name; }
  void SetQuantity(double quantity) { quantity_ = quantity; }
  void SetReason(const std::string& reason) { reason_ = reason; }
  void SetDisposalMechanism(const std::string& disposal_mechanism) { disposal_mechanism_ = disposal_mechanism; }
  void SetCost(double cost) { cost_ = cost; }
  
  // getters
  std::string GetDate() const { return date_; }
  std::string GetMeal() const { return meal_; }
  std::string GetName() const { return name_; }
  double GetQuantity() const { return quantity_; }
  std::string GetReason() const { return reason_; }
  std::string GetDisposalMechanism() const { return disposal_mechanism_; }
  double GetCost() const { return cost_; } 
  
  // overload function for `== operator`
  bool operator==(const LeftoverRecord& other) const {
    return (
      // date_ == other.GetDate() &&
      meal_ == other.GetMeal() &&
      name_ == other.GetName() &&
      quantity_ == other.GetQuantity() &&
      reason_ == other.GetReason() &&
      disposal_mechanism_ == other.GetDisposalMechanism() &&
      cost_ == other.GetCost()
    );
  }
};

#endif
