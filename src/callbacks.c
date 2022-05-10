#include <gtk/gtk.h>
#include <locale.h>

#include "calc.h"
#include "pars.h"
#include "simple_grapher/grapher.h"

#define UNUSED(expr) (void)(expr)

static inline GtkWidget* find_child(GtkWidget* parent, const gchar* name) {
    if (strcmp(gtk_widget_get_name(parent), name) == 0) return parent;

    GList* children = NULL;
    if (GTK_IS_CONTAINER(parent))
        children = gtk_container_get_children(GTK_CONTAINER(parent));

    while (children != NULL) {
        GtkWidget* widget = find_child(GTK_WIDGET(children->data), name);

        if (widget != NULL) return widget;

        children = children->next;
    }

    return NULL;
}

void to_locale_decimal_point(char* string) {
    char cur_delim = ',';
    char new_delim = '.';
    if (*localeconv()->decimal_point == ',') {
        cur_delim = '.';
        new_delim = ',';
    }
    for (size_t i = 0; i < strlen(string); ++i) {
        if (string[i] == cur_delim) {
            string[i] = new_delim;
        }
    }
}

void oncalculate(GtkButton* button, gpointer gtk_window) {
    GtkEntry* entry = GTK_ENTRY(find_child(gtk_window, "entry_exp"));
    gchar input[256];
    g_print("%s\n", gtk_entry_get_text(entry));
    g_snprintf(input, sizeof(input), "%s", gtk_entry_get_text(entry));
    que* qu;
    GtkEntry* entry_x = GTK_ENTRY(find_child(gtk_window, "entry_x"));
    gchar input_x[101];
    g_snprintf(input_x, sizeof(input), "%s", gtk_entry_get_text(entry_x));
    double input_x_d = strtod(input_x, NULL);
    if (str_to_polish(input, &qu)) {
        double result = calculate(qu, input_x_d);
        gchar expression[256];
        g_snprintf(expression, sizeof(expression), "%.9f", result);
        gtk_entry_buffer_set_text(gtk_entry_get_buffer(entry), expression,
                                  strlen(expression));
        g_print("%.9f\n", result);
        gtk_editable_set_position(
            GTK_EDITABLE(entry),
            gtk_editable_get_position(GTK_EDITABLE(entry)) + 50);
    }
    UNUSED(button);
}

void on_plote_window_close(GtkWidget* widget, gpointer main_window) {
    UNUSED(widget);
    gtk_widget_set_sensitive(GTK_WIDGET(main_window), TRUE);
}

void onPlote(GtkButton* b, gpointer main_window) {
    UNUSED(b);
    /* builder init */
    GtkBuilder* builder;
    GtkWindow* window;

    builder = gtk_builder_new_from_file("./UI/plotter.glade");

    /* get window object from the builder */
    window = GTK_WINDOW(gtk_builder_get_object(builder, "id@gtk_window"));

    /* enable all signals from builder */
    gtk_builder_connect_signals(builder, NULL);

    /* disable main window */
    gtk_widget_set_sensitive(GTK_WIDGET(main_window), FALSE);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(on_plote_window_close), main_window);

    /* show window */
    gtk_widget_show_all(GTK_WIDGET(window));
}

void onsqrt(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "sqrt()", 6,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 5);
}

void onmod(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "mod", 3,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 3);
}

void onlog(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "log()", 5,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 4);
}

void onln(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "ln()", 4,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 3);
}
void onpow(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "^", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void ontan(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "tan()", 5,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 4);
}

void onatan(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "atan()", 6,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 5);
}

void onsin(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "sin()", 5,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 4);
}

void onasin(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "asin()", 6,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 5);
}

void oncos(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "cos()", 5,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 4);
}

void onacos(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "acos()", 6,
                             &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 5);
}

void onopenbr(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "(", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void onclosebr(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), ")", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on1(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "1", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on2(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "2", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on3(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "3", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on4(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "4", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on5(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "5", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on6(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "6", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void onseven(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "7", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void oneight(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "8", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on9(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "9", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void on0(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "0", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void ondot(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), ".", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void onplus(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "+", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void onminus(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "-", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void ondef(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "/", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void onmul(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gint cursor_position = gtk_editable_get_position(GTK_EDITABLE(io_field));
    gtk_editable_insert_text(GTK_EDITABLE(io_field), "*", 1, &cursor_position);
    gtk_editable_set_position(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) + 1);
}

void oncls(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gtk_editable_delete_text(GTK_EDITABLE(io_field), 0,
                             gtk_entry_get_max_length(GTK_ENTRY(io_field)));
}

void ondel(GtkButton* b, gpointer io_field) {
    UNUSED(b);
    gtk_editable_delete_text(
        GTK_EDITABLE(io_field),
        gtk_editable_get_position(GTK_EDITABLE(io_field)) - 1,
        gtk_editable_get_position(GTK_EDITABLE(io_field)));
}

extern double* x;
extern double* y;
extern int count_of_dots;

void on_plotter_window_close(GtkWidget* widget, gpointer main_window) {
    UNUSED(widget);
    gtk_widget_set_sensitive(GTK_WIDGET(main_window), TRUE);
    gtk_widget_show(main_window);
}

void on_plote_graph(GtkButton* b, GtkGrid* plotter_window) {
    UNUSED(b);
    double x_max;
    double x_min;
    double y_max;
    double y_min;
    char* endptr;
    GtkWidget* widget;
    char str[256];

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_xmin");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    to_locale_decimal_point(str);
    x_min = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
    }

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_xmax");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    to_locale_decimal_point(str);
    x_max = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
    }

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_ymin");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    to_locale_decimal_point(str);
    y_min = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
    }

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_ymax");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));
    to_locale_decimal_point(str);
    y_max = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') {
        gtk_entry_set_text(GTK_ENTRY(widget), "error");
        return;
    }

    widget = find_child(GTK_WIDGET(plotter_window), "id@gtk_entry");
    g_snprintf(str, sizeof(str), "%s", gtk_entry_get_text(GTK_ENTRY(widget)));

    que* qu;

    linspace(x, x_min, x_max, count_of_dots);

    if (str_to_polish(str, &qu) == true) {
        for (int i = 0; i < count_of_dots; ++i) {
            y[i] = calculate(qu, x[i]);
        }
        plotter_set_domain(y_min, y_max);
        plotter_set_range(x_min, x_max);
        plotter_set_function(x, y, count_of_dots);
        gtk_widget_set_sensitive(GTK_WIDGET(plotter_window), FALSE);
        gtk_widget_hide(GTK_WIDGET(plotter_window));
        plotter_draw();
        plotter_signal_connect_on_close(on_plotter_window_close,
                                        (gpointer)plotter_window);
    } else {
        gtk_entry_buffer_set_text(gtk_entry_get_buffer(GTK_ENTRY(widget)),
                                  "ERROR", 6);
    }
    queue_free(qu);
}
