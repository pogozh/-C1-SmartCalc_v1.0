#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWindow *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("./UI/ui.glade");

    window = GTK_WINDOW(gtk_builder_get_object(builder, "gtk_window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    return 0;
}