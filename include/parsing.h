#ifndef PARSING_H
#define PARSING_H

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
# include "../uwu/C_tool.h"
# include <stdio.h>

/// @brief List of inputs
/// @param prev Previous element
/// @param next Next element
/// @param input Raw seperated string
/// @param token Token of input
typedef struct s_input
{
	struct s_input	*prev;
	struct s_input	*next;
	char			*input;
	int				token;
}				t_input;

typedef struct s_conv
{
	char	***res;
	int		i;
	int		j;
	int		*sizeofcom;
}				t_conv;

typedef struct s_quote
{
	char	*raw_input;
	int		i;
	int		i_res;
	char	*res;
}				t_quote;

//token.c
void	token_separator(char *str, t_input **ih);
void	print_node(t_input *list); //A enlever

//token_utils.c
int		token_handler_quote(char *str, int i);
int		token_len_quote(char *str);
int		ft_strlen_until_space(char *str);
char	*copy_and_join(char *str, int i);
int		is_command(char *str, int i, t_input *ih);
int		ft_strlen_until_alpha(char *str);
char	*red_handler(char *str, int *i);

//quote_handler.c
char	*quote_handler(char *input);

//parsing.c
char	***string_handler(char *input);

//parsing_utils.c
int		ft_strlen_until(char *str, char *c, int check_space);
char	*ft_sstrjoin(char const *s1, char const *s2);
size_t	ft_sstrlcpy(char *dst, const char *src, size_t dstsize);
t_input	*create_node(void);
void	add_node(t_input **input, int id);
void	free_list(t_input **input_handler);

//convert_list_to_string.c
char	***convert_list_to_string(t_input **ih);

//clean_space.c
void	extra_space_handler(t_input **input);

//clean_option.c
void	clean_option_handler(t_input **ih);

//utils.c
void	parsing_strcpy_len(char *dest, char *src, int len);

#endif