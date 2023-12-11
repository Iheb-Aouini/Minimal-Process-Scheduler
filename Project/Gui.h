#ifndef GUI_FUNCTIONS_H
#define GUI_FUNCTIONS_H

#include <gtk/gtk.h>
#include "Process.h"

// Function declarations
void populate_table(GtkListStore *list_store, struct Process_array process_array);

void on_destroy(GtkWidget *widget, gpointer data);

void open_gtk_IHM(struct Process_array process_array,char label_message[150]);

#endif
