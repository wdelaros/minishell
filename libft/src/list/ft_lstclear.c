#include "../../libft.h"

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
