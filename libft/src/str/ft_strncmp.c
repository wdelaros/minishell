#include "../../libft.h"

/// @brief This function compares two strings, s1 and s2, up to n characters.
/// @param s1 A pointer to the first string to be compared.
/// @param s2 A pointer to the second string to be compared.
/// @param n The maximum number of characters to be compared.
/// @return The function returns an integer greater than, equal to, or less 
/// than 0, according to whether the string s1 is greater than, equal to, or 
/// less than the string s2.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s1[i] == s2[i] && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
