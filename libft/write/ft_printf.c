/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:08:15 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/05 09:30:05 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_formats(va_list args, const char format, int fd)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_printchar(va_arg(args, int), fd);
	else if (format == 's')
		len += ft_printstr(va_arg(args, char *), fd);
	else if (format == 'p')
		len += ft_printptr(va_arg(args, uintptr_t), fd);
	else if (format == 'd' || format == 'i')
		len += ft_printnbr(va_arg(args, int), fd);
	else if (format == 'u')
		len += ft_printunnbr(va_arg(args, unsigned int), fd);
	else if (format == 'x' || format == 'X')
		len += ft_printhex(va_arg(args, unsigned int), format, fd);
	else if (format == '%')
		len += ft_printchar(37, fd);
	return (len);
}

/// @brief The ft_printf function prints formatted output to the 
/// standard output.
/// @param str The format string.
/// @param ... The variable arguments list.
/// @return The total number of characters printed.
int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	if (!str)
		return (0);
	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_formats(args, str[i + 1], 1);
			i++;
		}
		else
			len += ft_printchar(str[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}

/// @brief The ft_dprintf function prints formatted output 
/// to the specified file descriptor.
/// @param fd The file descriptor to write to.
/// @param str The format string.
/// @param ... The variable arguments list.
/// @return The total number of characters printed.
int	ft_dprintf(int fd, const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	if (!str)
		return (0);
	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_formats(args, str[i + 1], fd);
			i++;
		}
		else
			len += ft_printchar(str[i], fd);
		i++;
	}
	va_end(args);
	return (len);
}
