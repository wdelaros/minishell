#include "../../include/built_in.h"

char	*get_var(const char *var)
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

int	cd(char	*dir)
{
	int	err;

	if (!dir)
	{
		dir = get_var("HOME=");
		if (!dir)
		{
			ft_dprintf(2, "%s cd: HOME not set\n", MINI);
			return (1);
		}
	}
	err = chdir(dir);
	if (err)
	{
		ft_dprintf(2, "%s cd: ", MINI);
		perror(dir);
		return (1);
	}
	return (0);
}
