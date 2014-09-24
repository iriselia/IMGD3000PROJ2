///
/// The log manager
/// 

#pragma once

#include <stdio.h>

#include "Manager.h"
#include "utility.h"

#define DF_LOGFILE_NAME "dragonfly.log"

class LogManager : public Manager {

 private:
  LogManager();                      ///< Private since a singleton.
  LogManager(LogManager const&) = delete;    ///< Don't allow copy.
  void operator=(LogManager const&) = delete; ///< Don't allow assignment.

  bool do_flush;                     ///< True if flush after each write.
  FILE *fp;                 ///< Pointer to logfile.
  int log_level;                     ///< Logging level.
  bool log_time_string;              ///< True if prepend time.
  bool log_step_count;               ///< True if prepend step count.

 public:
  /// If logfile is open, close it.
  ~LogManager();

  /// Get the one and only instance of the LogManager.
  static LogManager &getInstance() {
	  static LogManager instance;
	  return instance;
  }

  /// Start up LogManager (open logfile "dragonfly.log").
  int startUp();

  /// Shut down LogManager (close logfile).
  void shutDown();

  /// Write to logfile.
  /// Supports printf() formatting of strings.
  /// Return bytes written (excluding prepends), -1 if error.
  int writeLog(const char *fmt, ...) const;

  /// Write to logfile.
  /// Only write if indicated log level >= LogManager log level
  /// Supports printf() formatting of strings.
  /// Return bytes written (excluding prepends), -1 if error.
  int writeLog(int log_level, const char *fmt, ...) const;

  /// Set logging level.
  void setLogLevel(int log_level)
  {
	  this->log_level = log_level;
  }

  /// Get logging level.
  int getLogLevel() const
  {
	  return this->log_level;
  }
  
  /// Set flush of logfile after each write.
  void setFlush(bool do_flush = true)
  {
	  this->do_flush = do_flush;
  }
  
  /// Set prepend time string to log messages.
  void setLogTimeString(bool log_time_string = true)
  {
	  this->log_time_string = log_time_string;
  }
  
  /// Set prepend step count to log messages.
  void setLogStepCount(bool log_step_count = true)
  {
	  this->log_step_count = log_step_count;
  }
};
