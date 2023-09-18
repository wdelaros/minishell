#include "../../libft.h"

void	*ft_xfree(void	*pointer)
{
	if (pointer)
		free(pointer);
	return (NULL);
}
