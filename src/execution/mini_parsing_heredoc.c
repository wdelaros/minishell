#include "../../include/execution.h"
#include "../../include/parsing.h"

char	*mini_parsing(char *str, char **env, int err)
{
	int	i;

	i = 0;
	Ct_mprintf(str, ft_strlen(str) + 1, 1, 'A');
	while (str[i])
	{
		if (str[i] == '$')
		{
			printf ("AMBOUT\n");
			normal_condition(&str, env, i , err);
			i = -1;
		}
		i++;
	}
	return (str);
}
