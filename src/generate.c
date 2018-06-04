#include "../headers/generate.h"

#include <sys/types.h>
#include <unistd.h>

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

void init_documentation(results* res){
    printf("Generating tex\n");
    generate_full_document(res);
    printf("Generating pdf\n");
    generate_pdf();
    printf("Open pdf\n");
    open_pdf();
}

void generate_full_document(results* res){
    printf("Creating out/soa-p3.tex\n");
    FILE *fp;
    fp=fopen(TEX_FILE, "wt");

    printf("Generating body of tex\n");
    document_class(fp);
    fprintf(fp, "\n");
    packages_document(fp);
    theme_document(fp);
    fprintf(fp, "\n");
    init_document(fp, res);
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

void init_document(FILE *fp, results* res){
    printf("Test");
    generate_title(fp);
    printf("Test");
    fprintf(fp,"\n");
    fprintf(fp,"\\begin{document}\n");
    fprintf(fp,"\\frame{\\titlepage}\n");


    slice_algoritmos(fp);
    slide_schedulability(fp,res);
    if(res->all_same_sile){ // ALL IN THE SAME SLICE
 
    }else{ // SEPARATE SLICE
        generate_slide_single_algorithm(fp,"RM", res->rm_result);
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

void generate_step_number(FILE *fp,scheduler_result result){
    fprintf(fp,"\\cline{2-%d}",result.fix_length+1+1);
    for(int i = 0; i<result.fix_length+1;i++){
        if(i==0)
            fprintf(fp,"& %d",0);
        else
            fprintf(fp,"& %d",result.simulation[i].time);
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

void generate_timeline_task(FILE *fp,scheduler_result result,int actual_task, int actual_step,int total_steps){
    fprintf(fp,"\\cline{1-%d}",total_steps+1);
    int id = result.tasks->tasks[actual_task].id;
    int period = result.tasks->tasks[actual_task].p;
    
    fprintf(fp,"t%d",id);

    const char* deadline = "*";
    for(int i = 0; i<total_steps;i++){
        fprintf(fp,"& ");

        const char* color = get_color_task(id);
        if(result.simulation[i].running_task_id == id)
            fprintf("\\cellcolor{%s}",color); 

        fprintf(fp,"%s", result.simulation[i].time%period==0? deadline: "");
    }
    fprintf(fp,"\\\\ \n");
}

void generate_table_single_algorithm(FILE *fp, scheduler_result result, int actual_step){
    int total_steps = result.fix_length+1;// 0 no esta contemplado 
    int total_task = result.task_size;

    begin_table(fp,total_steps);
    generate_step_number(fp,result);
    for(int t = 0; t < total_task; t++){
        generate_timeline_task(fp,result, t, actual_step, total_steps);
    }
    fprintf(fp,"\\cline{1-%d}",total_steps+1);
    end_table(fp);
}

void generate_slide_single_algorithm(FILE *fp, const char* title, scheduler_result result){
    printf("Generating for %s\n",title);
    printf("TOTAL length: %d\n",result.simulation_length);
    printf("FIX length: %d\n",result.fix_length);
    for(int step = 0; step < result.fix_length+1; step++){
        begin_slice(fp,title);
        generate_table_single_algorithm(fp,result,step);
        end_slice(fp);
    }
}


void slide_schedulability(FILE *fp, results* res) {
	fprintf(fp, "\\begin{frame}\n");
	fprintf(fp, "\\frametitle{Test de schedulability}\n");
	fprintf(fp, "\\begin{block}{RM: Rate Monotonic}\n");
	fprintf(fp, "$U = \\sum^n_{i=1}{\\frac{C_i}{T_i}\\leq n(2^{1/n}-1))}$\n\n");

//	fprintf(fp, "Under Rate Monotonic, $U = 0.5 < 0.6$. This task set is executable|not sure if executable");//TODO: ADD SCHEDULABLE? UNDER EACH.
	if(res->is_rm){
		fprintf(fp, "\\begin{itemize}\n");

		fprintf(fp, "\\item RM: %s schedulable\n",((res->rm_result.is_schedulable)? "Is" : "Is not"));
		fprintf(fp, "\\end{itemize}\n");
	}
	fprintf(fp, "\\end{block}\n");
	fprintf(fp, "\\begin{block}{EDF and LLF}\n");
	fprintf(fp, "$U = \\sum^n_{i=1}{\\frac{C_i}{T_i}\\leq 1}$\n\n");

//	fprintf(fp, "Under EDF or LLF $U=0.8 < 1.0$ This task set is executable|not executable");//TODO: ADD SCHEDULABLE? UNDER EACH.
	if(res->is_edf || res->is_llf){
		fprintf(fp, "\\begin{itemize}\n");
		printf("res->edf_result.is_schedulable %d\n", res->edf_result.is_schedulable);
		printf("res->llf_result.is_schedulable %d\n", res->llf_result.is_schedulable);
		if(res->is_edf)
			fprintf(fp, "\\item EDF: %s schedulable\n",(res->edf_result.is_schedulable)? "Is" : "Is not");
		if(res->is_llf)
			fprintf(fp, "\\item LLF: %s schedulable\n",(res->llf_result.is_schedulable)? "Is" : "Is not");
		fprintf(fp, "\\end{itemize}\n");
	}
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
