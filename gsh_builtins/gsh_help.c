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

#include "gsh_core.h"

const char			*g_help[] = {
	" - change working directory",
	" - print some text in terminal",
	" - env managment & run program",
	" - exit goose_shell",
	" - print this help massege",
	" - modificate shell history",
	" - set local variable",
	" - set environment variable",
	" - change shell behavior",
	" - delete local variable",
	" - delete environment variable",
	0
};

static void	gsh_help_commands_graph(void)
{
	unsigned	i;
	unsigned	speed;

	speed = (unsigned)ft_atoi(gsh_get_env("GRAPHICS_OUTPUT_SPEED"));
	if (speed > 100000)
		speed = 100000;
	i = 0;
	ft_printf("  _____________/\\_________________________\n");
	usleep(speed);
	ft_printf(" /            BUILT-IN COMMANDS           \\\n");
	usleep(speed);
	while (g_builtin[i].name)
	{
		ft_printf("|  %3$s%4$-8s%1$s%5$-30s%2$s  |\n", WHT, NON, RED,
		g_builtin[i].name, g_help[i]);
		usleep(speed);
		i++;
	}
	ft_printf(" \\________________________________________/\n");
	usleep(speed);
}

static void	gsh_help_commands_non_gr(void)
{
	unsigned	i;

	i = 0;
	ft_putstr("BUILT-IN COMMANDS:\n");
	while (g_builtin[i].name)
	{
		ft_printf("%-8s%-30s\n", g_builtin[i].name, g_help[i]);
		i++;
	}
}

int			gsh_help(char **av)
{
	extern uint32_t	g_opt_n;

	if (*av == NULL)
	{
		if (g_opt_n & GRAPHICS)
			gsh_help_commands_graph();
		else
			gsh_help_commands_non_gr();
	}
	return (0);
}
