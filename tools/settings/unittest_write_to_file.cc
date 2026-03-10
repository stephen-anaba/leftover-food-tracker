#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

#include "../../leftover_tracker_backend.h"
#include "../cppaudit/gtest_ext.h"
#include "test_utils.h"

using ::testing::HasSubstr;
using ::testing::Not;
using json = nlohmann::json;

// Helper: read the raw JSON file and parse it as a json array,
// bypassing any backend deserialization/GetRecords logic.
// Returns json::array() if the file can't be opened or parsed.
json ReadJSONArrayFromFile(const std::string& filename) {
  std::ifstream file{filename};
  if (!file.is_open()) {
    return json::array();
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string contents = buffer.str();
  if (contents.empty()) {
    return json::array();
  }
  return json::parse(contents);
}

// Helper: read the raw file contents as a string for error messages.
std::string ReadFileContents(const std::string& filename) {
  std::ifstream file{filename};
  if (!file.is_open()) {
    return "<file could not be opened>";
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string contents = buffer.str();
  if (contents.empty()) {
    return "<file is empty>";
  }
  return contents;
}

TEST(LeftoverTrackerBackend, WriteToFile) {
  const std::string kFilename = "tools/settings/data/temp.json";
  LeftoverTrackerBackend backend{kFilename};
  backend.AddRecord(CreateDefaultQueryString());
  ASSERT_TRUE(backend.WriteRecordsToJSONFile())
      << "Tracker failed to write records to JSON.";

  json file_array = ReadJSONArrayFromFile(kFilename);
  ASSERT_TRUE(file_array.is_array())
      << "Written file is not a JSON array. The file should be written as a "
         "JSON array of record objects (e.g. [{...}]). "
         "Actual file contents: " << ReadFileContents(kFilename);
  ASSERT_EQ(file_array.size(), 1)
      << "Expected exactly 1 record in the JSON file, but found "
      << file_array.size() << ". Make sure that:\n"
         "  1. SerializeLeftoverRecordToJSON correctly writes each field\n"
         "  2. WriteRecordsToJSONFile iterates over all records from the "
         "LeftoverTracker\n"
         "  3. The LeftoverTracker's getter returns the stored records\n"
         "Actual file contents: " << ReadFileContents(kFilename);
  std::remove(kFilename.c_str());
}

TEST(LeftoverTrackerBackend, WriteToFileCheckDefaultRecordContent) {
  const std::string kFilename = "tools/settings/data/temp_content.json";
  LeftoverTrackerBackend backend{kFilename};
  backend.AddRecord(CreateDefaultQueryString());
  ASSERT_TRUE(backend.WriteRecordsToJSONFile())
      << "Tracker failed to write records to JSON.";

  json file_array = ReadJSONArrayFromFile(kFilename);
  ASSERT_TRUE(file_array.is_array())
      << "Written file is not a JSON array. "
         "Actual file contents: " << ReadFileContents(kFilename);
  ASSERT_EQ(file_array.size(), 1)
      << "Expected 1 record in file but found " << file_array.size()
      << ". Actual file contents: " << ReadFileContents(kFilename);

  // Verify each field using the file-format keys (e.g. "date_", "meal_")
  json record = file_array.at(0);
  EXPECT_EQ(record.at("date_"), kDefaultDate)
      << "The date field (\"date_\") in the JSON file does not match. "
         "Expected: \"" << kDefaultDate << "\" but got: \""
      << record.at("date_") << "\". "
         "Make sure you are using the getter for date in "
         "SerializeLeftoverRecordToJSON (TODO 1).";
  EXPECT_EQ(record.at("meal_"), kDefaultMeal)
      << "The meal field (\"meal_\") in the JSON file does not match. "
         "Expected: \"" << kDefaultMeal << "\" but got: \""
      << record.at("meal_") << "\". "
         "Make sure you are using the getter for meal in "
         "SerializeLeftoverRecordToJSON (TODO 2).";
  EXPECT_EQ(record.at("food_name_"), kDefaultFood)
      << "The food_name field (\"food_name_\") in the JSON file does not match. "
         "Expected: \"" << kDefaultFood << "\" but got: \""
      << record.at("food_name_") << "\". "
         "Make sure you are using the getter for food name in "
         "SerializeLeftoverRecordToJSON (TODO 3).";
  EXPECT_DOUBLE_EQ(record.at("qty_in_oz_").get<double>(), kDefaultQty)
      << "The qty_in_oz field (\"qty_in_oz_\") in the JSON file does not match. "
         "Expected: " << kDefaultQty << " but got: "
      << record.at("qty_in_oz_") << ". "
         "Make sure you are using the getter for quantity in "
         "SerializeLeftoverRecordToJSON (TODO 4).";
  EXPECT_EQ(record.at("leftover_reason_"), kDefaultLeftoverReason)
      << "The leftover_reason field (\"leftover_reason_\") in the JSON file "
         "does not match. Expected: \"" << kDefaultLeftoverReason
      << "\" but got: \"" << record.at("leftover_reason_") << "\". "
         "Make sure you are using the getter for leftover reason in "
         "SerializeLeftoverRecordToJSON (TODO 5).";
  EXPECT_EQ(record.at("disposal_mechanism_"), kDefaultDisposal)
      << "The disposal_mechanism field (\"disposal_mechanism_\") in the JSON "
         "file does not match. Expected: \"" << kDefaultDisposal
      << "\" but got: \"" << record.at("disposal_mechanism_") << "\". "
         "Make sure you are using the getter for disposal mechanism in "
         "SerializeLeftoverRecordToJSON (TODO 6).";
  EXPECT_DOUBLE_EQ(record.at("cost_").get<double>(), kDefaultCost)
      << "The cost field (\"cost_\") in the JSON file does not match. "
         "Expected: " << kDefaultCost << " but got: "
      << record.at("cost_") << ". "
         "Make sure you are using the getter for cost in "
         "SerializeLeftoverRecordToJSON (TODO 7).";
  std::remove(kFilename.c_str());
}

TEST(LeftoverTrackerBackend, WriteToFileCheckCustomRecordContent) {
  const std::string kFilename = "tools/settings/data/temp_custom.json";
  LeftoverTrackerBackend backend{kFilename};

  std::string custom_date = "2024-01-15";
  std::string custom_meal = "Breakfast";
  std::string custom_food = "Eggs";
  double custom_qty = 3.5;
  std::string custom_disposal = "Compost";
  double custom_cost = 2.75;
  std::string custom_reason = "Tastes bad";

  backend.AddRecord(QueryStringfromRecordDetails(
      custom_date, custom_meal, custom_food, custom_qty, custom_disposal,
      custom_cost, custom_reason));
  ASSERT_TRUE(backend.WriteRecordsToJSONFile())
      << "Tracker failed to write records to JSON.";

  json file_array = ReadJSONArrayFromFile(kFilename);
  ASSERT_TRUE(file_array.is_array())
      << "Written file is not a JSON array. "
         "Actual file contents: " << ReadFileContents(kFilename);
  ASSERT_EQ(file_array.size(), 1)
      << "Expected 1 record in file but found " << file_array.size()
      << ". Actual file contents: " << ReadFileContents(kFilename);

  json record = file_array.at(0);
  EXPECT_EQ(record.at("date_"), custom_date)
      << "The date field (\"date_\") does not match the custom value. "
         "Expected: \"" << custom_date << "\" but got: \""
      << record.at("date_") << "\". "
         "Check that QueryStringToLeftoverRecord sets the date (TODO 1) and "
         "SerializeLeftoverRecordToJSON reads it back (TODO 1).";
  EXPECT_EQ(record.at("meal_"), custom_meal)
      << "The meal field (\"meal_\") does not match the custom value. "
         "Expected: \"" << custom_meal << "\" but got: \""
      << record.at("meal_") << "\". "
         "Check that QueryStringToLeftoverRecord sets the meal (TODO 2) and "
         "SerializeLeftoverRecordToJSON reads it back (TODO 2).";
  EXPECT_EQ(record.at("food_name_"), custom_food)
      << "The food_name field (\"food_name_\") does not match the custom value. "
         "Expected: \"" << custom_food << "\" but got: \""
      << record.at("food_name_") << "\". "
         "Check that QueryStringToLeftoverRecord sets food name (TODO 3) and "
         "SerializeLeftoverRecordToJSON reads it back (TODO 3).";
  EXPECT_DOUBLE_EQ(record.at("qty_in_oz_").get<double>(), custom_qty)
      << "The qty_in_oz field (\"qty_in_oz_\") does not match the custom value. "
         "Expected: " << custom_qty << " but got: "
      << record.at("qty_in_oz_") << ". "
         "Check that QueryStringToLeftoverRecord sets quantity (TODO 4) and "
         "SerializeLeftoverRecordToJSON reads it back (TODO 4).";
  EXPECT_EQ(record.at("leftover_reason_"), custom_reason)
      << "The leftover_reason field (\"leftover_reason_\") does not match. "
         "Expected: \"" << custom_reason << "\" but got: \""
      << record.at("leftover_reason_") << "\". "
         "Check that QueryStringToLeftoverRecord sets leftover reason (TODO 5) "
         "and SerializeLeftoverRecordToJSON reads it back (TODO 5).";
  EXPECT_EQ(record.at("disposal_mechanism_"), custom_disposal)
      << "The disposal_mechanism field (\"disposal_mechanism_\") does not match. "
         "Expected: \"" << custom_disposal << "\" but got: \""
      << record.at("disposal_mechanism_") << "\". "
         "Check that QueryStringToLeftoverRecord sets disposal mechanism "
         "(TODO 6) and SerializeLeftoverRecordToJSON reads it back (TODO 6).";
  EXPECT_DOUBLE_EQ(record.at("cost_").get<double>(), custom_cost)
      << "The cost field (\"cost_\") does not match the custom value. "
         "Expected: " << custom_cost << " but got: "
      << record.at("cost_") << ". "
         "Check that QueryStringToLeftoverRecord sets cost (TODO 7) and "
         "SerializeLeftoverRecordToJSON reads it back (TODO 7).";
  std::remove(kFilename.c_str());
}

TEST(LeftoverTrackerBackend, WriteToFileMultipleRecords) {
  const std::string kFilename = "tools/settings/data/temp_multi.json";
  LeftoverTrackerBackend backend{kFilename};

  backend.AddRecord(CreateDefaultQueryStringWithFoodName("Pizza"));
  backend.AddRecord(CreateDefaultQueryStringWithFoodName("Salad"));
  backend.AddRecord(CreateDefaultQueryStringWithFoodName("Soup"));
  ASSERT_TRUE(backend.WriteRecordsToJSONFile())
      << "Tracker failed to write multiple records to JSON.";

  json file_array = ReadJSONArrayFromFile(kFilename);
  ASSERT_TRUE(file_array.is_array())
      << "Written file is not a JSON array. "
         "Actual file contents: " << ReadFileContents(kFilename);
  ASSERT_EQ(file_array.size(), 3)
      << "Expected 3 records in the JSON file but found " << file_array.size()
      << ". Make sure WriteRecordsToJSONFile iterates over ALL records "
         "returned by the LeftoverTracker's getter, not just the first one.\n"
         "Actual file contents: " << ReadFileContents(kFilename);

  std::vector<std::string> expected_foods = {"Pizza", "Salad", "Soup"};
  std::vector<std::string> actual_foods;
  for (const auto& rec : file_array) {
    actual_foods.push_back(rec.at("food_name_").get<std::string>());
  }
  std::sort(expected_foods.begin(), expected_foods.end());
  std::sort(actual_foods.begin(), actual_foods.end());
  EXPECT_EQ(actual_foods, expected_foods)
      << "The food names written to the file don't match what was added. "
         "Expected: {Pizza, Salad, Soup} but got different values. "
         "Make sure each record's food_name is being serialized correctly "
         "in SerializeLeftoverRecordToJSON (TODO 3).";
  std::remove(kFilename.c_str());
}

TEST(LeftoverTrackerBackend, WriteToFileOverwritesPreviousContent) {
  const std::string kFilename = "tools/settings/data/temp_overwrite.json";
  LeftoverTrackerBackend backend{kFilename};

  backend.AddRecord(CreateDefaultQueryStringWithFoodName("Rice"));
  backend.AddRecord(CreateDefaultQueryStringWithFoodName("Beans"));
  ASSERT_TRUE(backend.WriteRecordsToJSONFile())
      << "Tracker failed to write records to JSON.";

  // Create a new backend, add only one record, and write again
  LeftoverTrackerBackend backend2{kFilename};
  backend2.AddRecord(CreateDefaultQueryStringWithFoodName("Tacos"));
  ASSERT_TRUE(backend2.WriteRecordsToJSONFile())
      << "Tracker failed to overwrite records to JSON.";

  // Read the raw file and verify only the latest record is present
  json file_array = ReadJSONArrayFromFile(kFilename);
  ASSERT_TRUE(file_array.is_array())
      << "Written file is not a JSON array after overwrite. "
         "Actual file contents: " << ReadFileContents(kFilename);
  ASSERT_EQ(file_array.size(), 1)
      << "After writing a second time with 1 record, the file should contain "
         "only 1 record, but found " << file_array.size() << ". "
         "WriteRecordsToJSONFile should overwrite (not append to) the file. "
         "Make sure you are opening the file with std::ofstream (which "
         "truncates by default).\n"
         "Actual file contents: " << ReadFileContents(kFilename);

  EXPECT_EQ(file_array.at(0).at("food_name_"), "Tacos")
      << "After overwriting the file, expected food_name_ to be \"Tacos\" "
         "but got: \"" << file_array.at(0).at("food_name_") << "\". "
         "The file should reflect only the records from the most recent "
         "WriteRecordsToJSONFile call.";
  std::remove(kFilename.c_str());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(new SkipListener());
  return RUN_ALL_TESTS();
}
