/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:37:03 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:37:04 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_unset(t_toktab *tab)
{
	int	i;

	if (ft_strcmp(tab->tok[0]->val, "export") == 0
		|| ft_strcmp(tab->tok[0]->val, "unset") == 0
		|| ft_strcmp(tab->tok[0]->val, "cd") == 0)
	{
		i = 1;
		while (i < tab->len)
		{
			if (tab->tok[i]->e_type == pip || (tab->tok[i]->e_type >= redir_l
					&& tab->tok[i]->e_type <= dredir_r))
			{
				tab->curr = i;
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	redirect(t_toktab tab, t_var **var)
{
	if (ft_strcmp(tab.tok[0]->val, "export") == 0)
		return (export(var, tab));
	else if (ft_strcmp(tab.tok[0]->val, "unset") == 0)
		return (unset(var, tab));
	return (cd_with_tab(tab));
}

void	sort_string(char **env)
{
	char	*swap;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				swap = env[i];
				env[i] = env[j];
				env[j] = swap;
			}
			j++;
		}
		i++;
	}
}
