/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:02:35 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:14:41 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Deletes a single node from a linked list.
/// @param lst The address of a pointer to the node to delete.
/// @param del The address of a function to delete the content of the node.
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del || !lst)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}
