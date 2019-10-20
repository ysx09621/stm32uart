#include <stdio.h>
#include <string.h>
//在字符串中选出以逗号隔开的数字"v=12,13,14,145"
int main()
{   
    char *pos = NULL;
    int num;
	unsigned char q[] = "v=12,13,14,145";
	pos = &q[2];
	while(pos!=NULL)
	{
			num =	atoi(pos);
			printf("%d\n",num);	
			pos = strstr(pos,",");	
			if(pos!=NULL)
			{
				pos++;	
			}  			
	}

    return 0;
}
