#include <gtk/gtk.h>
#include "log.h"
#include "xorz.h"

GtkWidget *http,*https;
static void
select_file(GtkWidget *widget,
             gpointer   data)
{
     GtkWidget *dialog;
     dialog = gtk_file_chooser_dialog_new ("Open File",
     				      NULL,
     				      GTK_FILE_CHOOSER_ACTION_OPEN,
     				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
     				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
     				      NULL);
     
     if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
       {
         char *filename;
		
         filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		 gtk_label_set_text(GTK_LABEL(data), filename);
		 log_path = filename;
		 log_path = filename;
       }
     
     gtk_widget_destroy (dialog);	
}

static void
start_server(GtkWidget *widget,
             gpointer   data)
{
	char *xargv[]={(char *)gtk_entry_get_text(GTK_ENTRY(http)), (char *)gtk_entry_get_text(GTK_ENTRY(https)), log_path};
	g_print("Starting Server\nHttp port: %s\nHttps port: %s\nLogfile: %s\n", xargv[0],xargv[1],xargv[2]);

	log_file = log_open(xargv[2]);
	log_server("Start Liso server. Server is running. \n");
	xorz_server(strtol(xargv[0],NULL,0));
	
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window,*hbox, *label_file;
  GtkWidget *button;
  GtkWidget *label;
  GtkWidget *entry;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "XORZ WEB SERVER");
  gtk_window_set_resizable((GtkWindow*)window, FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /*container of inputs*/
  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
  /* Here we construct the container that is going pack our buttons */
  //grid = gtk_grid_new ();

  /* Pack the container in the window */
  //gtk_container_add (GTK_CONTAINER (window), grid);


    /* Create our first entry */
	
  http = gtk_entry_new();
  gtk_entry_set_placeholder_text((GtkEntry*)http, "HTTP PORT");
  gtk_box_pack_start(GTK_BOX(hbox),http,0,0,0);

  https = gtk_entry_new();
  gtk_entry_set_placeholder_text((GtkEntry*)https, "HTTPS PORT");
  gtk_box_pack_start(GTK_BOX(hbox),https,0,0,0);

  label = gtk_label_new("log: ");
  gtk_box_pack_start(GTK_BOX(hbox),label,0,0,0);
  
  label_file = gtk_label_new("... ");
  gtk_box_pack_start(GTK_BOX(hbox),label_file,0,0,0);
  gtk_label_set_line_wrap((GtkLabel*)label_file, TRUE);
  
  button = gtk_button_new_with_label ("Select");
  gtk_box_pack_start(GTK_BOX(hbox),button,0,0,0);
  g_signal_connect (button, "clicked", G_CALLBACK (select_file), label_file);

  button = gtk_button_new_with_label ("Start");
  gtk_box_pack_start(GTK_BOX(hbox),button,0,0,0);
  g_signal_connect (button, "clicked", G_CALLBACK (start_server), NULL);
  gtk_container_add (GTK_CONTAINER (window), hbox);

  
  
/*  gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 2, 1);*/
  /* Now that we are done packing our widgets, we show them all
   * in one go, by calling gtk_widget_show_all() on the window.
   * This call recursively calls gtk_widget_show() on all widgets
   * that are contained in the window, directly or indirectly.
   */
  gtk_widget_show_all (window);

}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}