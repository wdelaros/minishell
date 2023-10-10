/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:08 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/10 15:54:25 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

char	*mini_parsing(char *str, char **env, int err)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && (str[i + 1] == DQ
					|| str[i + 1] == SQ))
				i = skip_quote(str, i + 1, str[i + 1]);
			else
			{
				normal_condition(&str, env, i, err);
				i = -1;
			}
		}
		if (i == -1 || str[i])
			i++;
	}
	return (str);
}
