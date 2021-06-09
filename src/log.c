#include "include/log.h"

int logger_init(char *filename) {
    if (fp != NULL)
        return 1;
    fp = fopen(filename, "a");

    if (fp == NULL) {
        fprintf(stderr, "File cannot be opened.\n");
        return 1;
    }
    return 0;
}   

int logger_close(void) {
    if (fp == NULL)
        return 1;
    return fclose(fp);
}

void logger_error(FILE *fp, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [ERROR  ] %-20.20s --- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	fprintf(fp, "\033[31m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_fatal(FILE *fp, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [FATAL  ] %-20.20s --- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	fprintf(fp, "\033[31m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_debug(FILE *fp, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [DEBUG  ] %-20.20s --- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	fprintf(fp, "\033[0m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_info(FILE *fp, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [INFO   ] %-20.20s --- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	fprintf(fp, "\033[36m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_success(FILE *fp, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [SUCCESS] %-20.20s --- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	fprintf(fp, "\033[32m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_trace(FILE *fp, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [TRACE  ] %-20.20s --- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	fprintf(fp, "\033[38;5;239m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

void logger_warn(FILE *fp, char *file, int line, const char *fmt, ...) {
	va_list	lst;
	char *time;
	char *out_info;
	char *out_mesg;
	char *f;

	f = NULL;
	if (strlen(file) >= 20) {
		f = strdup(file + (strlen(file) - 20));
		f[0] = '+';
	
	}
	else
		f = strdup(file);
	time = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) [WARN   ] %-20.20s --- ", \
			time, line, f);
	free(f);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	fprintf(fp, "\033[31m\033[1;33m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time);
}

char *logger_get_time(void) {
    time_t tm;
	char *buf;
	struct tm *tm_info;

	if (!(buf = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	tm = time(NULL);
	tm_info = localtime(&tm);
	strftime(buf, 9, "%H:%M:%S", tm_info);
	return buf;
}