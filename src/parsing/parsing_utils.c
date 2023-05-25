#include "../../include/parsing.h"

char	*replace_char(char *str, char c)
{
	char	*res;
	int		j;
	int		nb_replace;
	int		i;

	nb_replace = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			nb_replace++;
		i++;
	}
	i = 0;
	res = ft_calloc(ft_strlen(str) - nb_replace + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] != c)
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[i] = '\0';
	ft_xfree(str);
	return (res);
}

int	ft_strlen_until(char *str, char *c, int check_space)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(str);
	while (c[j])
	{
		i = 0;
		while (str[i])
		{
			if ((str[i] == c[j] && i != 0 && len > i) || (check_space == 1 && str[i] == SPACE))
				len = i;
			i++;
		}
		j++;
	}
	return (len);
}

char	*ft_sstrjoin(char const *s1, char const *s2) 
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		str = malloc(ft_strlen(s2) * sizeof(char) + 1);
	else
		str = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (0);
	if (s1)
		while (s1[i])
			str[j++] = s1[i++];
	while (s2[k])
		str[j++] = s2[k++];
	str[j] = '\0';
	return (str);
}
size_t	ft_sstrlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}