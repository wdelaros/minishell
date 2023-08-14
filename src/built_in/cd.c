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
	ft_free_null(data->envp);
	data->envp = add_environement(NULL, data->export, NULL, 2);
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
	update_export("OLDPWD=", m_pwd);
	update_export("PWD=", getcwd(NULL, 0));
	return (0);
}
