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
	unsigned			i;
	unsigned			speed;
	extern const t_fptr	g_builtin[BLTN_NUM];

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

int			gsh_help(char **av)
{
	if (*av == NULL)
		gsh_help_commands();
	return (0);
}
