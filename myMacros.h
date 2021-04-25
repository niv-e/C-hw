#include <stdio.h>
#include <stdlib.h>

#define CHECK_RETURN_0(ptr) if(ptr == NULL) return 0;

#define CHECK_RETURN_NULL(ptr) if(ptr == NULL) return NULL;

#define CHECK_MSG_RETURN_0(ptr){\
						if (ptr == NULL) {\
							printf("This pointer NULL");\
							return 0;\
						}\
}

#define CHECK_0_MSG_COLSE_FILE(value, file){\
						if(value == 0){\
							printf("This value equals to zero..");\
							fclose(file);\
							return 0;\
						}\
}

#define CHECK_NULL__MSG_COLSE_FILE(value, file){\
						if(value == NULL){\
							printf("This value equals to NULL..");\
							fclose(file);\
							return 0;\
						}\
}

#define MSG_CLOSE_RETURN_0(file){\
						printf("ERROR MASSAGE");\
						fclose(file);\
							return 0;\
						}
