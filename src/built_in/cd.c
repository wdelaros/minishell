#include "../../include/minishell.h"

static char	*get_var(const char *var)
{
	int	i;

	i = 0;
	while (struc()->envp[i])
	{
		if (!ft_strncmp(struc()->envp[i], var, ft_strlen(var)))
			return (struc()->envp[i] + ft_strlen(var));
		i++;
	}
	return (NULL);
}

int cd(char	*dir)
{
	if (!dir || !ft_strcmp(dir, "~"))
	{
		dir = get_var("HOME=");
		if (!dir)
		{
			ft_dprintf(2, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else if (!ft_strcmp(dir, "-"))
	{
		dir = get_var("OLDPWD=");
		if (!dir)
		{
			ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
			return (1);
		}
	}
	chdir(dir);
	return (0);
}
