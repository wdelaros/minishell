/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:34 by wdelaros          #+#    #+#             */
/*   Updated: 2023/05/08 08:01:50 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		add_history(input);
	}
	rl_clear_history();
	return (0);
}
