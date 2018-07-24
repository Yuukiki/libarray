#include <libarray/arraylog.h>

const static char *LOG_TEXT[] = {
	"\033[;37mDEBUG: ",
	"\033[;36mINFO: ",
	"\033[;33mWARN: ",
	"\033[;31mERROR: "
};

const static char* LOG_TEXT_END = "\033[0m";

void __array_log_print(enum LOG_LEVEL level, const char* str, ...)
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
