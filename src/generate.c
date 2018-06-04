#include "../headers/generate.h"

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define TEX_FILE "out/soa-p3.tex"
#define LATEX_COMMAND "/usr/bin/pdflatex"
#define LATEX_OUTPUT_DIRECTORY "-output-directory=out"

void init_documentation(){
    printf("Generating tex\n");
    generate_full_document();
    printf("Generating pdf\n");
    generate_pdf();
}

void generate_full_document(){
    printf("Creating LATEX/soa-p3.tex\n");
    FILE *fp;fp=fopen(TEX_FILE, "wt");

    printf("Generating body of tex\n");
    type_document(fp);
    fprintf(fp, "\n");
    packages_document(fp);
    fprintf(fp, "\n");
    init_document(fp);
    fprintf(fp, "\n");

    printf("Close soa-p3.tex\n");
    fclose(fp);
}

void type_document(FILE *fp){
    fprintf(fp, "\\documentclass{beamer}\n");
}

void packages_document(FILE *fp){
    fprintf(fp, "\\usepackage[utf8]{inputenc}\n");
}

void init_document(FILE *fp){
    generate_title(fp);
    fprintf(fp,"\n");
    fprintf(fp,"\\begin{document}\n");
    fprintf(fp,"\\frame{\\titlepage}\n");
    slice_1(fp);
    fprintf(fp,"\\end{document}");
}

void generate_title(FILE *fp){
    fprintf(fp,"\\title {Proyecto 3: Scheduling en Tiempo Real}\n\n");

    fprintf(fp,"\\author[Rody, Mario, Jose, Javier] {Rody Campos Gonzalez \\and Mario Romero Sandoval \\and Jose Daniel Salazar Vargas \\and Javier Porras Valensuela}");
}


void slice_1(FILE *fp){

}

void generate_pdf(){
    pid_t pid;
    char *const argv[] = {LATEX_COMMAND, LATEX_OUTPUT_DIRECTORY,TEX_FILE, NULL};
    if ((pid = fork()) ==-1)
        perror("fork error");
    else if (pid == 0) {
        printf("Excecuting pdflatex to generate pdf\n");
        
        if (-1 == execve(argv[0], (char **)argv , NULL)) {
            perror("Error Ejecutando pdflatex");
        }
    }
}