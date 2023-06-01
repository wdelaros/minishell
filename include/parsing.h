#ifndef PARSING_H
#define PARSING_H

# define MAXI 214748364
# define SPACE 32
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define MINUS 45
# define COMMAND 0

# include "../libft/libft.h"
# include "../uwu/C_tool.h"
# include <stdio.h>

typedef struct s_token
{
	char	**token;
	char	*input;
	int		index;
}				t_token;

size_t	ft_sstrlcpy(char *dst, const char *src, size_t dstsize);
char	**string_handler(char *input);
char	*ft_sstrjoin(char const *s1, char const *s2);
int		if_all_quote_closed(char *str, int quote);
int		token_handler_quote(char *str, int i);
int		token_len_quote(char *str);
int		ft_strlen_until(char *str, char *c, int check_space);
int		ft_strlen_until_space(char *str);
void	token_separator(char *str, t_token *token);
void	do_need_realloc(t_token *th, int *i);

#endif