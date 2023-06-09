#include "../../include/parsing.h"

int	token_handler_quote(char *str, int i)
{
	if (str[i] == DOUBLE_QUOTE)
		while (str[i] && !(str[i - 1] == DOUBLE_QUOTE && str[i] == SPACE))
			i++;
	else if (str[i] == SINGLE_QUOTE)
		while (str[i] && !(str[i - 1] == SINGLE_QUOTE && str[i] == SPACE))
			i++;
	else
		while (str[i] && str[i] != SPACE)
			i++;
	return (i);
}

int	token_len_quote(char *str)
{
	int	len;

	len = 0;
	if (str[len] == DOUBLE_QUOTE)
	{
		len = ft_strlen_until(str, "\"|><\0", 0);
		len++;
	}
	else if (str[len] == SINGLE_QUOTE)
	{
		len = ft_strlen_until(str, "\'|><\0", 0);
		len++;
	}
	else
		len = ft_strlen_until(str, "\"\'|><\0", 0);
	return (len);
}

int	ft_strlen_until_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SPACE)
			return (i);
		i++;
	}
	return (i);
}

char	*copy_and_join(char *str, int i)
{
	int		len;
	char	*res;
	char	*temp;

	res = NULL;
	temp = NULL;
	len = token_len_quote(&str[i]);
	printf ("LEN:%d\n", len);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[i], len);
	res = ft_sstrjoin(res, temp);
	ft_xfree(temp);
	return (res);
}

static int	separator_count(t_input **ih)
{
	t_input	*temp;
	int		count;

	count = 1;
	temp = (*ih);
	while (temp)
	{
		if (temp->token == 3)
			count++;
		temp = temp->next;
	}
	return (count);
}

char	***convert_list_to_string(t_input **ih)
{
	char	***res;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = separator_count(ih);
	// printf ("NOMBRE DE SEPARATOR:%d\n", len);
	res = ft_calloc(len + 1, sizeof(char **));
	// printf ("CALLOC A RÉUSSI\n");
	while (i <= len)
	{
		len = node_len_until_separator((*ih));
		// printf ("NOMBRE DE STRING DANS LE **:%d\n", len);
		res[j] = ft_calloc(len + 1, sizeof(char *));
		j++;
		i++;
	}
	// printf ("MALLOC DE ** RÉUSSIE\n");
	j = 0;
	i = 0;
	while ((*ih)->next)
	{
		// printf("STRING TO BE PROCESS:%s\n", (*ih)->input);
		if ((*ih)->token != 3 && (*ih)->token != -1)
		{
			// printf("COPIAGE DE STRING\n");
			res[j][i] = ft_strdup((*ih)->input);
			// printf("COPIAGE DE STRING CUMZONE\n");
			i++;
		}
		else if ((*ih)->token == 3)
		{
			i = 0;
			j++;
			res[j][i] = ft_strdup((*ih)->input);
			// printf ("STRING SEPARATOR:%s\n", res[j][i]);
			j++;
			// printf("SEPARATION DE STRING\n");
		}
		(*ih) = (*ih)->next;
	}
	// printf("CONVERTION COMPLETE\n");
	return (res);
}

int	is_command(char *str, int i)
{
	while (str[--i])
	{
		if (str[i] == '\0' || str[i] == PIPE
			|| str[i] == RED_IN || str[i] == RED_OUT)
			return (YES);
		else if (ft_isspace(str[i]) == 0)
			return (NO);
	}
	return (YES);
}
