#ifndef ARRAYLOG_H_
#define ARRAYLOG_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#define LOG_BUFFER_SIZE 1024

#define LOGE(fmt, ...) \
	__array_log_print(LOG_LEVEL_ERROR, fmt, __VA_ARGS__)

#define LOGW(fmt, ...) \
	__array_log_print(LOG_LEVEL_WARN, fmt, __VA_ARGS__)

#define LOGI(fmt, ...) \
	__array_log_print(LOG_LEVEL_INFO, fmt, __VA_ARGS__)

#define LOGD(fmt, ...) \
	__array_log_print(LOG_LEVEL_DEBUG, fmt, __VA_ARGS__)

enum LOG_LEVEL {
	LOG_LEVEL_DEBUG = 0,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR
};

void __array_log_print(enum LOG_LEVEL level, const char * fmt, ...);
#endif /* ARRAYLOG_H_ */
