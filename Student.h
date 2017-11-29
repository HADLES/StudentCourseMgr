#define STUDENT_H 1

#ifndef COURSE_H
#include "Course.h"
#endif
#define COURSE_NUM 8
typedef struct StudentNode {
	Course course[COURSE_NUM];
} Student;
