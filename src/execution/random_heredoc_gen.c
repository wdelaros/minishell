#include "../../include/execution.h"

char	*heredoc_file(void)
{
	char	*file;
	char	*temp;
	int		i;

	i = 0;
	file = ft_strdup(".HeReDoC");
	if (access(file, F_OK))
		return (file);
	temp = ft_strdup(file);
	while (i < 100)
	{
		file = ft_ffstrjoin(file, ft_itoa(i));
		if (access(file, F_OK))
		{
			ft_xfree(temp);
			return (file);
		}
		ft_xfree(file);
		file = ft_strdup(temp);
		i++;
	}
	return (NULL);
}
