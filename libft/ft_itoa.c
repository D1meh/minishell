/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:39:16 by mtaouil           #+#    #+#             */
/*   Updated: 2021/08/10 18:39:17 by mtaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	base10(int n)
{
	int	base;

	if (n == 0)
		return (1);
	base = 0;
	while (n != 0)
	{
		n /= 10;
		base++;
	}
	return (base);
}

static char	*alloc_nb(int n)
{
	char	*numb;
	int		size;

	size = base10(n) + 1;
	if (n < 0)
	{
		numb = malloc(sizeof(char) * size + 1);
		numb[0] = '-';
	}
	else
		numb = malloc(sizeof(char) * size);
	return (numb);
}

static char	*rempl_tab(int n, char *numb)
{
	int				i;
	unsigned int	nb;

	i = base10(n);
	if (n < 0)
	{
		i++;
		nb = n * -1;
	}
	else
		nb = n;
	numb[i] = 0;
	i--;
	while (numb[i] != '-' && i >= 0)
	{
		numb[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	return (numb);
}

char	*ft_itoa(int n)
{
	char	*numb;

	numb = alloc_nb(n);
	if (n == 0)
	{
		numb[0] = '0';
		numb[1] = 0;
	}
	else
		numb = rempl_tab(n, numb);
	return (numb);
}
