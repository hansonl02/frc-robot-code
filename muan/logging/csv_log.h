/*
 * csv_log.h
 *
 *  Created on: Oct 2, 2015
 *  Copyright 2015 Citrus Circuits
 *      Author: Kyle Stachowicz
 */

#ifndef MUAN_LOGGING_CSV_LOG_H_
#define MUAN_LOGGING_CSV_LOG_H_

#include <string>
#include <utility>
#include <vector>
#include "log.h"
#include "muan/units/units.h"
#include "muan/utils/timer.h"

namespace muan {

/*
 * A log in CSV (comma-separated values) format.
 * Example:
 *  CSVLog log("test", {"key1", "key2"});
 *  log["key1"] = "value1";
 *  log["key2"] = "value2";
 *  log.EndLine();
 */
class CSVLog : public Log {
 public:
  CSVLog(std::string filename, std::vector<std::string> keys);
  virtual void Write(std::string key, std::string value);
  virtual void EndLine();
  virtual std::string &operator[](std::string key);

  void FlushToFile() override;
  std::string GetExtension() const override;

  static void WriteToLog(std::string log, std::string key, std::string value);
  ~CSVLog() override = default;

  const std::vector<std::pair<std::string, std::string>> GetEntries() const;

 private:
  std::stringstream buffer_;
  std::vector<std::pair<std::string, std::string>> entries_;
  Timer timer;
};

}  // namespace muan

#endif /* MUAN_LOGGING_CSV_LOG_H_ */
