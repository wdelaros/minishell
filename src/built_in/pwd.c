/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:39 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/19 13:34:40 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

int	pwd(void)
{
	char	*str;

	struc()->exit_code = 0;
	str = getcwd(NULL, 0);
	if (!str)
		str = ft_strdup(struc()->current_pwd);
	return (ft_printf("%s\n", str), free(str), struc()->exit_code);
}
