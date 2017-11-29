//调试时，指输入学分
#define DEBUG  1

#define foreach(T,N)  for(int i = 0; i < N ; i++,*T++)
//和上面的foreach配对使用
#define reset_pointer(T,N)  for(int i = 0; i < N ; i++,*T--)

#define NEW_COURSE (Course*)malloc(sizeof(Course))

#define new_Course() (Course*)malloc(sizeof(Course))

#define _DECLARE_COURSE_MEMERS_\
	Course *course = NEW_COURSE; \
	char no[INPUT_CHAR_SIZE]; \
	char name[INPUT_CHAR_SIZE]; \
	char type[INPUT_CHAR_SIZE]; \
	float totalTime; \
	float givingCourseTime; \
	float practiceTime; \
	float operatingTime; \
	float score; \
	char info[INPUT_CHAR_SIZE*2]; \
	 
#define _PUSH_CSTACK_\
	strcpy(course->no,no); \
	strcpy(course->name,name); \
	strcpy(course->type,type); \
	course->totalTime=totalTime; \
	course->givingCourseTime=givingCourseTime; \
	course->practiceTime=practiceTime; \
	course->operatingTime=operatingTime; \
	course->score=score; \
	strcpy(course->info,info); \
	int idx=++stack.size-1; \
	++num; \
	stack.courses[idx]=*course; \
	 
#define OUT_FILE_PATH "output.txt"

#define QUERY_BY_TYPE(_T_);\
	FILE *fp;\
	fp = fopen(OUT_FILE_PATH,"r");\
	if(fp == NULL) {\
		printf("打开不了本地文件!\n ");\
		system("pause");\
		exit(0);\
	}\
	while(!feof(fp)) {\
		_DECLARE_COURSE_MEMERS_\
		fscanf(fp,"%s %s %s %f %f %f %f %f %s\n",&no,&name,&type,&totalTime,&givingCourseTime,&practiceTime,&operatingTime,&score,&info);\
		if(0==strcmp(type,_T_)) {\
			fflush(stdin);\
			_PUSH_CSTACK_\
			printf("%s  %s  %s  %0.1f  %0.1f  %0.1f  %0.1f  %0.1f %s\n",\
			       no,\
			       name,\
			       type,\
			       totalTime,\
			       givingCourseTime,\
			       practiceTime,\
			       operatingTime,\
			       score,\
			       info\
			      );\
		}\
	} \
	fclose(fp);\
	 
//stack.courses[idx]=*course不含指针则直接复制
//memcpy(&stack.courses[idx],&course,sizeof(Course));//会出现乱码,适用于指针


