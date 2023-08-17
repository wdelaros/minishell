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

// static size_t	size_of_var(char *input, char **env)
// {
// 	int		i;
// 	size_t	len;
// 	char	*temp;

// 	i = 0;
// 	temp = ft_calloc(ft_strlen(input) + 1, sizeof(char));
// 	while (input[i] && ft_isalpha(input[i]))
// 	{
// 		temp[i] = input[i];
// 		i++;
// 	}
// 	len = ft_strlen(get_var(temp, env));
// 	ft_xfree(temp);
// 	return (len);
// }

// static size_t	size_projection(char *input, char **env)
// {
// 	size_t	size;
// 	int		i;

// 	size = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == DOUBLE_QUOTE)
// 		{
// 			i++;
// 			size++;
// 			while (input[i] && input[i] != DOUBLE_QUOTE)
// 			{
// 				if (input[i] == '$')
// 				{
// 					size += size_of_var(&input[i + 1], env);
// 					while (input[i]
// 						&& (ft_isalpha(input[i]) == YES || input[i] == '$'))
// 						i++;
// 					i++;
// 					size++;
// 					break ;
// 				}
// 				i++;
// 				size++;
// 			}
// 		}
// 		size++;
// 		i++;
// 	}
// 	return (size);
// }

static int	skip_quote(char *input, int i, int quote)
{
	i++;
	if (quote == 1)
		while (input[i] && input[i] != SINGLE_QUOTE)
			i++;
	else if (quote == 2)
		while (input[i] && input[i] != DOUBLE_QUOTE)
			i++;
	return (i);
}

static int	double_quote_condition(char **input, char **env, int i)
{
	int		max_len;
	char	*var;
	int		j;
	int		start;
	char	*temp;

	temp = *input;
	max_len = skip_quote(temp, i, 2);
	printf("%d	%d\n", i, max_len);
	start = i;
	var = ft_calloc (max_len + 1, sizeof(char));
	while (i < max_len)
	{
		if (temp[i] && temp[i] == '$' && i++)
		{
			printf ("hihi\n");
			j = 0;
			while (temp[i] && ft_isalpha(temp[i]) == YES)
				var[j++] = temp[i++];
			var = ft_strjoin(var, "=");
			var = ft_strdup(get_var(var, env));
			ft_str_search_replace(&temp, i, var);
			i = start;
			printf ("TEMP SPECIAL UWU: %p	", temp);
			Ct_mprintf(temp, ft_strlen(temp) + 1, 1, 'D');
			ft_bzero(var, max_len);
		}
		i++;
	}
	printf ("TEMP DANS LA FONCTION DE PISS: %p	", temp);
	Ct_mprintf(temp, ft_strlen(temp) + 1, 1, 'E');
	*input = temp;
	printf ("RES DANS LA FONCTION DE PISS: %p	", *input);
	Ct_mprintf(*input, ft_strlen(*input) + 1, 1, 'F');
	ft_xfree(var);
	return (skip_quote(temp, start, 2));
}

// static int	normal_condition(char *input, char **env, int i)
// {
// }

void	var_handler(t_input **list, char **env)
{
	t_input	*temp;
	int		i;

	temp = *list;
	while (temp->next)
	{
		i = 0;
		while (temp->input[i])
		{
			if (temp->input[i] == '$')
			{
				;
				// i = normal_condition(temp->input, env, i);
			}
			else if (temp->input[i] == DOUBLE_QUOTE)
			{
				i = double_quote_condition(&temp->input, env, i);
				printf ("RES FINALE: %p	", temp->input);
				Ct_mprintf(temp->input, ft_strlen(temp->input) + 1, 1, 'G');
			}
			else if (temp->input[i] == SINGLE_QUOTE)
				i = skip_quote(temp->input, i, 1);
			i++;
		}
		temp = temp->next;
	}
}
