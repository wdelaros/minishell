#include "../../libft.h"

/// @brief Converts an uppercase letter to lowercase.
/// @param c The character to be converted.
/// @return The lowercase equivalent of the input character.
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
