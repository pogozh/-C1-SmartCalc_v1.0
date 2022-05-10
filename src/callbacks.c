#include <gtk/gtk.h>

#include "calc.h"
#include "pars.h"
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

void oncalculate(GtkButton* button, gpointer gtk_window) {
    GtkEntry* entry = find_child(gtk_window, "entry_exp");
    gchar input[256];
    g_print("%s\n", gtk_entry_get_text(entry));
    g_snprintf(input, sizeof(input), "%s", gtk_entry_get_text(entry));
    que* qu;
    GtkEntry* entry_x = find_child(gtk_window, "entry_x");
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
    };
    UNUSED(button);
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
