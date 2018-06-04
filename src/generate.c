#include "../headers/generate.h"

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define TEX_FILE "out/soa-p3.tex"
#define LATEX_COMMAND "/usr/bin/pdflatex"
#define LATEX_OUTPUT_DIRECTORY "-output-directory=out"
#define PDF_FILE "out/soa-p3.pdf"
#define EVINCE_COMMAND "/usr/bin/evince"

#define COLOR_TASK_1 "gray"
#define COLOR_TASK_2 "brown"
#define COLOR_TASK_3 "cyan"
#define COLOR_TASK_4 "lime"
#define COLOR_TASK_5 "orange"
#define COLOR_TASK_6 "teal"

void init_documentation(){
    printf("Generating tex\n");
    generate_full_document();
    printf("Generating pdf\n");
    generate_pdf();
    printf("Open pdf\n");
    open_pdf();
}

void generate_full_document(){
    printf("Creating LATEX/soa-p3.tex\n");
    FILE *fp;fp=fopen(TEX_FILE, "wt");

    printf("Generating body of tex\n");
    document_class(fp);
    fprintf(fp, "\n");
    packages_document(fp);
    fprintf(fp, "\n");
    init_document(fp);
    fprintf(fp, "\n");

    printf("Close soa-p3.tex\n");
    fclose(fp);
}

void document_class(FILE *fp){
    fprintf(fp, "\\documentclass{beamer}\n");
}

void packages_document(FILE *fp){
    fprintf(fp, "\\usepackage[utf8]{inputenc}\n");
    fprintf(fp, "\\usepackage{multirow}\n");
    fprintf(fp, "\\usepackage{colortbl}\n");
    fprintf(fp, "\\usepackage{xcolor}\n");
    fprintf(fp, "\\usepackage{color}\n");
}

void theme_document(FILE *fp){
    fprintf(fp, "\\usetheme{Madrid}\n");
}

void init_document(FILE *fp){
    generate_title(fp);
    fprintf(fp,"\n");
    fprintf(fp,"\\begin{document}\n");
    fprintf(fp,"\\frame{\\titlepage}\n");

    slice_algoritmos(fp);
    slide_schedulability(fp);
    if(0){ // ALL IN THE SAME SLICE

    }else{ // SEPARATE SLICE
        generate_slice_only_RM(fp);
    }
    
    fprintf(fp,"\\end{document}");
}

void generate_title(FILE *fp){
    fprintf(fp,"\\title {Proyecto 3: Scheduling en Tiempo Real}\n\n");

    fprintf(fp,"\\author[Rody, Mario, Jose, Javier] {Rody Campos Gonzalez \\and Mario Romero Sandoval \\and Jose Daniel Salazar Vargas \\and Javier Porras Valensuela}");
}

void begin_slice(FILE *fp, char *title){
    fprintf(fp, "\\begin{frame}\n");
    fprintf(fp, "\\frametitle{%s}\n",title);
}

void end_slice(FILE *fp){
    fprintf(fp, "\\end{frame}\n");
}


void slice_algoritmos(FILE *fp){
    begin_slice(fp,"Algoritmos");
    fprintf(fp, "\\begin{block}{RM: Rate Monotonic}\n");
    fprintf(fp, "Es un algoritmo de scheduling con prioridades estaticas, publicado por Liu y Layland en 1973. Su output indica una condicion \"Suficiente\" por lo tanto si dice que \"Si\" el conjunto de tareas es schedulable bajo RM de lo contrario, puede ser que el conjunto rechazado pueda ser schedulable");
    fprintf(fp, "\\end{block}\n");
    fprintf(fp, "\\begin{block}{EDF: Earliest Deadline First}\n");
    fprintf(fp, "Este es un algoritmo expropiativo, consiste cuando una tarea llega a cola de Ready se revisan las prioridades y si es necesarip expropia a la tarea que este usando la CPU en ese momento.");
    fprintf(fp, "\\end{block}\n");
	fprintf(fp, "\\begin{block}{LLF: Least Laxity First}\n");
	fprintf(fp, "Algoritmo que asigna prioridades según el Laxity de las tareas en la cola. Laxity está definido como $X_i = (d_i-a_i-C_i)$\n");
	fprintf(fp, "donde $C_i$ es tiempo de computación, $d_i$ es el deadline y $a_i$ es el tiempo de arribo\n");
    fprintf(fp, "");
    fprintf(fp, "\\end{block}\n");
    end_slice(fp);
}


void begin_table(FILE *fp, int total_columns){
    fprintf(fp,"\\begin{tabular}");

    fprintf(fp,"{");
    for(int i = 0; i<total_columns+1;i++){
        fprintf(fp,"c|");
    }
    fprintf(fp,"}\n");
}
void end_table(FILE *fp){
    fprintf(fp,"\\end{tabular}\n");
}

void generate_step_number(FILE *fp,int total_steps){
    fprintf(fp,"\\cline{2-%d}",total_steps+1);
    for(int i = 0; i<total_steps;i++){
        fprintf(fp,"& %d",i);
    }
    fprintf(fp,"\\\\ \n");
}

char *get_color_task(int id){
    switch(id){
        case 1: return COLOR_TASK_1; break;
        case 2: return COLOR_TASK_2; break;
        case 3: return COLOR_TASK_3; break;
        case 4: return COLOR_TASK_4; break;
        case 5: return COLOR_TASK_5; break;
        case 6: return COLOR_TASK_6; break;
    }
}

void generate_timeline_task(FILE *fp,int id,int period, int total_steps){
    fprintf(fp,"\\cline{1-%d}",total_steps+1);
    fprintf(fp,"t%d",id);
    const char* deadline = "*";
    for(int i = 0; i<total_steps;i++){
        const char* color = get_color_task(id);
        fprintf(fp,"& \\cellcolor{%s} %s", color, i%period==0? deadline: "");
    }
    fprintf(fp,"\\\\ \n");
}

void generate_slice_only_RM(FILE *fp){
    begin_slice(fp,"RM");

    int total_steps = 13;
    int total_task = 6;
    
    begin_table(fp,total_steps);
    generate_step_number(fp,total_steps);

    for(int t = 0; t < total_task; t++){
        generate_timeline_task(fp,t+1,t+1,total_steps);
    }
    fprintf(fp,"\\cline{1-%d}",total_steps+1);

    end_table(fp);
    end_slice(fp);
}

void slide_schedulability(FILE *fp) {
	fprintf(fp, "\\begin{frame}\n");
	fprintf(fp, "\\frametitle{Test de schedulability}\n");
	fprintf(fp, "\\begin{block}{RM: Rate Monotonic}\n");
	fprintf(fp, "$U = \\sum^n_{i=1}{\\frac{C_i}{T_i}\\leq n(2^{1/n}-1))}$\n\n");

	fprintf(fp, "Under Rate Monotonic, $U = 0.5 < 0.6$. This task set is executable|not sure if executable");//TODO: ADD SCHEDULABLE? UNDER EACH.

	fprintf(fp, "\\end{block}\n");
	fprintf(fp, "\\begin{block}{EDF and LLF}\n");
	fprintf(fp, "$U = \\sum^n_{i=1}{\\frac{C_i}{T_i}\\leq 1}$\n\n");

	fprintf(fp, "Under EDF or LLF $U=0.8 < 1.0$ This task set is executable|not executable");//TODO: ADD SCHEDULABLE? UNDER EACH.

	fprintf(fp, "\\end{block}\n");
	fprintf(fp, "\\end{frame}\n");
}


void generate_pdf(){
    pid_t pid;
    char *const argv[] = {LATEX_COMMAND,LATEX_OUTPUT_DIRECTORY,TEX_FILE, NULL};
//    char *const argv[] = {LATEX_OUTPUT_DIRECTORY,TEX_FILE, NULL};
    if ((pid = fork()) ==-1)
        perror("fork error");
    else if (pid == 0) {
        printf("Excecuting pdflatex to generate pdf\n");
        
        if (-1 == execve(LATEX_COMMAND, (char **)argv , NULL)) {
            perror("Error Ejecutando pdflatex");
        }
    }
}

// this is not working
void open_pdf(){
	char *symlinkpath = PDF_FILE;
	char actualpath [4096+1];
	char *ptr;

	ptr = realpath(symlinkpath, actualpath);
    pid_t pid;
    char *const argv[] = {EVINCE_COMMAND,actualpath, NULL};
	char *env[]={"DISPLAY=:0",NULL};
    if ((pid = fork()) ==-1)
        perror("fork error");
    else if (pid == 0) {
		sleep(2);
        if (-1 == execve(EVINCE_COMMAND, (char **)argv , env)) {
            perror("Error Ejecutando evince");
        }
    }
}