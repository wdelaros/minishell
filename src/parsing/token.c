#include "../../include/parsing.h"

/// @brief Seperate the command from the raw input.
/// @param str raw input.
/// @param res the command seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the command has been seperated.
static void	command_separator(char *str, char **res, int *i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until(&str[*i], "\"\'<>|\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return ;
	ft_sstrlcpy(temp, &str[*i], len);
	*res = ft_strdup(temp);
	ft_xfree(temp);
	while (str[*i] && (str[*i] != DOUBLE_QUOTE && str[*i] != SINGLE_QUOTE
			&& str[*i] != SPACE && str[*i] != RED_IN
			&& str[*i] != RED_OUT && str[*i] != PIPE))
		(*i)++;
}

/// @brief Seperate the option from the raw input.
/// @param str raw input.
/// @param res the option seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the option has been seperated.
static void	option_separator(char *str, char **res, int *i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until(&str[*i], "\"\'<>|\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return ;
	ft_sstrlcpy(temp, &str[*i], len);
	*res = ft_strdup(temp);
	ft_xfree(temp);
	while (str[*i] && str[*i] != SPACE && str[*i] != RED_IN
		&& str[*i] != RED_OUT && str[*i] != PIPE)
		(*i)++;
	while (str[*i] == SPACE)
		(*i)++;
}

/// @brief Seperate the argument from the raw input.
/// @param str raw input.
/// @param res the argument seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the argument has been seperated.
static void	argument_seperator(char *str, char **res, int *i)
{
	*res = copy_and_join(str, *i);
	if (!res)
		return ;
	if (str[*i] == DOUBLE_QUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != DOUBLE_QUOTE)
			(*i)++;
		(*i)++;
	}
	else if (str[*i] == SINGLE_QUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != SINGLE_QUOTE)
			(*i)++;
		(*i)++;
	}
	else
		while (str[*i] && str[*i] != DOUBLE_QUOTE && str[*i] != SINGLE_QUOTE
			&& str[*i] != PIPE && str[*i] != RED_IN && str[*i] != RED_OUT)
			(*i)++;
}

/// @brief Seperate the separator from the raw input.
/// @param str raw input.
/// @param res the separator seperated from the input.
/// @param i current index in the raw input.
/// @return Index after the separator has been seperated.
static void	separator_seperator(char *str, char **res, int *i)
{
	int		len;
	char	*temp;

	temp = NULL;
	if (str[*i] == RED_IN || str[*i] == RED_OUT)
	{
		*res = red_handler(str, i);
		if (!res)
			return ;
	}
	else if (str[*i] == PIPE)
	{
		len = ft_strlen_until_alpha(&str[*i]);
		temp = ft_calloc(len + 1, sizeof(char));
		if (!temp)
			return ;
		ft_sstrlcpy(temp, &str[*i], len);
		*res = ft_strdup(temp);
		while (str[*i] && str[*i] != SPACE && ft_isalpha(str[*i]) == NO)
			(*i)++;
	}
	ft_xfree(temp);
}

static int	token_if(char *str, t_input **ih, int i)
{
	t_input	*temp;

	temp = (*ih);
	while (temp->next)
		temp = temp->next;
	if (str[i] == PIPE || str[i] == RED_IN || str[i] == RED_OUT)
	{
		separator_seperator(str, &temp->input, &i);
		add_node(&temp, SEPARATOR);
		temp = temp->next;
	}
	else if (ft_isascii(str[i]) == YES && is_command(str, i, *ih) == YES
		&& str[i] != SPACE)
	{
		command_separator(str, &temp->input, &i);
		add_node(&temp, COMMAND);
		temp = temp->next;
	}
	else if (temp->input == NULL && str[i] == MINUS)
	{
		option_separator(str, &temp->input, &i);
		add_node(&temp, OPTION);
		temp = temp->next;
	}
	else if (str[i] && (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE
			|| ft_isascii(str[i])) && str[i] != SPACE)
	{
		argument_seperator(str, &temp->input, &i);
		add_node(&temp, ARGUMENT);
		temp = temp->next;
	}
	return (i);
}
// A ENLEVER
void	print_node(t_input *list)
{
	while (list)
	{
		Ct_mprintf(list->input, ft_strlen(list->input) + 1, 1, 'A');
		printf ("ID: %d\n", list->token);
		list = list->next;
	}
	printf ("\n");
}

/// @brief Handle the seperation of the raw input.
/// @param str raw input.
/// @param th token struct.
/// @return No return value.
void	token_separator(char *str, t_input **ih)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		i = token_if(str, ih, i);
		if (i < ft_strlen(str) && str[i] == SPACE)
			i++;
	}
}
