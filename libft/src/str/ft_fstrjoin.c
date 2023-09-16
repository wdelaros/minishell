#include "../../libft.h"

/// @brief A function that concatenates two strings and frees the first one.
/// @param s1 The first string to concatenate.
/// @param s2 The second string to concatenate.
/// @return A pointer to the new string, or NULL if the allocation fails. The 
/// function also frees the first string passed as argument.
char	*ft_fstrjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (free(s1), free(s2), NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (free(s1), str);
}

char	*ft_frstrjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (free(s1), free(s2), NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (free(s2), NULL);
	i = 0;
	j = 0;
	while (s2[i])
	{
		str[i] = s2[i];
		i++;
	}
	while (s1[j])
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	return (free(s2), str);
}

char	*ft_ffstrjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (free(s1), free(s2), NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (free(s1), free(s2), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (free(s1), free(s2), str);
}