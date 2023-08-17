#include "../../include/parsing.h"

// static int	do_search(char *str, char *search)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (ft_strncmp(&str[i], search, ft_strlen(search)) == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// static void	do_replace(char *str, char *res, int start, int size)
// {
// 	int	i;

// 	i = 0;
// 	(void)size;
// 	ft_strlcpy(res, str, (ft_strlen(str) - start) + 1);
// }

void	ft_str_search_replace(char **str, int end, char *replace)
{
	int		i;
	int		size;
	char	*res;
	char	*temp;

	i = end;
	size = 0;
	res = NULL;
	temp = *str;
	while (temp[i] && temp[i - 1] && temp[i] != '$')
	{
		size++;
		i--;
	}
	res = ft_calloc(ft_strlen(temp) + (ft_strlen(replace) - size), sizeof(char));
	ft_strlcpy(res, temp, i + 1);
	if (!replace)
	{
		temp = ft_strdup(res);
		*str = temp;
		ft_xfree(res);
		return ;
	}
	ft_strcat(res, replace);
	ft_strcat(res, &temp[end]);
	printf ("RES: %p	", res);
	Ct_mprintf(res, ft_strlen(res) + 1, 1, 'A');
	temp = ft_strdup(res);
	printf ("TEMP: %p	", temp);
	Ct_mprintf(temp, ft_strlen(temp) + 1, 1, 'B');
	ft_xfree(res);
	*str = temp;
	printf ("STR: %p	", *str);
	Ct_mprintf(*str, ft_strlen(*str) + 1, 1, 'C');
}
