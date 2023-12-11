#include "../Gui.h"




static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // Cast data back to Process_array
    struct Process_array *process_array = (struct Process_array *)data;

    // Set the starting position for the Gantt chart
    int x = 50;
    int y = 200;
    int bar_height = 60;
    int bar_width_factor = 30;

    int start_time, finish_time;

    // Draw Gantt chart for each process
    for (int i = 0; i < process_array->size; ++i) {
        // Calculate the width of the bar based on Burst_time
        int bar_width = process_array->proc[i].Burst_time * bar_width_factor;

        // Set a color for the Gantt chart bar
        cairo_set_source_rgb(cr, 0.2, 0.4, 0.6); // Blue color
        cairo_rectangle(cr, x, y, bar_width, bar_height);
        cairo_fill(cr);

        // Set color for text
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);

        // Set font size and draw process name
        cairo_set_font_size(cr, 14); // Increase font size
        cairo_move_to(cr, x + 5, y + 20);
        cairo_show_text(cr, process_array->proc[i].Name);

        // Calculate and display start and finish times
        if (i == 0) {
            start_time = process_array->proc[i].Arrival_time;
            finish_time = process_array->proc[i].Response_time;
        } else {
            start_time = process_array->proc[i - 1].Response_time;
            finish_time = process_array->proc[i].Response_time;
        }

        // Display start time
        cairo_move_to(cr, x + 5, y + 35);
        cairo_show_text(cr, g_strdup_printf("Start: %d", start_time));

        // Display finish time
        cairo_move_to(cr, x + 5, y + 50);
        cairo_show_text(cr, g_strdup_printf("Finish: %d", finish_time));

        // Update the position for the next bar
        x += bar_width + 15; // Increase space between bars
    }

    return FALSE;
}







// Function to populate the GtkListStore with data from the process array
void populate_table(GtkListStore *list_store, struct Process_array process_array) {
    for (int i = 0; i < process_array.size; ++i) {
        GtkTreeIter iter;
        gtk_list_store_append(list_store, &iter);
        gtk_list_store_set(list_store, &iter,
                           0, process_array.proc[i].Name,
                           1, process_array.proc[i].Arrival_time,
                           2, process_array.proc[i].Burst_time,
                           3, process_array.proc[i].Priority,
                           4, process_array.proc[i].pid,
                           5, process_array.proc[i].Waiting_time,
                           6, process_array.proc[i].Response_time,
                           -1);
    }
}

// Callback function to handle the destroy event
void on_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}







void open_gtk_IHM(struct Process_array process_array,char label_message[150]) {
    
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Process Table");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);

     //create the label

     GtkWidget *label = gtk_label_new(label_message);
    gtk_label_set_xalign(GTK_LABEL(label), 0.5); // Center the label horizontally
    gtk_label_set_use_markup(GTK_LABEL(label), TRUE);   

    // Create the list store
    GtkListStore *list_store = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT,
                                                  G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);

    // Create the tree view
    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));

    // Create the columns with titles
    const char *column_titles[] = {"Name", "Arrival Time", "Burst Time", "Priority","PID","Waiting Time","Response Time"};

    for (int i = 0; i < 7; ++i) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(column_titles[i], renderer, "text", i, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    }

    // Create a scrolled window to contain the tree view
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);

    // Set up the main grid layout
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

   
    // Add the label to the grid
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

     // Add the scrolled window to the grid and expand it
    gtk_grid_attach_next_to(GTK_GRID(grid), scrolled_window, label, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    gtk_widget_set_hexpand(scrolled_window, TRUE);


        // Create the drawing area for the Gantt chart
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 600, 100);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), &process_array);


       



    // Add the drawing area to the grid and expand it
    gtk_grid_attach_next_to(GTK_GRID(grid), drawing_area, scrolled_window, GTK_POS_BOTTOM, 1, 1);
    gtk_widget_set_vexpand(drawing_area, TRUE);
    gtk_widget_set_hexpand(drawing_area, TRUE);





    // Your process array data
    //struct Process_array process_array = extract_process_list("processes_list.txt");

    // Populate the table with data
    populate_table(list_store, process_array);


    

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

}
