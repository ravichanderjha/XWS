#include "xorz.h"
#include "log.h"

int xorz_server(int http_port)
{
  /* initialize glib */
  log_server("hello\n");
  GError * error = NULL;

  /* create the new socketservice */
  GSocketService * service = g_socket_service_new ();

  /* connect to the port */
  g_socket_listener_add_inet_port ((GSocketListener*)service,
                                    http_port, /* your port goes here */
                                    NULL,
                                    &error);

  /* don't forget to check for errors */
  if (error != NULL)
  {
      g_error (error->message);
  }

  /* listen to the 'incoming' signal */
  g_signal_connect (service,
                    "incoming",
                    G_CALLBACK (incoming_callback),
                    log_file);

  /* start the socket service */
  g_socket_service_start (service);

  /* enter mainloop */
  g_print ("Waiting for client!\n");
  log_close();
  return 0;
}

gboolean
incoming_callback  (GSocketService *service,
                    GSocketConnection *connection,
                    GObject *source_object,
                    gpointer user_data)
{
	
  GSocketAddress *sockaddr = g_socket_connection_get_remote_address(connection, NULL);
  GInetAddress *addr = g_inet_socket_address_get_address(G_INET_SOCKET_ADDRESS(sockaddr));
  guint16 port = g_inet_socket_address_get_port(G_INET_SOCKET_ADDRESS(sockaddr));

  //log_server("New Connection from %s:%d\n", g_inet_address_to_string(addr), port);
  log_server("accept client: client_fd\n");

  //g_print("Received Connection from client!\n");
  GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));
  GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));

  gchar message[1024];
  g_input_stream_read  (istream,
                        message,
                        1024,
                        NULL,
                        NULL);
  g_print("Message was: \"%s\"\n", message);
	g_output_stream_write (ostream, "hello", 6, NULL, NULL);
  return FALSE;
}
