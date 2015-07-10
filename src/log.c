/*




void Log(const char *format, ...)
{
	
}
*/

#include "log.h"
#include<strings.h>

GFileOutputStream * log_open(const char *path)
{
	GFile *file = g_file_new_for_path(path);
	GFileOutputStream *output=g_file_replace(
                file,NULL,FALSE,
                G_FILE_CREATE_NONE,
                NULL,NULL);
    g_object_unref(file);
	return output;
}

void log_server(const char *format, ...)
{

    time_t ltime;
    struct tm *Tm;

    ltime = time(NULL);
    Tm = localtime(&ltime);
	gchar *buf;
	
    buf = g_strdup_printf("[%04d%02d%02d %02d:%02d:%02d] ",
                 Tm->tm_year+1900,
                 Tm->tm_mon+1,
                 Tm->tm_mday,
                 Tm->tm_hour,
                 Tm->tm_min,
                 Tm->tm_sec
           );
	g_output_stream_write(G_OUTPUT_STREAM(log_file),
                buf,strlen(buf),NULL,NULL);
	g_free(buf);
	
	va_list ap;
    va_start(ap, format);
	buf=g_strdup_vprintf(format, ap);
	g_output_stream_write(G_OUTPUT_STREAM(log_file),
                buf,strlen(buf),NULL,NULL);
	g_free(buf);
}

void log_close()
{
	g_output_stream_close(G_OUTPUT_STREAM(log_file),NULL,NULL);
	g_object_unref(log_file);	
}