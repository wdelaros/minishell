/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:19:30 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:14:56 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Finds the last node of a linked list.
/// @param lst The beginning of the linked list.
/// @return The last node of the linked list, or NULL if the list is empty.
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	if (lst->next == NULL)
		return (lst);
	return (ft_lstlast(lst->next));
}
