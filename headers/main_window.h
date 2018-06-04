//
// Created by mario on 31/05/18.
//

#ifndef PROJECT3_MAIN_WINDOW_H
#define PROJECT3_MAIN_WINDOW_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <memory.h>
#include "task_set.h"
#include "scheduler.h"
#include "generate.h"

enum {
    LIST_TASK_PERIOD,
    LIST_TASK_EXECUTION_TIME,
    //LIST_TASK_PRIORITY,
            N_COLUMNS
};

typedef struct add_btn_click_data {

    GtkListStore *store;

    GtkWidget *period;
    GtkWidget *excec_time;

    GtkWidget *feedback_text;
} add_click_data;

typedef struct run_btn_click_data {

    GtkListStore *store;

    GtkWidget *runRM;
    GtkWidget *runEDF;
    GtkWidget *runLLF;

    GtkWidget *combo;

    GtkWidget *feedback_text;

} run_click_data;

static bool validate_only_numbers(const gchar *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (str[i] < 48 || str[i] > 57)
            return 1;
    }
    return 0;
}

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}


static void set_window(GtkWidget *window) {
    gtk_window_set_title(GTK_WINDOW(window), "Project 3"); //Set window title
    gtk_window_set_default_size(GTK_WINDOW (window), 400, 200); //Set default size for the window
    g_signal_connect (window, "destroy", G_CALLBACK(destroy), NULL); //End application when close button clicked

}


static void add_btn_clicked(GtkWidget *widget, gpointer data) {

    gtk_label_set_text(((add_click_data *) data)->feedback_text, "");
    GtkTreeIter iter;

    const gchar *period_str = gtk_entry_get_text((GtkEntry *) ((add_click_data *) data)->period);
    const gchar *excec_time_str = gtk_entry_get_text((GtkEntry *) ((add_click_data *) data)->excec_time);

    if (validate_only_numbers(period_str) ||
        validate_only_numbers(excec_time_str)) {
        gtk_label_set_text(((add_click_data *) data)->feedback_text, "Period and exec time should be numbers ONLY!");
        return;
    }

    gtk_list_store_append(GTK_LIST_STORE(((add_click_data *) data)->store), &iter);
    gtk_list_store_set(GTK_LIST_STORE(((add_click_data *) data)->store), &iter,
                       LIST_TASK_PERIOD, period_str,
                       LIST_TASK_EXECUTION_TIME, excec_time_str,
                       -1);


}


static void run_btn_clicked(GtkWidget *widget, gpointer data) {

    gtk_label_set_text(((run_click_data *) data)->feedback_text, "");

    GtkListStore *list = ((run_click_data *) data)->store;
    GtkCheckButton *to_run_edf = (GtkCheckButton *) ((run_click_data *) data)->runEDF;
    GtkCheckButton *to_run_rm = (GtkCheckButton *) ((run_click_data *) data)->runRM;
    GtkCheckButton *to_run_llf = (GtkCheckButton *) ((run_click_data *) data)->runLLF;


    GtkComboBox *mode = (GtkComboBox *) ((run_click_data *) data)->combo;

    GtkTreeIter iter;

    int size = 0;

    gboolean out = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list), &iter);

    while (out) {
        size++;
        out = gtk_tree_model_iter_next(GTK_TREE_MODEL(list), &iter);
    }

    if (size == 0) {
        gtk_label_set_text(((run_click_data *) data)->feedback_text, "There should be at least one task selected!");
    }

    out = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list), &iter);
    task_set set;
    set.tasks = calloc(size, sizeof(task));
    set.size = size;

    int it = 0;
    while (out) {
        gchar *period_str, *priority_str, *exec_time_str;
        gtk_tree_model_get(GTK_TREE_MODEL(list), &iter,
                           LIST_TASK_PERIOD, &period_str,
                           LIST_TASK_EXECUTION_TIME, &exec_time_str,
                           -1);

        int period = atoi(period_str);
        int exec_time = atoi(exec_time_str);

        set.tasks[it].id = it + 1;
        set.tasks[it].e = exec_time;
        set.tasks[it].p = period;

        it++;

        out = gtk_tree_model_iter_next(GTK_TREE_MODEL(list), &iter);
    }

    set.is_rm = gtk_toggle_button_get_active(&(to_run_rm->toggle_button));
    set.is_edf = gtk_toggle_button_get_active(&(to_run_edf->toggle_button));
    set.is_llf = gtk_toggle_button_get_active(&(to_run_llf->toggle_button));


    if (!(set.is_rm || set.is_edf || set.is_llf)) {
        gtk_label_set_text(((run_click_data *) data)->feedback_text, "There must be at least one algorithm selected!");
        return;
    }

    int single_slide = gtk_combo_box_get_active(mode) == 0;

    results res = schedule(&set);

    res.all_same_sile = single_slide;

    init_documentation(&res);
}


static void
create_list_view(GtkCellRenderer *renderer, GtkTreeViewColumn *column, GtkListStore **store, GtkWidget **list);


static void init(int argc, char **argv) {
    GtkWidget *window, *grid;
    GtkCellRenderer *renderer;

    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkWidget *list;

    gtk_init(&argc, &argv);

    //Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    set_window(window);


    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER (window), grid);


    GtkWidget *child1 = gtk_label_new("Task Period");
    gtk_grid_attach(GTK_GRID (grid), child1, 0, 0, 1, 1);
    GtkWidget *period_entry = gtk_entry_new();

    gtk_grid_attach_next_to(GTK_GRID (grid), period_entry, child1, GTK_POS_RIGHT, 1, 1);

    GtkWidget *child3 = gtk_label_new("Task execution time:");
    gtk_grid_attach(GTK_GRID (grid), child3, 0, 1, 1, 1);
    GtkWidget *exec_time_entry = gtk_entry_new();
    gtk_grid_attach_next_to(GTK_GRID (grid), exec_time_entry, child3, GTK_POS_RIGHT, 1, 1);

    GtkWidget *add_btn = gtk_button_new_with_label("Add");
    gtk_grid_attach(GTK_GRID (grid), add_btn, 1, 3, 1, 1);

    GtkWidget *checkRM = gtk_check_button_new_with_label("Run RM");
    GtkWidget *checkEDF = gtk_check_button_new_with_label("Run EDF");
    GtkWidget *checkLLF = gtk_check_button_new_with_label("Run LLF");

    gtk_grid_attach(GTK_GRID (grid), checkRM, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID (grid), checkEDF, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID (grid), checkLLF, 0, 5, 1, 1);

    GtkWidget *combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combo), "One slide");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT (combo), "Multiple slides");

    gtk_combo_box_set_active(GTK_COMBO_BOX (combo), 0);

    gtk_grid_attach(GTK_GRID (grid), combo, 1, 5, 1, 1);


    create_list_view(renderer, column, &store, &list);

    gtk_grid_attach(GTK_GRID (grid), list, 3, 0, 5, 7);

    GtkWidget *run_btn = gtk_button_new_with_label("RUN!");
    gtk_grid_attach(GTK_GRID (grid), run_btn, 0, 6, 3, 1);

    GtkWidget *feedback = gtk_label_new("Task Period");
    gtk_grid_attach(GTK_GRID (grid), feedback, 0, 7, 8, 1);

    add_click_data *add_data = (add_click_data *) malloc(sizeof(add_click_data));

    add_data->store = store;

    add_data->excec_time = exec_time_entry;
    add_data->period = period_entry;


    add_data->feedback_text = feedback;

    g_signal_connect(G_OBJECT(add_btn), "clicked", G_CALLBACK(add_btn_clicked), add_data);


    run_click_data *run_data = (run_click_data *) malloc(sizeof(run_click_data));

    run_data->store = store;
    run_data->runRM = checkRM;
    run_data->runEDF = checkEDF;
    run_data->runLLF = checkLLF;
    run_data->combo = combo;
    run_data->feedback_text = feedback;


    g_signal_connect(G_OBJECT(run_btn), "clicked", G_CALLBACK(run_btn_clicked), run_data);


    gtk_widget_show_all(window);

    gtk_main();
}

static void
create_list_view(GtkCellRenderer *renderer, GtkTreeViewColumn *column, GtkListStore **store, GtkWidget **list) {

    (*store) = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);
    (*list) = gtk_tree_view_new();

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("PERIOD", renderer, "text", LIST_TASK_PERIOD, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW((*list)), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("EXECUTION_TIME", renderer, "text", LIST_TASK_EXECUTION_TIME,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW((*list)), column);

    gtk_tree_view_set_model(GTK_TREE_VIEW((*list)), GTK_TREE_MODEL((*store)));

    g_object_unref((*store));

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW((*list)), TRUE);
}

#endif //PROJECT3_MAIN_WINDOW_H
