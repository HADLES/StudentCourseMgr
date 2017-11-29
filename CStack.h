#define CSTACK_H  1

#ifndef COURSE_H
#include "Course.h"
#endif

typedef struct CStackNode {
	int size;
	Course courses[MAXSIZE/2];
} CStack;
