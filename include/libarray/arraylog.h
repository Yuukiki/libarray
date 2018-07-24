#ifndef ARRAYLOG_H_
#define ARRAYLOG_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#define LOGE(fmt, arg...) \
	__array_log_print(LOG_LEVEL_ERROR, fmt, ##arg)

#define LOGW(fmt, arg...) \
	__array_log_print(LOG_LEVEL_WARN, fmt, ##arg)

#define LOGI(fmt, arg...) \
	__array_log_print(LOG_LEVEL_INFO, fmt, ##arg)

#define LOGD(fmt, arg...) \
	__array_log_print(LOG_LEVEL_DEBUG, fmt, ##arg)

enum LOG_LEVEL {
	LOG_LEVEL_DEBUG = 0,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR
};

void __array_log_print(enum LOG_LEVEL level, const char * fmt, ...);
#endif /* ARRAYLOG_H_ */
