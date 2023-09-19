#include "../../include/execution.h"
#include "../../include/parsing.h"

char	*mini_parsing(char *str, char **env, int err)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && (str[i + 1] == DOUBLE_QUOTE || str[i + 1] == SINGLE_QUOTE))
				i = skip_quote(str, i + 1, str[i + 1]);
			else
			{
				normal_condition(&str, env, i , err);
				i = -1;
			}
		}
		if (i == -1 || str[i])
			i++;
	}
	Ct_mprintf(str, ft_strlen(str) + 1, 1, 'A');
	return (str);
}
