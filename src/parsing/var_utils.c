#include "../../include/parsing.h"

void	ft_str_search_replace(char *str, char *search, char *replace)
{
	int		i;
	char	*res;
	int		flag;

	i = 0;
	flag = 0;
	printf ("%s	%s	%s\n", str, search, replace);
	// if (!replace)
		// do_null();
	while (str[i])
	{
		if (ft_strncmp(&str[i], search, ft_strlen(search)) == 0)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		return ;
	printf ("SDCASDASD\n");
	res = ft_calloc(ft_strlen(str) + (ft_strlen(replace) - ft_strlen(search)) + 1, sizeof(char));
	do_replace();
}
