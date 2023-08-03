#include "../../include/minishell.h"

static char	**ft_sort_params(int nbr_param, char **tabexport)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < nbr_param)
	{
		j = i + 1;
		while (j < nbr_param)
		{
			if (ft_strcmp(tabexport[j], tabexport[i]) < 0)
			{
				temp = tabexport[i];
				tabexport[i] = tabexport[j];
				tabexport[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (tabexport);
}

static void	print_export(void)
{
	char	**export;
	int		i;
	int		j;

	i = 0;
	export = struc()->export;
	export = ft_sort_params(ft_strlen_double(export), export);
	while (export[i])
	{
		j = 0;
		ft_printf("declare -x ");
		while (export[i][j] != '=' && export[i][j])
		{
			ft_putchar_fd(export[i][j], 1);
			j++;
		}
		if (ft_strsearch(export[i], '='))
		{
			ft_putchar_fd('=', 1);
			ft_printf("\"%s\"", ft_strchr(export[i], '=') + 1);
		}
		ft_printf("\n");
		i++;
	}
}

/// @brief Allocates a new string by trimming leading and trailing characters 
/// from a given string.
/// @param s1 The string to be trimmed.
/// @param set The characters to be trimmed.
/// @return The newly allocated string, or NULL if allocation failed.
static char	*ft_strtrim2(char const *s1, char set)
{
	char	*str;
	size_t	i;
	size_t	index;

	index = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[index] && s1[index] != set)
		index++;
	if (!s1[index])
		index = ft_strlen(s1);
	str = malloc(sizeof(char) * (index + 1));
	if (!str)
		return (0);
	i = -1;
	while (++i < index)
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

char	**add_environement(char **env, char **cpy_env, char	*content)
{
	int	i;

	i = 0;
	while (cpy_env[i])
		i++;
	env = ft_calloc(i + 2, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (cpy_env[i] && cpy_env[i + 1])
	{
		env[i] = ft_strdup(cpy_env[i]);
		i++;
	}
	env[i] = ft_strdup(content);
	return (ft_free_null(cpy_env), env);
}

static void	parse_export(char	*content)
{
	char	**export;
	char	*check_ex;
	char	*check_ex2;
	int		i;

	i = 0;
	export = struc()->export;
	check_ex = NULL;
	check_ex = ft_fstrjoin(ft_strtrim2(content, '='), "=");
	check_ex2 = ft_strtrim2(content, '=');
	while (export[i])
	{
		if ((ft_strsearch(content, '=') && !ft_strncmp(export[i], check_ex, \
		ft_strlen(check_ex))) || (!ft_strsearch(content, '=') && \
		!ft_strcmp(export[i], check_ex2)))
		{
			free(export[i]);
			export[i] = ft_strdup(content);
			return ;
		}
		i++;
	}
	export = add_environement(NULL, export, content);
	struc()->export = export;
	free(check_ex);
}

int	export(char **content)
{
	int	i;

	i = 1;
	struc()->exit_code = 0;
	if (!content[i])
		print_export();
	else
	{
		while (content[i])
		{
			if ((!ft_isalpha(content[i][0]) && content[i][0] != '_') || \
			ft_strsearch(content[i], 32))
			{
				ft_dprintf(2, "minishell: export: `%s': "\
				"not a valid identifier\n", content[i]);
				struc()->exit_code = 1;
				i++;
				continue ;
			}
			parse_export(content[i]);
			i++;
		}
	}
	return (struc()->exit_code);
}
