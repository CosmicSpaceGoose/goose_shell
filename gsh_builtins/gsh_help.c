/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:06:11 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/18 16:06:16 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_graphics.h"
#include "gsh_core.h"

static void	gsh_help_commands(void)
{
	unsigned long		i;
	extern const t_fptr	g_builtin[11];

	i = 0;
	ft_printf("  _____________/\\_________________________\n");
	usleep(TIME);
	ft_printf(" /            BUILT-IN COMMANDS           \\\n");
	usleep(TIME);
	while (i < 7)
	{
		ft_printf("|  %3$s%4$-8s%1$s%5$-30s%2$s  |\n", WHT, NON, RED,
		g_builtin[i].name, g_help[i]);
		usleep(TIME);
		i++;
	}
	ft_printf(" \\________________________________________/\n");
	usleep(TIME);
}

int			gsh_help(char **av)
{
	if (*av == NULL)
		gsh_help_commands();
	return (0);
}
