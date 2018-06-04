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
    if(1){ // ALL IN THE SAME SLICE

    }else{ // SEPARATE SLICE

    }
    
    fprintf(fp,"\\end{document}");
}

void generate_title(FILE *fp){
    fprintf(fp,"\\title {Proyecto 3: Scheduling en Tiempo Real}\n\n");

    fprintf(fp,"\\author[Rody, Mario, Jose, Javier] {Rody Campos Gonzalez \\and Mario Romero Sandoval \\and Jose Daniel Salazar Vargas \\and Javier Porras Valensuela}");
}


void slice_algoritmos(FILE *fp){
    fprintf(fp, "\\begin{frame}\n");
    fprintf(fp, "\\frametitle{Algoritmos}\n");
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