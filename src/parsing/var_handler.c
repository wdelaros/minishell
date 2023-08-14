#include "../../include/parsing.h"

static char	*get_var(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
			return (envp[i] + ft_strlen(var));
		i++;
	}
	return (NULL);
}

static size_t	size_of_var(char *input, char **env)
{
	int		i;
	size_t	len;
	char	*temp;

	i = 0;
	temp = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	while (input[i] && ft_isalpha(input[i]))
	{
		temp[i] = input[i];
		i++;
	}
	len = ft_strlen(get_var(temp, env));
	printf ("Size of var:	%zu\n", len);
	ft_xfree(temp);
	return (len);
}

static size_t	size_projection(char *input, char **env)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE)
		{
			i++;
			size++;
			while (input[i] && input[i] != DOUBLE_QUOTE)
			{
				if (input[i] == '$')
				{
					size += size_of_var(&input[i + 1], env);
					while (input[i]
						&& (ft_isalpha(input[i]) == YES || input[i] == '$'))
						i++;
				}
				i++;
				size++;
			}
		}
		size++;
		i++;
	}
	printf ("Input:	%s Size projected:	%zu\n", input, size);
	return (size);
}

static char	*double_quote_condition(char *input, char **env)
{
	char	*res;
	int		i;
	int		j;
	int		len;
	char	*var;

	i = 0;
	j = 0;
	res = ft_calloc(size_projection(input, env) + 1, sizeof(char));
	while (input[i])
	{
		if (input[i] == '$' && i++)
		{
			len = i;
			while (input[len] && ft_isalpha(input[len]) == YES)
				len++;
			var = ft_fstrjoin(ft_substr(input, i, len - i), "=");
			res = ft_strjoin(res, get_var(var, env));
			i = len;
			j = ft_strlen(res);
		}
		res[j++] = input[i++];
	}
	return (res);
}

void	var_handler(t_input **list, char **env)
{
	int		i;
	t_input	*temp;

	temp = *list;
	while (temp->next)
	{
		i = 0;
		while (temp->input[i])
		{
			if (temp->input[i] == DOUBLE_QUOTE || temp->input[i] == '$')
			{
				temp->input = double_quote_condition(temp->input, env);
			}
			else if (temp->input[i] == SINGLE_QUOTE && i++)
			{
				while (temp->input[i] && temp->input[i] != SINGLE_QUOTE)
					i++;
			}
			i++;
		}
		temp = temp->next;
	}
}
