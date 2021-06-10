#ifndef TIMERAL_LOG_H
#define TIMERAL_LOG_H

#include <stdarg.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define F_DEST "/tmp/timeral.log"

/*
* Macro to get the basename of the __FILE__ macro.
*/

#define __FILENAME__	\
	(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/*
** Global variables, the file descriptor to write on, and the log level.
*/
int			g_log_fd;
int			g_log_lvl;

/*
** Tools functions.
*/

int	logger_init_open_file(char *log_file);

void logger_fatal(int fd, char *file, int line, const char *fmt, ...);
void logger_error(int fd, char *file, int line, const char *fmt, ...);
void logger_warn(int fd, char *file, int line, const char *fmt, ...);
void logger_success(int fd, char *file, int line, const char *fmt, ...);
void logger_info(int fd, char *file, int line, const char *fmt, ...);
void logger_debug(int fd, char *file, int line, const char *fmt, ...);
void logger_trace(int fd, char *file, int line, const char *fmt, ...);

char *logger_get_time(void);

#define D_OFF 0

#define D_ERROR 2
#define D_WARN	3
#define D_FATAL 1
#define D_SUCCESS 4
#define D_INFO	5
#define D_DEBUG 6
#define D_TRACE 7

/*
** Functions to use for display log messages.
*/

#define log_fatal(...)		\
	logger_fatal(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_error(...)		\
	logger_error(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_warn(...)		\
	logger_warn(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_success(...)	\
	logger_success(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_info(...)		\
	logger_info(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_debug(...)		\
	logger_debug(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_trace(...)		\
	logger_trace(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

/*
** Setup the logger and write a sample message 'INFO' if success on the given
** log output (the log_file paramater).
** - The level parameter must be one of the define D_*. If it is not one of
** them, the define D_OFF will be used.
*/

int	logger_init(int level, char *log_file);


/*
Destroy the log file 
*/
int logger_destroy(void);

/*
** Display an 'INFO' message and close the file descriptor of the logger.
*/

int	logger_close(void);

#endif // TIMERAL_LOG_H

