#include <glib.h>
#include <gio/gio.h>

GFileOutputStream *log_file;

int xorz_server(int);

gboolean incoming_callback  (GSocketService *, GSocketConnection *, GObject *, gpointer);