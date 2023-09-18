#include "../../libft.h"

/// @brief Copy a memory area from source to destination.
/// @param dst A pointer to the destination memory area.
/// @param src A pointer to the source memory area.
/// @param n The number of bytes to be copied.
/// @return A pointer to the destination memory area.
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (!dst || !src)
		return (dst);
	if (dst != NULL || src != NULL)
		while (n--)
			*d++ = *s++;
	return (dst);
}
