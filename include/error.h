/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:27:30 by wdelaros          #+#    #+#             */
/*   Updated: 2023/10/03 14:40:23 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../libft/libft.h"

# define DQ 34
# define SQ 39
# define MINUS 45
# define PIPE 124
# define RD_I 60
# define RD_O 62
# define NO 0
# define YES 1

typedef struct s_err
{
	char	*input;
	int		error_code;
}				t_err;

void	mul_red_error(t_err *err, int i);

#endif