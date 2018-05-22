/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:11:58 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/15 18:11:59 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_options.h"

static int	gsh_get_opt(char *str)
{
	int			i;

	i = 0;
	while (g_opt[i])
	{
		if (!ft_strcmp(g_opt[i], str))
			break ;
		i++;
	}
	if (i == 32)
		return (-1);
	return (i);
}

static int	gsh_list_opt(char *str, int num)
{
	unsigned	i;
	int			rat;

	i = 0;
	rat = 0;
	while (g_opt[i] && *g_opt[i])
	{
		if (!str || !ft_strcmp(str, g_opt[i]))
		{
			if (g_opt_n & (1 << i) && (num == 0 || num == 1))
				rat = ft_printf("%-16s%s", g_opt[i], " yes\n");
			else if (!(g_opt_n & (1 << i)) && (num == 0 || num == 2))
				rat = ft_printf("%-16s%s", g_opt[i], " no\n");
		}
		i++;
	}
	if (!rat)
		return (1);
	return (0);
}

static void	gsh_s_switch_options(char **av, int f)
{
	int i;

	while (*av)
	{
		if ((i = gsh_get_opt(*av)) == -1)
			ft_dprintf(2, "%s%s\n", "setopt: wrong option name: ", *av);
		av++;
		if (f == 1)
			g_opt_n |= (1 << i);
		else
			g_opt_n &= ~(1 << i);
	}
}

static int	gsh_s_optoptopt(char **av)
{
	int i;
	int f;

	i = 1;
	f = 0;
	while ((*av)[i])
	{
		if ((*av)[i] != 's' && (*av)[i] != 'u' && !((*av)[i] == '-' && i == 1
			&& !(*av)[i + 1]))
			return (-1);
		if ((*av)[i] == '-' && i == 1 && !(*av)[i + 1])
			return (0);
		if ((*av)[i] == 's')
			f |= 1;
		else if ((*av)[i] == 'u')
			f |= 2;
		i++;
	}
	if (f == 3 || i == 1)
		return (-1);
	av++;
	if (!*av)
		return (f);
	gsh_s_switch_options(av, f);
	return (0);
}

int			gsh_setopt(char **av)
{
	int num;

	num = 0;
	if (!*av)
		return (gsh_list_opt(0, 0));
	else if (**av == '-')
	{
		if ((num = gsh_s_optoptopt(av)) == -1)
			return (write(2, "usage: setopt [-su][option ...]\n", 32) && 1);
		else if (num)
			gsh_list_opt(0, num);
		return (0);
	}
	while (*av)
	{
		if (gsh_list_opt(*av, num))
			ft_dprintf(2, "%s%s\n", "setopt: wrong option name: ", *av);
		av++;
	}
	return (0);
}
