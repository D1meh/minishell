/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 09:52:46 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/11 09:52:47 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	write_in_file(int fd, char **tmp)
{
	write(fd, *tmp, ft_strlen(*tmp));
	if (*tmp)
		write(fd, "\n", 1);
	free(*tmp);
	*tmp = NULL;
	ft_putstr("> ");
	return (ft_gnl(tmp, 0));
}

static void	init_function(int *fd, char *file, int *std)
{
	*fd = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	g_sig.dred_l = 1;
	echo_control_seq(0);
	*std = dup(STDIN_FILENO);
}

void	temp_file(t_toktab *tab, int i)
{
	static char		file[8] = "/tmp/f";
	char			*tmp;
	int				fd;
	int				std;
	struct stat		buf;

	file[6] = 0;
	tmp = char_toa(i + '0');
	ft_strcat(file, tmp);
	free(tmp);
	tmp = NULL;
	init_function(&fd, file, &std);
	while ((fstat(STDIN_FILENO, &buf) != -1)
		&& ft_strcmp(tmp, tab->tok[i + 1]->val) != 0)
		if (write_in_file(fd, &tmp) == 0 && ft_strlen(tmp) == 0)
			break ;
	g_sig.dred_l = 0;
	if (ft_strcmp(tmp, tab->tok[i + 1]->val))
		dup2(std, STDIN_FILENO);
	if (tmp && !g_sig.ctrl_c)
		free(tmp);
	close(fd);
	tab->temp[0] = file;
}

int	double_left(t_fd *f)
{
	static int	n = 0;
	int			fd;

	fd = open(f->file[n], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	n++;
	close(fd);
	return (0);
}
