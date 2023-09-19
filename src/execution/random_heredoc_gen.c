/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_heredoc_gen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:19 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:35:20 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

char	*heredoc_file(void)
{
	char	*file;
	char	*temp;
	int		i;

	i = 0;
	file = ft_strdup(".HeReDoC");
	if (access(file, F_OK))
		return (file);
	temp = ft_strdup(file);
	while (i < 1000)
	{
		file = ft_ffstrjoin(file, ft_itoa(i));
		if (access(file, F_OK))
		{
			ft_xfree(temp);
			return (file);
		}
		ft_xfree(file);
		file = ft_strdup(temp);
		i++;
	}
	return (NULL);
}
