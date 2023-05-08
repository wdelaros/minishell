/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 07:09:28 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:42:50 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_getline(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str || !str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
	{
		line = ft_calloc(1, sizeof(char));
		return (line);
	}
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*nextline(char *str)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] || !str)
		return (free(str), NULL);
	buff = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!buff)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i])
		buff[j++] = str[i++];
	return (free(str), buff);
}

char	*readstr(int fd, char *str)
{
	char	*buff;
	int		i;

	if (!str)
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (NULL);
	}
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (free(str), NULL);
	i = 1;
	while (!(ft_strchr(str, '\n')) && i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (free(buff), free(str), NULL);
		buff[i] = 0;
		str = ft_fstrjoin(str, buff);
		if (!str)
			return (free(buff), NULL);
	}
	return (free(buff), str);
}

/// @brief The get_next_line function reads a line from a file descriptor
/// and returns it as a string.
/// @param fd The file descriptor of the file to read from.
/// @return A pointer to the next line of the file as a string, or NULL 
/// if there are no more lines to read or an error occurred.
char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	str[fd] = readstr(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_getline(str[fd]);
	str[fd] = nextline(str[fd]);
	return (line);
}
