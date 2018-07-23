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

const char *LOG_TEXT[] = {
	"\033[;37mDEBUG: ",
	"\033[;36mINFO: ",
	"\033[;33mWARN: ",
	"\033[;31mERROR: "
};

const char* LOG_TEXT_END = "\033[0m";

static inline void __array_log_print(enum LOG_LEVEL level, const char* str, ...)
{
	va_list list;
	va_start(list, str);
	char buffer[1024];
	memset(buffer, 0x0, sizeof(buffer));
	vsnprintf(buffer, sizeof(buffer), str, list);
	va_end(list);
	char *logstr = (char *) malloc(sizeof(char) * 2048);
	strncpy(logstr, LOG_TEXT[level], sizeof(char) * 2048);
	strncat(logstr, buffer, sizeof(char) * 2048);
	strncat(logstr, LOG_TEXT_END, sizeof(char) * 2048);
	printf("%s", logstr);
	free(logstr);
}

#endif /* ARRAYLOG_H_ */
