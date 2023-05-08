/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:19:47 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:14:31 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Deletes and frees all the nodes of a linked list and sets the first 
/// element to NULL.
/// @param lst A pointer to a pointer to the first element of the linked list.
/// @param del The function to delete the content of a node.
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (lst && *lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}	
}
