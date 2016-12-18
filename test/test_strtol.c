#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int tmpValue;
	char* str[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10"};
	
	for(i = 0; i < 10; i++)
	{
		tmpValue = strtol(str[i], NULL, 10);
		printf("Decode \"%s\": %d\n", str[i], tmpValue);
	}

	return 0;
}
