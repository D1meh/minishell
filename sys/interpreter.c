/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:26 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:42:28 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "env") == 0
		|| ft_strcmp(command, "unset") == 0
		|| ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

static int	return_free(char **path, int i, char **command, int statut)
{
	(void)i;
	if (!ft_exist(command[0]) && !g_sig.err)
	{
		ft_freetab(path);
		ft_putstr_fd("bash: ", 2);
		if (!ft_isredir(command[0]))
			ft_putstr_fd(command[0] + 1, 2);
		else if (command[2])
			ft_putstr_fd(command[2], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (-1);
	}
	if (WEXITSTATUS(statut))
		return (-1);
	ft_freetab(path);
	return (0);
}

static int	get_statut(char **path, char **command, char **env, int i)
{
	int		statut;
	char	*tmp;
	int		p;

	tmp = ft_strjoin_no_free(path[i], command[0]);
	if (!ft_exist(tmp))
		return (256);
	echo_control_seq(1);
	p = fork();
	error_fork(p);
	g_sig.fork = p;
	if (p == 0)
	{
		if (execve(tmp, command, env) == -1)
			exit(1);
	}
	wait(&statut);
	if (ft_exist(tmp))
		g_sig.err = 1;
	g_sig.fork = -1;
	free(tmp);
	return (statut);
}

static int	try_cmd(char **command, char **env, int err)
{
	int	p;
	int	statut;

	p = fork();
	error_fork(p);
	echo_control_seq(1);
	g_sig.fork = p;
	if (p == 0)
	{
		if (execve(command[0], command, env) == -1)
			exit(1);
	}
	wait(&statut);
	if (!ft_exist(command[0]))
		g_sig.err2 = 1;
	if (!statut && !err)
		return (1);
	if (statut && err)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (0);
}

int	interpreter(char **command, char **env, t_var **var)
{
	int		i;
	int		statut;
	char	*tmp;
	char	**path;

	if (!command[0])
		return (0);
	if (is_builtin(command[0]))
		return (builtin(command, var));
	if (try_cmd(command, env, 0))
		return (0);
	if (!ft_varexist(*var, "PATH"))
		return (try_cmd(command, env, 1));
	path = ft_split(ft_varexist(*var, "PATH"), ':');
	tmp = ft_strdup("/");
	i = -1;
	command[0] = ft_strjoin(tmp, command[0]);
	while (path[++i])
	{
		statut = get_statut(path, command, env, i);
		if (!statut)
			break ;
	}
	return (return_free(path, i, command, statut));
}
