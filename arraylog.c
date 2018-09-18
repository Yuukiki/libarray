#include <libarray/arraylog.h>

static const char *LOG_TEXT[] = {
	"\033[;37mDEBUG: ",
	"\033[;36mINFO: ",
	"\033[;33mWARN: ",
	"\033[;31mERROR: "
};

static const char* LOG_TEXT_END = "\033[0m";

void __array_log_print(enum LOG_LEVEL level, const char* str, ...)
{
	va_list list;
	va_start(list, str);
	char buffer[LOG_BUFFER_SIZE];
	memset(buffer, 0x0, sizeof(buffer));
	vsnprintf(buffer, sizeof(buffer), str, list);
	va_end(list);
	static const uint64_t logstr_size = sizeof(char) * LOG_BUFFER_SIZE * 2;
	char *logstr = (char *) malloc(logstr_size);
	strncpy(logstr, LOG_TEXT[level], logstr_size);
	strncat(logstr, buffer, logstr_size);
	strncat(logstr, LOG_TEXT_END, logstr_size);
	printf("%s", logstr);
	free(logstr);
}
