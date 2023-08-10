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

static void	update_export(char *var, char *var2)
{
	t_data	*data;
	char	*trim_var;
	int		i;

	i = 0;
	data = struc();
	trim_var = ft_strtrim2(var, '=');
	while (struc()->export[i])
	{
		if (!ft_strncmp(struc()->export[i], var, ft_strlen(var)))
		{
			free(struc()->export[i]);
			data->export[i] = ft_strjoin(var, var2);
		}
		else if (!ft_strcmp(struc()->export[i], trim_var))
		{
			free(struc()->export[i]);
			data->export[i] = ft_strjoin(var, var2);
		}
		i++;
	}
	free(var2);
	free(trim_var);
}

static void	update_env(char *var, char *var2)
{
	t_data	*data;
	char	*trim_var;
	int		i;

	i = 0;
	data = struc();
	trim_var = ft_strtrim2(var, '=');
	while (struc()->envp[i])
	{
		if (!ft_strncmp(struc()->envp[i], var, ft_strlen(var)))
		{
			free(struc()->envp[i]);
			data->envp[i] = ft_strjoin(var, var2);
		}
		else if (!ft_strcmp(struc()->envp[i], trim_var))
		{
			free(struc()->envp[i]);
			data->envp[i] = ft_strjoin(var, var2);
		}
		i++;
	}
	update_export(var, var2);
	free(trim_var);
}

int	cd(char	*dir)
{
	int		err;
	char	*m_pwd;

	if (!dir)
	{
		dir = get_var("HOME=");
		if (!dir)
		{
			ft_dprintf(2, "%s cd: HOME not set\n", MINI);
			return (1);
		}
	}
	m_pwd = getcwd(NULL, 0);
	err = chdir(dir);
	if (err)
	{
		ft_dprintf(2, "%s cd: ", MINI);
		perror(dir);
		free(m_pwd);
		return (1);
	}
	update_env("OLDPWD=", m_pwd);
	update_env("PWD=", getcwd(NULL, 0));
	return (0);
}
