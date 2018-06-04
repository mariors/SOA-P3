#ifndef DOC_INIT_H
#define DOC_INIT_H

#include <stdio.h>

void init_documentation();

void generate_full_document();

void type_document(FILE *fp);

void packages_document(FILE *fp);

void init_document(FILE *fp);

void generate_title(FILE *fp);

void slice_1(FILE *fp);

void generate_pdf();

#endif //DOC_INIT_H
