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
	len = ft_strlen_until(&str[*i], "\"\'-\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[*i], len);
	*res = ft_sstrjoin(*res, temp);
	ft_xfree(temp);
	while (str[*i] && (str[*i] != DOUBLE_QUOTE && str[*i] != SINGLE_QUOTE
			&& str[*i] != MINUS && str[*i] != SPACE))
		(*i)++;
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
	len = ft_strlen_until(&str[*i], "\"\'-\0", 1);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[*i], len);
	*res = ft_sstrjoin(*res, temp);
	ft_xfree(temp);
	while (str[*i] && str[*i] != SPACE)
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
/// @return Index after the separatpr has been seperated.
static void	separator_seperator(char *str, char **res, int *i)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen_until_alpha(&str[*i]);
	temp = ft_calloc(len + 1, sizeof(char));
	ft_sstrlcpy(temp, &str[*i], len);
	*res = ft_sstrjoin(*res, temp);
	ft_xfree(temp);
	while (str[*i] != SPACE)
		(*i)++;
}

static int	token_if(char *str, t_input **ih, int i)
{
	t_input	*temp;

	temp = (*ih);
	while (temp->next)
		temp = temp->next;
	// printf ("RESTANT DE LA STRING:%s	CHAR:%c\n", &str[i], str[i]);
	if (ft_isalpha(str[i]) == YES && is_command(str, i) == YES)
	{
		// printf ("OUI OUI JE SUIS UNE COMMANDE ET ME VOICI:");
		command_separator(str, &temp->input, &i);
		// printf ("%s\n", temp->input);
		add_node(&temp, COMMAND);
		temp = temp->next;
	}
	// printf ("RESTANT DE LA STRING APRÈS COMMAND:%s\n", &str[i]);
	if (str[i] == PIPE || str[i] == RED_IN || str[i] == RED_OUT)
	{
		separator_seperator(str, &temp->input, &i);
		add_node(&temp, SEPARATOR);
		temp = temp->next;
	}
	// printf ("RESTANT DE LA STRING APRÈS SEPARATOR:%s\n", &str[i]);
	if (temp->input == NULL && str[i] == MINUS)
	{
		option_separator(str, &temp->input, &i);
		add_node(&temp, OPTION);
		temp = temp->next;
	}
	// printf ("RESTANT DE LA STRING APRÈS OPTION:%s\n", &str[i]);
	if (str[i] && (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE
			|| ft_isascii(str[i])) && str[i] != SPACE)
	{
		argument_seperator(str, &temp->input, &i);
		add_node(&temp, ARGUMENT);
		temp = temp->next;
	}
	//printf ("RESTANT DE LA STRING APRÈS ARG:%s\n", &str[i]);
	return (i);
}
// A ENLEVER
void	print_node(t_input *list)
{
	while (list)
	{
		printf ("MESSAGE:%s	ID:%d\n", list->input, list->token);
		list = list->next;
	}
}

/// @brief Handle the seperation of the raw input.
/// @param str raw input.
/// @param th token struct.
/// @return No return value.
void	token_separator(char *str, t_input **ih)
{
	size_t	i;

	i = 0;
	(*ih) = create_node();
	while (i < ft_strlen(str))
	{
		i = token_if(str, ih, i);
		if (str[i] == SPACE)
			i++;
		// printf ("INDEX:%zu\n", i);
	}
}
