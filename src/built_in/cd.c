#include "../../include/minishell.h"

static char	*get_home(void)
{
	int	i;
	// int	j;

	i = 0;
	while (struc()->envp[i])
	{
		if (ft_strncmp(struc()->envp[i], "HOME=", 5))
		{
			
		}
		i++;
	}
	return (NULL);
}

int cd(char	*dir)
{
	if (!dir)
	{
		dir = get_home();
		if (!dir)
		{
			ft_dprintf(2, "minishell: cd: cd: HOME not set\n");
			return (1);
		}
		/*
		old = strdup pwd
		PWD = ft_strdup(getcwd(NULL, 0));
		*/
	}
	chdir(dir);
	return (0);
}
