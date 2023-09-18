#include "../../libft.h"

/// @brief checks if a character is a printable ASCII character.
/// @param c the character to be checked.
/// @return returns 1 if the character is a printable ASCII character, 
/// and 0 otherwise.
int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}
