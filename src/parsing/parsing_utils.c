#include "../../include/parsing.h"

char	*replace_char(char *str, char c)
{
	char	*res;
	int		j;
	int		nb_replace;
	int		i;

	nb_replace = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			nb_replace++;
		i++;
	}
	i = 0;
	res = ft_calloc(ft_strlen(str) - nb_replace + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] != c)
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[i] = '\0';
	ft_xfree(str);
	return (res);
}

char	*do_things(char *str)
{
	
}
