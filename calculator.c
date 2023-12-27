#include <gtk/gtk.h>

// Function declarations
void on_button_click(GtkWidget *widget, gpointer data);
void on_clear_button_click(GtkWidget *widget, gpointer data);

// Global variables
GtkWidget *entry;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simple Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create the entry widget
    entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_entry_set_max_length(GTK_ENTRY(entry), 20);
    gtk_entry_set_editable(GTK_ENTRY(entry), FALSE);
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 20);
    gtk_container_add(GTK_CONTAINER(window), entry);

    // Create a grid to hold the buttons
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Button labels
    gchar *button_labels[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };

    // Attach buttons to the grid
    for (int i = 0; i < 16; i++) {
        GtkWidget *button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, i / 4, 1, 1);
        g_signal_connect(button, "clicked", G_CALLBACK(on_button_click), entry);
    }

    // Clear button
    GtkWidget *clear_button = gtk_button_new_with_label("C");
    gtk_grid_attach(GTK_GRID(grid), clear_button, 3, 4, 1, 1);
    g_signal_connect(clear_button, "clicked", G_CALLBACK(on_clear_button_click), entry);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

// Callback function for numeric and operator buttons
void on_button_click(GtkWidget *widget, gpointer data) {
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON(widget));
    const gchar *current_text = gtk_entry_get_text(GTK_ENTRY(data));

    gchar *new_text = g_strconcat(current_text, button_label, NULL);
    gtk_entry_set_text(GTK_ENTRY(data), new_text);
    g_free(new_text);
}

// Callback function for the clear button
void on_clear_button_click(GtkWidget *widget, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(data), "");
}
