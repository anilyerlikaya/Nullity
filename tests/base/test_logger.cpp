#include "test.h"
#include <utils/Logger.h>

int test_logger(int argc, char** argv) {
    printf("\n*******************\nTest: Logger\n*******************\n\n");

    nl::Logger* logger = nl::Logger::getInstance("logger.txt", "../Logs");
    printf("logger_path: %s\n", logger->getLogPath().c_str());

    logger->Log("initialized!\n");
    logger->Log("this is warning!\n", nl::LogType(1));
    logger->Log("this is error!\n", nl::LogType(2));
    logger->Log("just info, no big deal:)\n", nl::LogType(0));
    logger->Log("this is warning again!\n", nl::LogType(1));
    logger->Log("this is notype!\n", nl::LogType(-1));

    return 0;
}