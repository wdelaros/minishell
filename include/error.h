#ifndef ERROR_H
# define ERROR_H

# include "../libft/libft.h"
# include "../uwu/C_tool.h"
# include <stdio.h>

# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

typedef struct s_err
{
	char	*input;
	int		error_code;
}				t_err;

#endif