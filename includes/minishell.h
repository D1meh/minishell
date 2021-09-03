/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:37:34 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:43:32 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <sys/stat.h>

# include "lexer.h"
# include "libft.h"

typedef struct s_fd
{
	int		fd1;
	int		fd2;
	char	**file;
}	t_fd;

typedef struct s_sig
{
	int		fork;
	int		dred_l;
	int		ctrl_c;
	int		err;
	int		err2;
	int		ret;
	char	*l;
}	t_sig;

t_sig	g_sig;

t_var	*init_var(char **env);
void	init_global(char *l);
void	read_loop(t_var *var);
void	rl_replace_line(const char *s, int n);

char	*replace_dollar(char *val, t_var *var);
int		parser(t_toktab tab, t_var **var);
int		piper(t_toktab tab, char **envp, int in, t_var **var);
int		interpreter(char **command, char **env, t_var **var);
int		builtin(char **command, t_var **var);
int		redirect(t_toktab tab, t_var **var);

int		get_quote(char *s);
int		empty(char *s);
int		onlyquote(char *s);
void	temp_file(t_toktab *tab, int i);
int		error_fork(int p);
int		ret_error(int i);
char	**tvar_to_env(t_var *var);
int		ft_exist(char *file);
int		return_val(int i);
void	finish_piper(t_toktab tab, int in, char **command, int fds[]);
void	interrupt(int sig);
void	quit_interr(int sig);
void	sigint_interr(int sig);
void	echo_control_seq(int c);

void	change_input_output(t_fd *f, int fds[], int in, int a);
int		change_in_out(t_fd *f, char **command);
int		redirection(char **command, int i, t_fd *f, int *n);
int		double_left(t_fd *f);

int		export_unset(t_toktab *tab);
int		pwd(void);
int		env(t_var *v);
int		export(t_var **var, t_toktab tab);
int		print_env(t_var *var);
void	sort_string(char **env);
int		unset(t_var **var, t_toktab tab);
int		ft_exit(char *l, t_var *v);
int		echo(char **command);
int		cd(char **command);
int		cd_with_tab(t_toktab tab);

int		bad_file(char **command);
void	put_error(char **command, int statut);

#endif
