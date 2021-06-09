#ifndef TIMERAL_LOG_H
#define TIMERAL_LOG_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>

FILE* fp;

// basename for __FILENAME__
#define __FILENAME__	\
	(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/* Macros for logging in different levels */
#define log_fatal(...)		\
	logger_fatal(fp, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_error(...)		\
	logger_error(fp, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_warn(...)		\
	logger_warn(fp, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_success(...)	\
	logger_success(fp, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_info(...)		\
	logger_info(fp, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_debug(...)		\
	logger_debug(fp, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_trace(...)		\
	logger_trace(fp, __FILENAME__, __LINE__, __VA_ARGS__)


/* logger_init: initialize the logger pointer with the file */
int logger_init(char *filename);

/* logger_close: free up the resources logger allocates */
int logger_close(void);

/* display a log message with fatal level */
void logger_fatal(FILE *fp, char *file, int line, const char *fmt, ...);
/* display a log message with error level */
void logger_error(FILE *fp, char *file, int line, const char *fmt, ...);
/* display a log message with warn level */
void logger_warn(FILE *fp, char *file, int line, const char *fmt, ...);
/* display a log message with success level */
void logger_success(FILE *fp, char *file, int line, const char *fmt, ...);
/* display a log message with info level */
void logger_info(FILE *fp, char *file, int line, const char *fmt, ...);
/* display a log message with debug level */
void logger_debug(FILE *fp, char *file, int line, const char *fmt, ...);
/* display a log message with trace level */
void logger_trace(FILE *fp, char *file, int line, const char *fmt, ...);

/* logger_get_time: get the current time */
char *logger_get_time(void);


#endif // TIMERAL_LOG_H

