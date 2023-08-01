#include "../../include/minishell.h"

static char	*get_home(void)
{
	int	i;

	i = 0;
	while (struc()->envp[i])
	{
		if (!ft_strncmp(struc()->envp[i], "HOME=", 5))
			return (struc()->envp[i] + 5);
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
			ft_dprintf(2, "minishell: cd: HOME not set\n");
			return (1);
		}
		chdir(dir);
		/*
		OLDPWD = strdup pwd
		PWD = ft_strdup(getcwd(NULL, 0));
		*/
	}
	chdir(dir);
	return (0);
}
