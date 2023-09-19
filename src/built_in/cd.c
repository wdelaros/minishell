/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:25 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:34:26 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	update_export(char *var, char *var2, t_data	*data)
{
	char	*trim_var;
	int		i;

	i = 0;
	if (!var2)
	{
		free(var2);
		return ;
	}
	trim_var = ft_strtrim2(var, '=');
	while (struc()->export[i])
	{
		if (!ft_strncmp(struc()->export[i], var, ft_strlen(var)) || \
		!ft_strcmp(struc()->export[i], trim_var))
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
			return (ft_dprintf(2, "%s cd: HOME not set\n", MINI), 1);
	}
	err = chdir(dir);
	if (err)
		return (ft_dprintf(2, "%s cd: ", MINI), perror(dir), 1);
	update_export("OLDPWD=", ft_strdup(struc()->current_pwd), struc());
	update_export("PWD=", getcwd(NULL, 0), struc());
	m_pwd = getcwd(NULL, 0);
	if (m_pwd)
	{
		free(struc()->current_pwd);
		struc()->current_pwd = m_pwd;
	}
	return (0);
}
