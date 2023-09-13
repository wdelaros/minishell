#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

# define ERR  "not a valid identifier"
# define MINI "minishell:"

char	**ft_sort_params(int nbr_param, char **tabexport);
char	*ft_strtrim2(char const *s1, char set);
void	print_export(void);
int		parse_content(char *content, t_data *data, const char *built);

char	*get_var(const char *var);

char	**add_environement(char **env, char **cpy_env, char *content, \
int option);
#endif