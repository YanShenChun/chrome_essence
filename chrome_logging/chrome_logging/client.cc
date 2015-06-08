#include <stdio.h>
#include <tchar.h>
#include "base\logging.h"
#include "base\command_line.h"

int main(int argc, const char* const argv[])
{
    base::CommandLine::Init(argc, argv);
    logging::LoggingSettings settings;
    settings.logging_dest = logging::LOG_TO_SYSTEM_DEBUG_LOG;
    logging::InitLogging(settings);
    
    logging::SetLogItems(true, true, false, false);
    
    LOG(INFO) << "INFO";
    LOG(WARNING) << "WARNING";
    LOG(ERROR) << "ERROR";
    
    LOG_IF(INFO, true) << "LOG_IF INFO";
    LOG_IF(WARNING, false) << "LOG_IF WARNING";
    LOG_IF(ERROR, true) << "LOG_IF ERROR";

    return 0;
}