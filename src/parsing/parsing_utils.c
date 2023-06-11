#include "../../include/parsing.h"

int	ft_strlen_until(char *str, char *c, int check_space)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(str);
	j = 0;
	if (c[j] == '\0' && check_space == 1)
		len = ft_strlen_until_space(str);
	while (c[j])
	{
		i = 0;
		while (str[i])
		{
			if ((str[i] == c[j] && i != 0 && len > i))
				len = i;
			else if (check_space == 1 && str[i] == SPACE && len > i)
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
		str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char) + 1);
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

t_input	*create_node(void)
{
	t_input	*temp;

	temp = ft_calloc(1, sizeof(t_input));
	if (!temp)
		return (NULL);
	temp->token = -1;
	return (temp);
}

void	add_node(t_input **input, int id)
{
	t_input	*current;

	if (*input == NULL)
	{
		(*input) = create_node();
		return ;
	}
	current = (*input);
	while (current->next != NULL)
		current = current->next;
	current->next = create_node();
	if (!current->next)
		return ;
	current->next->prev = current;
	current->token = id;
}

size_t	node_len_until_separator(t_input *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		if (list->token == 3)
			return (i);
		i++;
		list = list->next;
	}
	return (i);
}
