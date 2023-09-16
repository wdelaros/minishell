#ifndef PARSING_H
# define PARSING_H

# define MAXI 214748364
# define SPACE 32
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define MINUS 45
# define PIPE 124
# define RED_IN 60
# define RED_OUT 62

# define COMMAND 0
# define OPTION 1
# define ARGUMENT 2
# define SEPARATOR 3

# define NO 0
# define YES 1

# include "../libft/libft.h"
# include "../uwu/inc/C_tool.h"
# include <stdio.h>

/// @brief List of inputs
/// @param prev Previous element
/// @param next Next element
/// @param input Raw seperated string
/// @param token Token of input
/// @param is_quoted If the possible var in input must be i
typedef struct s_input
{
	struct s_input	*prev;
	struct s_input	*next;
	char			*input;
	int				token;
	int				is_quoted;
}				t_input;

typedef struct s_conv
{
	char	***res;
	int		i;
	int		j;
	int		*sizeofcom;
}				t_conv;

typedef struct s_var
{
	int	maxlen;
	int	err_code;
}				t_var;

typedef struct s_quote
{
	char	*raw_input;
	int		i;
	int		i_res;
	char	*res;
}				t_quote;

//parsing_list.c
t_input	*create_node(void);
void	add_node(t_input **input, int id);
void	free_list(t_input **input_handler);
void	create_list(t_input **list, char **input);

//convert_list_to_string.c
char	***convert_list_to_string(t_input **ih, int k);

//parsing_utils.c
int		skip_quote(char *input, int i, int quote);
int		ft_strlen_until(char *str, char *c);
void	parsing_xfree_double(char **str);
char	*return_var(char *var, int err, char **env);

//parsing.c
char	***string_handler(char *input, char **env, int err_code);

//quote_handler.c
void	quote_handler(t_input **input);

//token.c
int		is_command(char **input, int i);
int		is_option(char **input, int i);
int		is_separator(char **input, int i);
int		is_after_red(char **input, int i);

//var_handler.c
void	var_handler(t_input **list, char **env, int err_code);

//var_utils.c
void	ft_str_search_replace(char **str, int start, char *replace);
char	*get_var_parsing(char *var, char **envp);
char	*change_input_with_var(char *str, char **env, int i, t_var t_var);

#endif