#ifndef ERROR_H
# define ERROR_H

# include "../libft/libft.h"
# include "../uwu/inc/C_tool.h"
# include <stdio.h>

# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define MINUS 45
# define PIPE 124
# define RED_IN 60
# define RED_OUT 62
# define NO 0
# define YES 1

typedef struct s_err
{
	char	*input;
	int		error_code;
}				t_err;

#endif