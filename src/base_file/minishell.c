/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:34:22 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/22 10:41:32 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data	*struc(void)
{
	static t_data	data;

	return (&data);
}

static void	pre_exec(char ***cmd, int err)
{
	err = error_handler(struc()->input);
	if (err != RUN)
		ft_error(err);
	else if (err == RUN)
	{
		cmd = string_handler(struc()->input, struc()->envp, \
		struc()->exit_code);
		run_pipe(cmd);
	}
}

static void	ft_prompt(char	***cmd)
{
	char	*line;

	while (1)
	{
		// signal_handler(NO, YES);
		line = ft_prompt_line();
		struc()->input = readline(line);
		free(line);
		if (!struc()->input)
		{
			ft_printf("minishell> exit\n");
			break ;
		}
		// signal_handler(NO, NO);
		if (ft_strcmp("", struc()->input))
			add_history(struc()->input);
		pre_exec(cmd, 0);
	}
}

static void	initialize(char **envp, t_data *data)
{
	int		i;
	char	***cmd;

	i = 1;
	data->envp = cpy_environement(NULL, envp);
	data->export = cpy_environement(NULL, envp);
	cmd = ft_calloc(3, sizeof(char **));
	while (i > 0)
	{
		i--;
		cmd[i] = ft_calloc(7, sizeof(char *));
	}
	cmd[0][0] = ft_strdup("export");
	cmd[0][1] = ft_strdup("OLDPWD");
	data->exit_code = 0;
	export(cmd[0], data);
	ft_free_null(cmd[0]);
	data->current_pwd = getcwd(NULL, 0);
	free(cmd);
	logo();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	initialize(envp, struc());
	ft_prompt(NULL);
	free(struc()->current_pwd);
	ft_free_null(struc()->envp);
	ft_free_null(struc()->export);
	rl_clear_history();
	return (struc()->exit_code);
}
