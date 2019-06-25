#include <stdlib.h>
#include <stdio.h>
#include "../inc/malloc.h"

int main()
{
	char *addr;

	printf("OK OK --");
	addr = (char*)malloc(5);
	printf("OK OK");
	//addr[0] = 42;
	printf("CURRENT = %p TINY = %p", g_zone.current, &g_zone.tiny);
	return (0);
}
