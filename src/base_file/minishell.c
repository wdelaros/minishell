#include "../../include/minishell.h"

t_data	*struc(void)
{
	static t_data	data;

	return (&data);
}

static void	ft_error(int code)
{
	struc()->exit_code = 258;
	if (code == 1)
		ft_dprintf(2, "minishell: syntax error near unexpected token `|'\n");
	else if (code == 2)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `newline'\n");
	else if (code == 3)
		ft_dprintf(2, \
		"minishell: syntax error near unexpected token `quote'\n");
}

static void	initialize(int argc, char **argv, char **envp, t_data *data)
{
	int		i;
	char	***cmd;

	(void)argc;
	(void)argv;
	data->envp = cpy_environement(NULL, envp);
	data->export = cpy_environement(NULL, envp);
	i = 1;
	cmd = ft_calloc(3, sizeof(char **));
	while (i > 0)
	{
		i--;
		cmd[i] = ft_calloc(7, sizeof(char *));
	}
	cmd[0][0] = ft_strdup("export");
	cmd[0][1] = ft_strdup("OLDPWD");
	data->exit_code = 0;
	data->is_child = 0;
	export(cmd[0], data);
	ft_free_null(cmd[0]);
	data->current_pwd = getcwd(NULL, 0);
	free(cmd);
	logo();
}

int	main(int argc, char **argv, char **envp)
{
	char	***cmd;
	int		err;

	if (signal_handler())
		exit(1);
	initialize(argc, argv, envp, struc());
	while (1)
	{
		struc()->is_child = 0;
		struc()->input = readline("minishell> ");
		if (!struc()->input)
		{
			ft_printf("minishell> exit\n");
			break ;
		}
		if (ft_strcmp("", struc()->input))
			add_history(struc()->input);
		err = error_handler(struc()->input);
		if (err != RUN)
			ft_error(err);
		else if (err == RUN)
		{
			cmd = string_handler(struc()->input, envp);
			run_pipe(cmd);
		}
		printf("exit code: %d\n", struc()->exit_code);
	}
	ft_free_null(struc()->envp);
	ft_free_null(struc()->export);
	rl_clear_history();
	return (0);
}
