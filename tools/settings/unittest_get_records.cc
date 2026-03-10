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
#include "test_utils.h"

using ::testing::HasSubstr;
using ::testing::Not;
using json = nlohmann::json;

TEST(LeftoverTrackerBackend, GetRecords) {
  LeftoverTrackerBackend backend{""};
  ASSERT_TRUE(loadTrackerWithDefaultTestData(backend));

  json records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 6)
      << "Failed to return all the records.";
}

// Add, then get a record
TEST(LeftoverTrackerBackend, AddAndGetRecord) {
  // Load records to backend
  LeftoverTrackerBackend backend{""};
  ASSERT_TRUE(loadTrackerWithDefaultTestData(backend));
  json records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 6)
      << "Failed to return all the records.";

  // Create and add new record
  json add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithFoodName("Pineapples"))
          .dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add the leftover record. Make sure that Feature 1 is "
         "functioning properly before working on Get Records feature.";

  // There are now 7 records
  records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 7)
      << "Failed to return all the records.";
}

// Get records with a large number of records already added
TEST(LeftoverTrackerBackend, GetManyRecords) {
  // Load records to backend
  LeftoverTrackerBackend backend{""};
  ASSERT_TRUE(loadTrackerWithDefaultTestData(backend));
  json records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 6);

  // Create and add new records
  for (int i = 0; i < BIG_N; i++) {
    json add_status = json::parse(
        backend.AddRecord(CreateDefaultQueryStringWithCost(i + 1)).dump());
    ASSERT_TRUE(add_status.at("success"));
  }

  // There are now BIG_N + 6 records
  records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == BIG_N + 6);
}

// Add a record, retrieve it, and verify all fields match
TEST(LeftoverTrackerBackend, AddAndGetRecordContent) {
  LeftoverTrackerBackend backend{""};

  json add_status =
      json::parse(backend.AddRecord(CreateDefaultQueryString()).dump());
  ASSERT_TRUE(add_status.at("success")) << "Failed to add the record.";

  json records = json::parse(backend.GetRecords().dump());
  ASSERT_EQ(records.at("num_records"), 1)
      << "Expected exactly 1 record after adding one record.";

  json record = records.at("record_array").at(0);
  EXPECT_EQ(record.at("date"), kDefaultDate)
      << "Retrieved record's date does not match what was added. "
         "Check that AddRecord correctly stores the date and that "
         "GetRecords correctly retrieves it.";
  EXPECT_EQ(record.at("meal"), kDefaultMeal)
      << "Retrieved record's meal does not match what was added. "
         "Check that AddRecord correctly stores the meal and that "
         "GetRecords correctly retrieves it.";
  EXPECT_EQ(record.at("food_name"), kDefaultFood)
      << "Retrieved record's food_name does not match what was added. "
         "Check that AddRecord correctly stores the food_name and that "
         "GetRecords correctly retrieves it.";
  EXPECT_NEAR(record.at("qty_in_oz").get<double>(), kDefaultQty, 1e-9)
      << "Retrieved record's qty_in_oz does not match what was added. "
         "Check that AddRecord correctly stores the qty_in_oz and that "
         "GetRecords correctly retrieves it.";
  EXPECT_EQ(record.at("disposal_mechanism"), kDefaultDisposal)
      << "Retrieved record's disposal_mechanism does not match what was added. "
         "Check that AddRecord correctly stores the disposal_mechanism and that "
         "GetRecords correctly retrieves it.";
  EXPECT_NEAR(record.at("cost").get<double>(), kDefaultCost, 1e-9)
      << "Retrieved record's cost does not match what was added. "
         "Check that AddRecord correctly stores the cost and that "
         "GetRecords correctly retrieves it.";
  EXPECT_EQ(record.at("leftover_reason"), kDefaultLeftoverReason)
      << "Retrieved record's leftover_reason does not match what was added. "
         "Check that AddRecord correctly stores the leftover_reason and that "
         "GetRecords correctly retrieves it.";
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(new SkipListener());
  return RUN_ALL_TESTS();
}
