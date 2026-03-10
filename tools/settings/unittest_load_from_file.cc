#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../../leftover_tracker_backend.h"
#include "../cppaudit/gtest_ext.h"

using ::testing::HasSubstr;
using ::testing::Not;
using json = nlohmann::json;

TEST(LeftoverTrackerBackend, LoadFromFile) {
  std::string kFilename = "tools/settings/data/leftover_records.json";
  LeftoverTrackerBackend backend{kFilename};
  ASSERT_TRUE(backend.LoadRecordsFromJSONFile())
      << "Failed to load records from JSON file.";

  json records = json::parse(backend.GetRecords().dump());
  if (records.at("num_records") > 6) {
    ASSERT_TRUE(records.at("num_records") == 6)
        << "Tracker contains more than expected records after loading from "
           "JSON.";
  } else {
    ASSERT_TRUE(records.at("num_records") == 6)
        << "Tracker contains fewer than expected records after loading from "
           "JSON.";
  }

  json record_array = records.at("record_array");
  ASSERT_TRUE(record_array.is_array())
      << "GetRecords should return a JSON object with a record_array.";
  ASSERT_EQ(record_array.size(), 6)
      << "record_array size does not match the number of records in the JSON "
         "file.";

  // Verify the first record (Milk) was loaded correctly from the file.
  ASSERT_EQ(record_array.at(0).at("date"), "2023-10-18")
      << "First record's date was not loaded correctly from the JSON file. "
         "Expected \"2023-10-18\".";
  ASSERT_EQ(record_array.at(0).at("meal"), "Breakfast")
      << "First record's meal was not loaded correctly from the JSON file. "
         "Expected \"Breakfast\".";
  ASSERT_EQ(record_array.at(0).at("food_name"), "Milk")
      << "First record's food_name was not loaded correctly from the JSON "
         "file. Expected \"Milk\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(0).at("qty_in_oz")),
              8.0, 1e-9)
      << "First record's qty_in_oz was not loaded correctly from the JSON "
         "file. Expected 8.0.";
  ASSERT_EQ(record_array.at(0).at("leftover_reason"), "Expired")
      << "First record's leftover_reason was not loaded correctly from the "
         "JSON file. Expected \"Expired\".";
  ASSERT_EQ(record_array.at(0).at("disposal_mechanism"), "Sink")
      << "First record's disposal_mechanism was not loaded correctly from the "
         "JSON file. Expected \"Sink\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(0).at("cost")),
              2.0, 1e-9)
      << "First record's cost was not loaded correctly from the JSON file. "
         "Expected 2.0.";

  // Verify the second record (Rice) was loaded correctly from the file.
  ASSERT_EQ(record_array.at(1).at("date"), "2023-10-19")
      << "Second record's date was not loaded correctly from the JSON file. "
         "Expected \"2023-10-19\".";
  ASSERT_EQ(record_array.at(1).at("meal"), "Lunch")
      << "Second record's meal was not loaded correctly from the JSON file. "
         "Expected \"Lunch\".";
  ASSERT_EQ(record_array.at(1).at("food_name"), "Rice")
      << "Second record's food_name was not loaded correctly from the JSON "
         "file. Expected \"Rice\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(1).at("qty_in_oz")),
              2.0, 1e-9)
      << "Second record's qty_in_oz was not loaded correctly from the JSON "
         "file. Expected 2.0.";
  ASSERT_EQ(record_array.at(1).at("leftover_reason"), "Too much left overs")
      << "Second record's leftover_reason was not loaded correctly from the "
         "JSON file. Expected \"Too much left overs\".";
  ASSERT_EQ(record_array.at(1).at("disposal_mechanism"), "Trash")
      << "Second record's disposal_mechanism was not loaded correctly from the "
         "JSON file. Expected \"Trash\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(1).at("cost")),
              1.2, 1e-9)
      << "Second record's cost was not loaded correctly from the JSON file. "
         "Expected 1.2.";

  // Verify the third record (Bread) was loaded correctly from the file.
  ASSERT_EQ(record_array.at(2).at("date"), "2023-10-19")
      << "Third record's date was not loaded correctly from the JSON file. "
         "Expected \"2023-10-19\".";
  ASSERT_EQ(record_array.at(2).at("meal"), "Dinner")
      << "Third record's meal was not loaded correctly from the JSON file. "
         "Expected \"Dinner\".";
  ASSERT_EQ(record_array.at(2).at("food_name"), "Bread")
      << "Third record's food_name was not loaded correctly from the JSON "
         "file. Expected \"Bread\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(2).at("qty_in_oz")),
              3.0, 1e-9)
      << "Third record's qty_in_oz was not loaded correctly from the JSON "
         "file. Expected 3.0.";
  ASSERT_EQ(record_array.at(2).at("leftover_reason"), "Expired")
      << "Third record's leftover_reason was not loaded correctly from the "
         "JSON file. Expected \"Expired\".";
  ASSERT_EQ(record_array.at(2).at("disposal_mechanism"), "Trash")
      << "Third record's disposal_mechanism was not loaded correctly from the "
         "JSON file. Expected \"Trash\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(2).at("cost")),
              0.5, 1e-9)
      << "Third record's cost was not loaded correctly from the JSON file. "
         "Expected 0.5.";

  // Verify the fourth record (Oats) was loaded correctly from the file.
  ASSERT_EQ(record_array.at(3).at("date"), "2023-10-20")
      << "Fourth record's date was not loaded correctly from the JSON file. "
         "Expected \"2023-10-20\".";
  ASSERT_EQ(record_array.at(3).at("meal"), "Breakfast")
      << "Fourth record's meal was not loaded correctly from the JSON file. "
         "Expected \"Breakfast\".";
  ASSERT_EQ(record_array.at(3).at("food_name"), "Oats")
      << "Fourth record's food_name was not loaded correctly from the JSON "
         "file. Expected \"Oats\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(3).at("qty_in_oz")),
              5.0, 1e-9)
      << "Fourth record's qty_in_oz was not loaded correctly from the JSON "
         "file. Expected 5.0.";
  ASSERT_EQ(record_array.at(3).at("leftover_reason"), "Tastes bad")
      << "Fourth record's leftover_reason was not loaded correctly from the "
         "JSON file. Expected \"Tastes bad\".";
  ASSERT_EQ(record_array.at(3).at("disposal_mechanism"), "Compost")
      << "Fourth record's disposal_mechanism was not loaded correctly from the "
         "JSON file. Expected \"Compost\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(3).at("cost")),
              1.3, 1e-9)
      << "Fourth record's cost was not loaded correctly from the JSON file. "
         "Expected 1.3.";

  // Verify the fifth record (Cake) was loaded correctly from the file.
  ASSERT_EQ(record_array.at(4).at("date"), "2023-10-22")
      << "Fifth record's date was not loaded correctly from the JSON file. "
         "Expected \"2023-10-22\".";
  ASSERT_EQ(record_array.at(4).at("meal"), "Dinner")
      << "Fifth record's meal was not loaded correctly from the JSON file. "
         "Expected \"Dinner\".";
  ASSERT_EQ(record_array.at(4).at("food_name"), "Cake")
      << "Fifth record's food_name was not loaded correctly from the JSON "
         "file. Expected \"Cake\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(4).at("qty_in_oz")),
              5.0, 1e-9)
      << "Fifth record's qty_in_oz was not loaded correctly from the JSON "
         "file. Expected 5.0.";
  ASSERT_EQ(record_array.at(4).at("leftover_reason"), "Tastes bad")
      << "Fifth record's leftover_reason was not loaded correctly from the "
         "JSON file. Expected \"Tastes bad\".";
  ASSERT_EQ(record_array.at(4).at("disposal_mechanism"), "Donation")
      << "Fifth record's disposal_mechanism was not loaded correctly from the "
         "JSON file. Expected \"Donation\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(4).at("cost")),
              4.0, 1e-9)
      << "Fifth record's cost was not loaded correctly from the JSON file. "
         "Expected 4.0.";

  // Verify the last record (Pasta) was loaded correctly from the file.
  ASSERT_EQ(record_array.at(5).at("date"), "2023-10-21")
      << "Last record's date was not loaded correctly from the JSON file. "
         "Expected \"2023-10-21\".";
  ASSERT_EQ(record_array.at(5).at("meal"), "Dinner")
      << "Last record's meal was not loaded correctly from the JSON file. "
         "Expected \"Dinner\".";
  ASSERT_EQ(record_array.at(5).at("food_name"), "Pasta")
      << "Last record's food_name was not loaded correctly from the JSON "
         "file. Expected \"Pasta\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(5).at("qty_in_oz")),
              5.0, 1e-9)
      << "Last record's qty_in_oz was not loaded correctly from the JSON "
         "file. Expected 5.0.";
  ASSERT_EQ(record_array.at(5).at("leftover_reason"), "Too much left overs")
      << "Last record's leftover_reason was not loaded correctly from the "
         "JSON file. Expected \"Too much left overs\".";
  ASSERT_EQ(record_array.at(5).at("disposal_mechanism"), "Donation")
      << "Last record's disposal_mechanism was not loaded correctly from the "
         "JSON file. Expected \"Donation\".";
  ASSERT_NEAR(static_cast<double>(record_array.at(5).at("cost")),
              4.5, 1e-9)
      << "Last record's cost was not loaded correctly from the JSON file. "
         "Expected 4.5.";
}

TEST(LeftoverTrackerBackend, LoadFromFileTotalCost) {
  std::string kFilename = "tools/settings/data/leftover_records.json";
  LeftoverTrackerBackend backend{kFilename};
  ASSERT_TRUE(backend.LoadRecordsFromJSONFile())
      << "Failed to load records from JSON file.";

  json records = json::parse(backend.GetRecords().dump());
  json record_array = records.at("record_array");

  double total_cost = 0.0;
  for (size_t i = 0; i < record_array.size(); ++i) {
    total_cost += static_cast<double>(record_array.at(i).at("cost"));
  }

  ASSERT_NEAR(total_cost, 13.5, 1e-9)
      << "Total cost of all loaded records does not match the expected value "
         "of 13.5. Ensure each record's cost field is loaded correctly from "
         "the JSON file.";
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(new SkipListener());
  return RUN_ALL_TESTS();
}
