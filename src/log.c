#include "include/log.h"

int	logger_init(int level, char *log_file) {
	int	ret;
	if ((ret = logger_init_open_file(log_file)) < 0)
		return ret;
	g_log_lvl = D_OFF;
	if (level >= D_FATAL && level <= D_TRACE) {
		g_log_lvl = level;
	}
	return (0);
}

int	logger_close(void) {
	return (close(g_log_fd));
}


void logger_debug(int fd, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	if (g_log_lvl < D_DEBUG)
		return ;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [DEBUG] %-20.20s -- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	dprintf(fd, "\033[0m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_info(int fd, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	if (g_log_lvl < D_INFO)
		return ;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [INFO] %-20.20s -- ", \
			time, line, f);
	free(f);


	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	dprintf(fd, "\033[36m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_error(int fd, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	if (g_log_lvl < D_ERROR)
		return ;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [ERROR] %-20.20s -- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	dprintf(fd, "\033[31m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_fatal(int fd, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	if (g_log_lvl < D_FATAL)
		return ;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [FATAL] %-20.20s -- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	dprintf(fd, "\033[31m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_success(int fd, char *file, int line, const char *fmt, ...)
{
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	if (g_log_lvl < D_WARN)
		return ;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [SUCCESS] %-20.20s -- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	dprintf(fd, "\033[32m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_trace(int fd, char *file, int line, const char *fmt, ...)
{
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	if (g_log_lvl < D_TRACE)
		return ;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [TRACE] %-20.20s -- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	dprintf(fd, "\033[38;5;239m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_warn(int fd, char *file, int line, const char *fmt, ...)
{
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	if (g_log_lvl < D_WARN)
		return ;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [WARN] %-20.20s -- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	dprintf(fd, "\033[31m\033[1;33m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

char *logger_get_time(void)
{
	time_t tm;
	char *buf;
	struct tm *tm_info;

	if (!(buf = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	tm = time(NULL);
	tm_info = localtime(&tm);
	strftime(buf, 9, "%H:%M:%S", tm_info);
	return (buf);
}

int	logger_init_open_file(char *log_file) {
	if (log_file == NULL)
		g_log_fd = -1;
	g_log_fd = open(log_file, O_WRONLY | O_APPEND | O_CREAT, 0755);
	return (g_log_fd);
}

int	logger_destroy(void) {
	return remove(F_DEST);
}