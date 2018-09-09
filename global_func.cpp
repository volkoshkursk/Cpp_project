#include "global_func.h"
//#include "func.h"

bool file_ask(char* name)
{
	FILE * file;
	file = fopen(name,"r");
	if (file)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	fclose(file);
}