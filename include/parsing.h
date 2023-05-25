#ifndef PARSING_H
#define PARSING_H


# define SPACE 32
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define MINUS 45
# define COMMAND 0

# include "../libft/libft.h"
# include <stdio.h>

typedef struct s_token
{
	char	**token;
	char	*input;
}				t_token;

char	**string_handler(char *input);
int		if_all_quote_closed(char *str, int quote);
char	*replace_char(char *str, char c);
void	token_separator(char *str, t_token *token);
int		ft_strlen_until(char *str, char *c, int check_space);
char	*ft_sstrjoin(char const *s1, char const *s2);
size_t	ft_sstrlcpy(char *dst, const char *src, size_t dstsize);

#endif