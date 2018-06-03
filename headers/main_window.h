//
// Created by mario on 31/05/18.
//

#ifndef PROJECT3_MAIN_WINDOW_H
#define PROJECT3_MAIN_WINDOW_H

#include <gtk/gtk.h>

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}


static void initialize_window(GtkWidget *window) {
    gtk_window_set_title(GTK_WINDOW(window), "My Window"); //Set window title
    gtk_window_set_default_size(GTK_WINDOW (window), 400, 200); //Set default size for the window
    g_signal_connect (window, "destroy", G_CALLBACK(destroy), NULL); //End application when close button clicked

}

static void button_clicked(GtkWidget *widget, gpointer data) {

    g_print("clicked\n");
}


enum {
    LIST_ID,
    LIST_BRAND,
    LIST_PRICE,
    N_COLUMNS
};

static void create_list_view(GtkCellRenderer *renderer, GtkTreeViewColumn *column, GtkListStore **store, GtkWidget **list);

static void lunch_window(int argc, char **argv) {
    GtkWidget *window, *grid;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkWidget *list;

    GtkWidget *vbox;
    GtkWidget *label;
    GtkTreeSelection *selection;

    gtk_init(&argc, &argv);

    //Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    initialize_window(window);


    /* Create a 1x2 grid */
    // grid = gtk_table_new (1, 2, TRUE);
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER (window), grid);


    GtkWidget *child1 = gtk_label_new("Task Period");
    gtk_grid_attach(GTK_GRID (grid), child1, 0, 0, 1, 1);
    GtkWidget *child2 = gtk_entry_new();
    gtk_grid_attach_next_to(GTK_GRID (grid), child2, child1, GTK_POS_RIGHT, 1, 1);

    GtkWidget *child3 = gtk_label_new("Task execution time:");
    gtk_grid_attach(GTK_GRID (grid), child3, 3, 0, 1, 1);
    GtkWidget *child4 = gtk_entry_new();
    gtk_grid_attach_next_to(GTK_GRID (grid), child4, child3, GTK_POS_RIGHT, 1, 1);

    GtkWidget *child5 = gtk_label_new("Task priority:");
    gtk_grid_attach(GTK_GRID (grid), child5, 5, 0, 1, 1);
    GtkWidget *child6 = gtk_entry_new();
    gtk_grid_attach_next_to(GTK_GRID (grid), child6, child5, GTK_POS_RIGHT, 1, 1);

    GtkWidget *child7 = gtk_button_new_with_label("Add");
    gtk_grid_attach(GTK_GRID (grid), child7, 7, 0, 1, 1);

    g_signal_connect(G_OBJECT(child7), "clicked", G_CALLBACK(button_clicked), NULL);

    create_list_view(renderer, column, &store, &list);

    gtk_grid_attach(GTK_GRID (grid), list, 3, 1, 1, 1);

//
//    vbox = gtk_box_new(FALSE, 0);
//
//    gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);
//
//    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkTreeIter iter;

    gtk_list_store_append(GTK_LIST_STORE(store), &iter);
    gtk_list_store_set(GTK_LIST_STORE(store), &iter,
                       LIST_ID, "Period:",
                       LIST_BRAND, "Execution time:",
                       LIST_PRICE, "Priority:",
                       -1);

    gtk_list_store_append(GTK_LIST_STORE(store), &iter);
    gtk_list_store_set(GTK_LIST_STORE(store), &iter,
                       LIST_ID, "1:",
                       LIST_BRAND, "2:",
                       LIST_PRICE, "2:",
                       -1);


    gtk_widget_show_all(window);

    gtk_main();
}

static void create_list_view(GtkCellRenderer *renderer, GtkTreeViewColumn *column, GtkListStore **store, GtkWidget **list) {
    (*store) = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    (*list) = gtk_tree_view_new();

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID",
                                                      renderer, "text", LIST_ID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW((*list)), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("BRAND",
                                                      renderer, "text", LIST_BRAND, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW((*list)), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("PRICE",
                                                      renderer, "text", LIST_PRICE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW((*list)), column);

    gtk_tree_view_set_model(GTK_TREE_VIEW((*list)), GTK_TREE_MODEL((*store)));

    g_object_unref((*store));

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW((*list)), FALSE);
}

#endif //PROJECT3_MAIN_WINDOW_H
