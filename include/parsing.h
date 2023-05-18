#ifndef PARSING_H
#define PARSING_H


# define SPACE 32
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

# include "../libft/libft.h"
# include <stdio.h>

char	**string_handler(char *input);
char	*do_things(char *str);
char	*replace_char(char *str, char c);

#endif