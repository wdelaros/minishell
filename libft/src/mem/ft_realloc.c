#include "../../libft.h"

void	*ft_realloc(void *old, size_t size, size_t len, size_t new_len)
{
	void	*new;

	if (!old)
		return (NULL);
	new = ft_calloc(size, new_len);
	if (!new)
		return (NULL);
	if (len > new_len)
		ft_memcpy(new, old, size * new_len);
	else
		ft_memcpy(new, old, size * len);
	ft_xfree(old);
	return (new);
}
