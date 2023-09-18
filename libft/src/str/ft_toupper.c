#include "../../libft.h"

/// @brief Converts an lowercase letter to uppercase.
/// @param c The character to be converted.
/// @return The uppercase equivalent of the input character.
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
