#ifndef LEFTOVER_RECORD_H_
#define LEFTOVER_RECORD_H_

// Stephen Anaba
// CPSC 121L-01
// 3/16/2026
// stevoclock@csu.fullerton.edu
// 3takita

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
  // non-defaault constructor
  LeftoverRecord(
      const std::string& date,
      const std::string& meal,
      const std::string& name,
      double quantity,
      const std::string& reason,
      const std::string& disposal_mechanism,
      double cost
      ) : date_(date), meal_(meal), name_(name), quantity_(quantity), reason_(reason), disposal_mechanism_(disposal_mechanism), cost_(cost) {}
  // setters
  void SetDate(const std::string& date) { date_ = date; }
  void SetMeal(const std::string& meal) { meal_ = meal; }
  void SetName(const std::string& name) { name_ = name; }
  void SetQuantity(double quantitiy) { quantity_ = quantity; }
  void SetReason(const std::string& reason) { reason_ = reason; }
  void SetDisposalMechanism(const std::string& disposal_mechanism) { disposal_mechanism_ = disposal_mechanism; }
  void SetCost(double cost) { cost_ = cost; }
  // getters
  std::string GetDate() const { date_ = date; }
  std::string GetMeal() const { meal_ = meal; }
  std::string GetName() const { name_ = name; }
  double GetQuantity() const { quantity_ = quantity; }
  std::string GetReason() const { reason_ = reason; }
  std::string GetDisposalMechanism() const { disposal_mechanism_ = disposal_mechanism; }
  double GetCost() const { cost_ = cost; }

  // ======================= YOUR CODE HERE =======================
  // Write the LeftoverRecord class here. Refer to your class design for the
  // member variables, constructors, and member functions needed.
  //
  // Note: mark functions that do not modify the member variables
  // as const, by writing `const` after the parameter list.
  // Pass objects by const reference when appropriate.
  // Remember that std::string is an object!
  // ===============================================================
};

#endif
