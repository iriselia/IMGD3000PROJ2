#include <string>
#include <fstream>
#include <stdarg.h>
#include "LogManager.h"

LogManager::LogManager()
{

}

LogManager::~LogManager()
{

}

int LogManager::startUp()
{
	//start up base first
	bool b_isFailed = Manager::startUp();

	if (!b_isFailed) {
		fp = fopen(DF_LOGFILE_NAME, "w");
		if (fp) {
			writeLog("LogManager: Log File Opened Successfully.\n");
		}
		else {
			fprintf(stderr, "LogManager: Fatal Error: Unable to open file.\n");
			b_isFailed = true;
		}
	}

	writeLog("LogManager: Initialized.\n");
	return b_isFailed;
}

void LogManager::shutDown()
{
	if (this->isStarted())
	{
		auto& logManager = LogManager::getInstance();
		logManager.writeLog("LogManager: Shutting down.\n");
		fclose(fp);
		//shutdown base at the end
		Manager::shutDown();
	}

}

int LogManager::writeLog(const char *fmt, ...) const
{
	va_list args;
	va_start(args, fmt);
	int bytesWrote = vfprintf(fp, fmt, args);
	va_end(args);

	if (do_flush)
	{
		fflush(fp);
	}

	return bytesWrote;
}

int LogManager::writeLog(int log_level, const char *fmt, ...) const
{
	if (log_level >= this->log_level)
	{
		return writeLog(fmt);
	}
	else
	{
		return 0;
	}
}