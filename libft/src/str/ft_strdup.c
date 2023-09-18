#include "../../libft.h"

/// @brief Duplicate a string.
/// @param s1 The string to be duplicated.
/// @return A pointer to the new duplicated string, or NULL if allocation 
/// fails.
char	*ft_strdup(const char *s1)
{
	if (!s1)
		return (NULL);
	return (ft_substr(s1, 0, ft_strlen(s1)));
}
