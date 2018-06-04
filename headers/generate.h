#ifndef DOC_INIT_H
#define DOC_INIT_H

#include <stdio.h>
#include "scheduler_result.h"

void init_documentation(results*);

void generate_full_document(results*);

void document_class(FILE *fp);

void packages_document(FILE *fp);

void theme_document(FILE *fp);

void init_document(FILE *fp, results*);

void generate_title(FILE *fp);

void slice_algoritmos(FILE *fp);

void generate_slice_only_RM(FILE *fp,scheduler_result);

void generate_slide_single_algorithm(FILE *fp,const char* title, scheduler_result result);

void generate_pdf();

void open_pdf();

#endif //DOC_INIT_H
