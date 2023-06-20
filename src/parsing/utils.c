#include "../../include/parsing.h"

void	parsing_strcpy_len(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
