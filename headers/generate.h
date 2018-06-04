#ifndef DOC_INIT_H
#define DOC_INIT_H

#include <stdio.h>

void init_documentation();

void generate_full_document();

void document_class(FILE *fp);

void packages_document(FILE *fp);

void theme_document(FILE *fp);

void init_document(FILE *fp);

void generate_title(FILE *fp);

void slice_algoritmos(FILE *fp);

void generate_pdf();

void open_pdf();

#endif //DOC_INIT_H
