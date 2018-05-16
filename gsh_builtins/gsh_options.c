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

// static int	gsh_get_opt(char *str)
// {
// 	extern const char	*g_opt[OPT_NUM];
// 	int			i;

// 	i = 0;
// 	while (g_opt[i])
// 	{
// 		if (!ft_strcmp(g_opt[i], str))
// 			break ;
// 		i++;
// 	}
// 	if (i == 32)
// 		return (-1);
// 	return (i);
// }

static int	gsh_list_opt(char *str, int num)
{
	unsigned			i;
	int					rat;

	i = 0;
	rat = 0;
	while (g_opt[i] && *g_opt[i])
	{
		if (!str || !ft_strcmp(str, g_opt[i]))
		{
			if (g_opt_n & (1 << i) && (num == 0 || num == 1))
				rat = ft_printf("%-16s%s", g_opt[i], " yes\n");
			else if (num == 0 || num == -1)
				rat = ft_printf("%-16s%s", g_opt[i], " no\n");
		}
		i++;
	}
	if (!rat)
		return (1);
	return (0);
}

int			gsh_setopt(char **av)
{
	if (!*av)
		return (gsh_list_opt(0, 0));
	else if (**av == '-')
	{
		;
	}
	while (*av)
	{
		if (gsh_list_opt(*av, 0))
			ft_dprintf(2, "%s%s\n", "setopt: wrong option name: ", *av);
		av++;
	}
	return (0);
}
