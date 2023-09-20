/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:27:24 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/20 13:49:49 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

# define ERR  "not a valid identifier"
# define MINI "minishell:"

char	**ft_sort_params(int nbr_param, char **tabexport);
char	*ft_strtrim2(char const *s1, char set);
void	print_export(void);
int		parse_content(char *trim, char *content, t_data *data,
			const char *built);

char	*get_var(const char *var);

char	**add_environement(char **env, char **cpy_env, char *content,
			int option);
#endif