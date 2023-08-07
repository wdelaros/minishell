#include "../../include/built_in.h"

char	**add_environement(char **env, char **cpy_env, char *content, \
int option)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cpy_env[i])
		i++;
	env = ft_calloc(i + 2, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (cpy_env[i])
	{
		if (option == 2 && ft_strsearch(cpy_env[i], '='))
			env[j++] = ft_strdup(cpy_env[i]);
		else if (option != 2)
			env[i] = ft_strdup(cpy_env[i]);
		i++;
	}
	if (option == 1)
	{
		env[i] = ft_strdup(content);
		return (ft_free_null(cpy_env), env);
	}
	return (env);
}

static void	parse_export2(char	*content, char **export, char *check_ex)
{
	int		i;

	i = 0;
	free(check_ex);
	check_ex = ft_strtrim2(content, '=');
	while (export[i])
	{
		if (!ft_strsearch(export[i], '=') && !ft_strcmp(export[i], check_ex))
		{
			free(export[i]);
			export[i] = ft_strdup(content);
			free(check_ex);
			return ;
		}
		else if (!ft_strncmp(export[i], check_ex, ft_strlen(check_ex)))
		{
			free(check_ex);
			return ;
		}
		i++;
	}
	free(check_ex);
	export = add_environement(NULL, export, content, 1);
	struc()->export = export;
}

static void	parse_export(char	*content)
{
	char	**export;
	char	*check_ex;
	int		i;

	i = 0;
	export = struc()->export;
	check_ex = ft_strtrim2(content, '=');
	if (ft_strsearch(content, '='))
		check_ex = ft_fstrjoin(check_ex, "=");
	while (export[i])
	{
		if (ft_strsearch(export[i], '=') && ft_strsearch(check_ex, '=') && \
		!ft_strncmp(export[i], check_ex, ft_strlen(check_ex)))
		{
			free(export[i]);
			export[i] = ft_strdup(content);
			free(check_ex);
			return ;
		}
		i++;
	}
	parse_export2(content, export, check_ex);
}

int	parse_content(char *content, t_data *data)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(content[0]) && content[0] != '_') || \
	ft_strsearch(content, 32))
	{
		ft_dprintf(2, "%s export: `%s': %s\n", MINI, content, ERR);
		data->exit_code = 1;
		return (1);
	}
	while (content[i])
	{
		if (content[i] == '=')
			break ;
		else if (!ft_isalnum(content[i]) && content[i] != '_')
		{
			ft_dprintf(2, "%s export: `%s': %s\n", MINI, content, ERR);
			data->exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(char **content, t_data *data)
{
	int	i;

	i = 1;
	data->exit_code = 0;
	if (!content[i])
		print_export();
	else
	{
		while (content[i])
		{
			if (parse_content(content[i], data))
			{
				i++;
				continue ;
			}
			else
				parse_export(content[i]);
			i++;
		}
		ft_free_null(data->envp);
		data->envp = add_environement(NULL, data->export, NULL, 2);
	}
	return (data->exit_code);
}
