#include "leftover_tracker_backend.h"

#include <filesystem>

#include "leftover_record.h"
#include "leftover_report.h"
#include "server_utils/rapidjson/document.h"      // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h"  // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"     
#include "server_utils/rapidjson/stringbuffer.h"  // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"        // version 3fc79df8-9e2f-4ae2-b929-5dc3e14d98a4

// Util function to convert a LeftoverRecord class object into a serialized
// JSON object. Used in saving data to JSON files
void SerializeLeftoverRecordToJSON(
    const LeftoverRecord& record,
    rapidjson::Writer<rapidjson::StringBuffer>* writer) {
  writer->StartObject();

  writer->String(kFileDataDate);  // DO NOT MODIFY
  std::string date;
  // TODO 1. Use the accessor/getter function for date from the
  // LeftoverRecord class object to get the date and store it in the date
  // string declared above. DONE
  date = record.GetDate();
  writer->String(date.c_str());

  writer->String(kFileDataMeal);  // DO NOT MODIFY
  std::string meal;
  // TODO 2. Use the accessor/getter function for meal from the
  // LeftoverRecord class object to get the meal and store it in the meal
  // string declared above. DONE
  meal = record.GetMeal();
  writer->String(meal.c_str());

  writer->String(kFileDataFoodName);  // DO NOT MODIFY
  std::string food_name;
  // TODO 3. Use the accessor/getter function for food name from the
  // LeftoverRecord class object to get the food name and store it in the
  // food_name string declared above. DONE
  food_name = record.GetName();
  writer->String(food_name.c_str());

  writer->String(kFileDataQtyInOz);  // DO NOT MODIFY
  double quantity;
  // TODO 4. Use the accessor/getter function for quantity from the
  // LeftoverRecord class object to get the quantity and store it in the
  // quantity variable declared above. DONE
  quantitiy = record.GetQuantity();
  writer->Double(quantity);

  writer->String(kFileDataLeftoverReason);  // DO NOT MODIFY
  std::string leftover_reason;
  // TODO 5. Use the accessor/getter function for leftover reason from the
  // LeftoverRecord class object to get the leftover reason and store it in
  // the leftover_reason string declared above. DONE
  leftover_reason = record.GetReason();
  writer->String(leftover_reason.c_str());

  writer->String(kFileDataFoodDisposalMechanism);  // DO NOT MODIFY
  std::string disposal_mechanism;
  // TODO 6. Use the accessor/getter function for disposal mechanism from the
  // LeftoverRecord class object to get the disposal mechanism and store it
  // in the disposal_mechanism string declared above. DONE
  disposal_mechanism = record.GetDisposalMechanism();
  writer->String(disposal_mechanism.c_str());

  writer->String(kFileDataCost);  // DO NOT MODIFY
  double cost;
  // TODO 7. Use the accessor/getter function for cost from the
  // LeftoverRecord class object to get the cost and store it in the cost
  // variable declared above. DONE
  cost = record.GetCost();
  writer->Double(cost);

  writer->EndObject();
}

// Util function to convert a serialized JSON object in to a LeftoverRecord
// class object. Used in loading data from JSON files
LeftoverRecord DeserializeLeftoverRecordFromJSON(
    const rapidjson::Value& json_obj) {
  LeftoverRecord record;
  /* TODO 1. Use the mutator/setter function for date from the LeftoverRecord
   *  class to set the date in `record` object. You can get the date from JSON
   *  object as follows: `json_obj[kFileDataDate].GetString()`.
   *  Use that as a function  argument for the mutator that you'll call.
   */
  record.SetDate(json_obj[kFileDataDate].GetString()); // DONE

  /* TODO 2. Use the mutator/setter function for meal from the LeftoverRecord
   *  class to set the meal in `record` object. You can get the meal from JSON
   *  object as follows: `json_obj[kFileDataMeal].GetString()`.
   *  Use that as a function  argument for the mutator that you'll call.
   */
  record.SetMeal(json_obj[kFileDataMeal].GetString()); // DONE

  /* TODO 3. Use the mutator/setter function for food name from the
   * LeftoverRecord class to set the food name in `record` object. You can
   * get the food name from the JSON object as follows:
   * `json_obj[kFileDataFoodName].GetString()`. Use that as a function
   * argument for the mutator that you'll call.
   */
  record.SetName(json_obj[kFileDataFoodName].GetString()); // DONE

  /* TODO 4. Use the mutator/setter function for quantity from the
   * LeftoverRecord class to set the quantity in `record` object. You can get
   * the quantity from the JSON object as follows:
   * `json_obj[kFileDataQtyInOz].GetDouble()`. Use that as an function  argument
   * for the mutator that you'll call.
   */
  record.SetQuantity(json_obj[kFileDataQtyInOz].GetDouble()); // DONE

  /* TODO 5. Use the mutator/setter function for leftover reason from the
   * LeftoverRecord class to set the leftover reason in `record` object. You
   * can get the leftover reason from the JSON object as follows:
   * `json_obj[kFileDataLeftoverReason].GetString()`. Use that as a function
   * argument for the mutator that you'll call.
   */
  record.SetReason(json_obj[kFileDataLeftoverReason].GetString()); // DONE

  /* TODO 6. Use the mutator/setter function for disposal mechanism from the
   * LeftoverRecord class to set the disposal mechanism in `record` object.
   * You can get the disposal mechanism from the JSON object as follows:
   * `json_obj[kFileDataFoodDisposalMechanism].GetString()`. Use that as an
   * function argument for the mutator that you'll call.
   */
  record.SetDisposalMechanism(json_obj[kFileDataFoodDisposalMechanism].GetString()); // DONE

  /* TODO 7. Use the mutator/setter function for cost from the LeftoverRecord
   *  class to set the cost in `record` object. You can get the cost from the
   * JSON object as follows: `json_obj[kFileDataCost].GetDouble()`. Use that as
   * an function  argument for the mutator that you'll call.
   */
  record.SetCost(json_obj[kFileDataCost].GetDouble()); // DONE
  return record;
}

// Util function to convert a LeftoverRecord class object into a Crow JSON
// object. Used in sending data over the web. Data is formatted in the JSON
// format.
crow::json::wvalue LeftoverRecordToCrowJSON(const LeftoverRecord& record) {
  crow::json::wvalue record_json({});

  std::string date;
  // TODO 1. Use the accessor/getter function for date from the
  // LeftoverRecord class object to get the date and store it in the date
  // string declared above.
 date = record. GetDate(); // DONE
  record_json[kWebDataDate] = date;

  std::string meal;
  // TODO 2. Use the accessor/getter function for meal from the
  // LeftoverRecord class object to get the meal and store it in the meal
  // string declared above.
  meal = record.GetMeal(); // DONE
  record_json[kWebDataMeal] = meal;

  std::string food_name;
  // TODO 3. Use the accessor/getter function for food name from the
  // LeftoverRecord class object to get the food name and store it in the
  // food_name string declared above.
  food_name = record.GetName(); // DONE
  record_json[kWebDataFoodName] = food_name;

  double quantity;
  // TODO 4. Use the accessor/getter function for quantity from the
  // LeftoverRecord class object to get the quantity and store it in the
  // quantity variable declared above.
  quantity = record.GetQuantity(); // DONE
  record_json[kWebDataQtyInOz] = quantity;

  std::string leftover_reason;
  // TODO 5. Use the accessor/getter function for leftover reason from the
  // LeftoverRecord class object to get the leftover reason and store it in
  // the leftover_reason string declared above.
  leftover_reason = record.GetReason(); // DONE
  record_json[kWebDataLeftoverReason] = leftover_reason;

  std::string disposal_mechanism;
  // TODO 6. Use the accessor/getter function for disposal mechanism from the
  // LeftoverRecord class object to get the disposal mechanism and store it
  // in the disposal_mechanism string declared above.
  disposal_mechanism = record.GetDisposalMechanism(); // DONE
  record_json[kWebDataDisposalMechanism] = disposal_mechanism;

  double cost;
  // TODO 7. Use the accessor/getter function for cost from the
  // LeftoverRecord class object to get the cost and store it in the cost
  // variable declared above.
  cost = record.GetCost(); // DONE
  record_json[kWebDataCost] = cost;

  return record_json;
}

// Util function to convert a LeftoverReport object into a serialized
// JSON object. Used in sending data over the web. Data is formatted in the JSON
// format.
crow::json::wvalue LeftoverReportToCrowJSON(const LeftoverReport& report) {
  crow::json::wvalue report_json({});

  std::vector<std::string> most_common_disposal_mechanisms{};
  // TODO: Call the member function of LeftoverReport class that returns all
  // the most common disposal mechanisms as a vector of strings. Store the
  // result in the vector declared above.
  most_common_disposal_mechanisms = report.GetMostCommonDisposalMechanisms(); // DONE
  report_json[kWebReportDataCommonDisposalMechanism] =
      most_common_disposal_mechanisms;

  std::vector<std::string> most_common_leftovers{};
  // TODO: Call the member function of LeftoverReport class that returns all
  // the most common leftovers as a vector of strings. Store the result in
  // the vector declared above.
  most_common_leftovers = report.GetMostCommonLeftoverNames();
  report_json[kWebReportDataCommonLeftOver] = most_common_leftovers; // DONE

  std::vector<std::string> most_common_leftover_reasons{};
  // TODO: Call the member function of LeftoverReport class that returns all
  // the most commonwastage reasons as a vector of strings. Store the result in
  // the vector declared above.
  most_common_leftover_reasons = report.GetMostCommonLeftoverReasons(); // DONE
  report_json[kWebReportDataCommonLeftOverReason] =
      most_common_leftover_reasons;

  std::vector<std::string> most_costly_leftover_producing_meals{};
  // TODO: Call the member function of LeftoverReport class that returns all
  // the most costly waste producing meals as a vector of strings. Store the
  // result in the vector declared above.
  most_costly_leftover_producing_meals = report.GetMostCostlyLeftoverProducingMeals(); // DONE
  report_json[kWebReportDataMostLeftOverProducingMeal] =
      most_costly_leftover_producing_meals;

  std::vector<std::string> suggested_strategies_to_reduce_leftover{};
  // TODO: Call the member function of LeftoverReport class that returns all
  // the suggested strategies as a vector of strings. Store the result in the
  // vector declared above.
  suggested_strategies_to_reduce_leftover = report.GetSuggestedStrategiesToReduceLeftovers(); // DONE
  report_json[kWebReportDataSuggestedReductLeftover] =
      suggested_strategies_to_reduce_leftover;

  double total_cost_of_leftover = -9999.0;
  // TODO: Call the member function of LeftoverReport class that returns the
  // total cost of leftovers as a double. Store the result in the double
  // declared.
  total_cost_of_leftover = report.GetTotalCostOfLeftovers(); // DONE
  report_json[kWebReportDataLeftOverCost] = total_cost_of_leftover;

  return report_json;
}

// Util function to convert a crow query string into a LeftoverRecord class
// object.
LeftoverRecord QueryStringToLeftoverRecord(
    const crow::query_string& query_string) {
  LeftoverRecord record{};

  // TODO 1. Get the date from the query_string using
  // query_string.get(kWebDataDate), and set it in the `record` object using the
  // setter in LeftoverRecord class.
  record.SetDate(query_string.get(kWebDataDate)); // DONE

  // TODO 2. Get the meal from the query_string using
  // query_string.get(kWebDataMeal), and set it in the `record` object using the
  // setter in LeftoverRecord class.
  record.SetDate(query_string.get(kWebDataMeal)); // DONE

  // TODO 3. Get the food name from the query_string using
  // query_string.get(kWebDataFoodName), and set it in the `record` object using
  // the setter in LeftoverRecord class.
  record.SetName(query_string.get(kWebDataFoodName)); // DONE

  // TODO 4. Get the quantity from the query_string using
  // std::stod(query_string.get(kWebDataQtyInOz)), and set it in the `record`
  // object using the setter in LeftoverRecord class.
  record.SetQuantity(query_string.get(kWebDataQtyInOz)); // DONE

  // TODO 5. Get the leftover reason from the query_string using
  // query_string.get(kWebDataLeftoverReason), and set it in the `record` object
  // using the setter in LeftoverRecord class.
  record.SetReason(query_string.get(kWebDataLeftoverReason)); // DONE

  // TODO 6. Get the disposal mechanism from the query_string using
  // query_string.get(kWebDataDisposalMechanism), and set it in the `record`
  // object using the setter in LeftoverRecord class.
  record.SetDisposalMechanism(query_string.get(kWebDataDisposalMechanism)); // DONE

  // TODO 7. Get the cost from the query_string using
  // std::stod(query_string.get(kWebDataCost)), and set it in the `record`
  // object using the setter in LeftoverRecord class.
  record.SetCost(std::stod(query_string.get(kWebDataCost))); // DONE

  return record;
}

bool LeftoverTrackerBackend::LoadRecordsFromJSONFile() { 
  std::ifstream records_file{kLeftoverRecordsFilepath};
  
  if (!records_file.is_open()) {
    std::filesystem::remove(kLeftoverRecordsFilepath);
    return false;
  }
  
  std::stringstream buffer;
  
  buffer << records_file.rdbuf();

  std::string s = buffer.str();
  rapidjson::Document doc;

  if (s.empty()) {
    std::filesystem::remove(kLeftoverRecordsFilepath);
    return false;
  }

  std::string validJson(s);

  bool doc_parse_error = doc.Parse(validJson.c_str()).HasParseError();
  if (doc_parse_error || !doc.IsArray()) {
    std::filesystem::remove(kLeftoverRecordsFilepath);
    return false;
  }
  // iterate through the document
  for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End();
       ++itr) {
    LeftoverRecord record = DeserializeLeftoverRecordFromJSON(*itr);
    // TODO: Call the member function in the LeftoverTracker class to add a
    // `record`
    leftover_tracker_.AddRecord(record); //  DONE.  AddRecord() accepts `record` as an argument.
  }

  records_file.close();
  return true;
}

bool LeftoverTrackerBackend::WriteRecordsToJSONFile() const {
  std::ofstream records_file{kLeftoverRecordsFilepath};
  // Get the records from leftover_tracker_, convert to JSON and
  // save to file.
  rapidjson::StringBuffer ss;
  rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
  writer.StartArray();

  // std::vector<LeftoverRecord> records; // previous declaration
  // TODO: Call the member function in the LeftoverTracker class, on the
  // member object that you added in leftover_tracker.h, that returns all
  // the LeftoverRecord objects. Store the returned records in the vector
  // declared above. Also change the data type of the records vector to `const
  // std::vector<LettoverRecord>&` - better declaration
  const std::vector<LeftoverRecord>& records = leftover_tracker_.GetRecords(); // DONE. NOT SURE
  // since we're using const & to avoid copies, avoid copying each record while looping through them 
  for (const auto& /*LeftoverRecord*/ record : records) {
    SerializeLeftoverRecordToJSON(record, &writer);
  }
  writer.EndArray();

  records_file << ss.GetString();

  records_file.flush();
  records_file.close();
  return true;
}

crow::json::wvalue LeftoverTrackerBackend::AddRecord(
    const crow::query_string& query_string) {
  LeftoverRecord record = QueryStringToLeftoverRecord(query_string);
  crow::json::wvalue status;

  bool add_result = false;
  // TODO: Call the member function in the LeftoverTracker class, on the
  // member object that you added in leftover_tracker.h, that adds a
  // `record` and returns the status of the add operation as a bool. Store the
  // returned value in the bool declared above.
  add_result = leftover_tracker_.AddRecord(record); // DONE
  status[kStatusSuccess] = add_result;

  return status;
}

crow::json::wvalue LeftoverTrackerBackend::DeleteRecord(
    const crow::query_string& query_string) {
  LeftoverRecord record = QueryStringToLeftoverRecord(query_string);
  crow::json::wvalue status;

  bool delete_result = false;
  // TODO: Call the member function in the LefrtoverTracker class, on the
  // member object that you added in leftover_tracker.h, that deletes
  // `record` and returns the status of the delete operation as a bool. Store
  // the returned value in the bool declared above.
  delete_result = leftover_tracker_.DeleteRecord(record); // DONE
  status[kStatusSuccess] = delete_result;

  return status;
}

crow::json::wvalue LeftoverTrackerBackend::GetRecords() const {
  // std::vector<LeftoverRecord> records; // prev declaration
  // TODO: Call the member function in the LeftoverTracker class, on the
  // member object that you added in leftover_tracker.h, that returns all
  // the LeftoverRecord objects. Store the returned records in the vector
  // declared above. Also change the data type of the records vector to `const
  // std::vector<LeftoverRecord>&`.
  const std::vector<LeftoverRecord>& records = leftover_tracker_.GetRecords(); // DONE

  crow::json::wvalue records_json({});
  records_json[kNumRecords] = records.size();

  std::vector<crow::json::wvalue> record_json_vector;
  for (const LeftoverRecord& record : records) {
    record_json_vector.push_back(LeftoverRecordToCrowJSON(record));
  }
  records_json[kRecordArray] = std::move(record_json_vector);
  return records_json;
}

crow::json::wvalue LeftoverTrackerBackend::GetLeftoverReport() const {
  LeftoverReport generated_report;
  // TODO: Call the member function in the LeftoverTracker class, on the
  // member object that you added in leftover_tracker.h, that generates a
  // LeftoverReport object using all the LeftoverRecords and returns it.
  // Store the returned value in the `generated_report` object declared above.
  generated_report = leftover_tracker_.GenerateLeftoverReport(); // DONE

  return LeftoverReportToCrowJSON(generated_report);
}

// Constants used in File Reading/Writing
const char* kFileDataDate = "date_";
const char* kFileDataMeal = "meal_";
const char* kFileDataFoodName = "food_name_";
const char* kFileDataQtyInOz = "qty_in_oz_";
const char* kFileDataLeftoverReason = "leftover_reason_";
const char* kFileDataFoodDisposalMechanism = "disposal_mechanism_";
const char* kFileDataCost = "cost_";

// Constants used in sending/receiving data from the web
const char* kWebDataDate = "date";
const char* kWebDataMeal = "meal";
const char* kWebDataFoodName = "food_name";
const char* kWebDataQtyInOz = "qty_in_oz";
const char* kWebDataLeftoverReason = "leftover_reason";
const char* kWebDataDisposalMechanism = "disposal_mechanism";
const char* kWebDataCost = "cost";

// Constants used in sending/receiving report data from the web.
const char* kWebReportDataCommonDisposalMechanism =
    "most_common_disposal_mechanism_";
const char* kWebReportDataCommonLeftOver = "most_common_leftover_";
const char* kWebReportDataCommonLeftOverReason = "most_common_leftover_reason_";
const char* kWebReportDataMostLeftOverProducingMeal =
    "most_leftover_producing_meal_";
const char* kWebReportDataSuggestedReductLeftover =
    "suggested_strategies_to_reduce_leftover_";
const char* kWebReportDataLeftOverCost = "total_cost_of_leftover_";
