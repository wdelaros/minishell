#include "../../include/parsing.h"

char	**string_handler(char *input)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_split(input, SPACE);
	while (res[i])
	{
		if (ft_strsearch(res[i], DOUBLE_QUOTE) == 1
			|| ft_strsearch(res[i], SINGLE_QUOTE) == 1)
			res[i] = do_things(res[i]);
		i++;
	}
	return (res);
}
