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

typedef struct s_token
{
	char	**token;
	char	*input;
	int		index;
}				t_token;

typedef struct s_input
{
	struct s_input	*prev;
	struct s_input	*next;
	char			*input;
	int				token;
}				t_input;

t_input	*create_node(void);
size_t	ft_sstrlcpy(char *dst, const char *src, size_t dstsize);
size_t	node_len(t_input *list);
char	***string_handler(char *input);
// char	***convert_list_to_string(t_input **ih);
char	*ft_sstrjoin(char const *s1, char const *s2);
char	*copy_and_join(char *str, int i);
int		if_all_quote_closed(char *str, int quote);
int		token_handler_quote(char *str, int i);
int		token_len_quote(char *str);
int		ft_strlen_until(char *str, char *c, int check_space);
int		ft_strlen_until_space(char *str);
void	add_node(t_input **input, int id);
void	token_separator(char *str, t_input **ih);
void	do_need_realloc(t_token *th, int *i);
void	quote_handler(t_input **input);
void	print_node(t_input *list); //A enlever

#endif