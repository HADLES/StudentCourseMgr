#define COURSE_H  1

#ifndef float
#include <float.h>
#define INPUT_CHAR_SIZE 15

typedef struct CourseNode{
	char no[INPUT_CHAR_SIZE];
	char name[INPUT_CHAR_SIZE];
	char type[INPUT_CHAR_SIZE];
	float totalTime;
	float givingCourseTime;
	float practiceTime;
	float operatingTime;
	float score;
	
	char info[INPUT_CHAR_SIZE*2];
}Course;
#endif
