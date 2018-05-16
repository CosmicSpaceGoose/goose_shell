/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:22:19 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/17 14:22:20 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

void		gsh_write_head(void)
{
	unsigned	speed;

	speed = (unsigned)ft_atoi(gsh_get_env("GRAPHICS_OUTPUT_SPEED"));
	if (speed > 100000)
		speed = 100000;
	ft_printf("%s   __                 \n", WHT);
	usleep(speed);
	ft_printf("  /  \\%s___         #   ____ ____ ____\n", YLW);
	usleep(speed);
	ft_printf("%1$s |  %2$so%1$s |%3$s .\\        #  ||G |||S |||H ||\n\
", WHT, RED, YLW);
	usleep(speed);
	ft_printf("%s |    |%s   \\___    #  ||__|||__|||__||\n", WHT, YLW);
	usleep(speed);
	ft_printf("%s_/    |%s_______\\   #  |/__\\|/__\\|/__\\|\n", WHT, YLW);
	usleep(speed);
	ft_printf("%s      |%s-----/\n", WHT, YLW);
	usleep(speed);
	ft_printf("%s_____/%s\n", WHT, NON);
	usleep(speed);
}

size_t		gsh_prompt(int mod)
{
	char	buf[BUFSIZE];
	char	*ptr;

	if (!isatty(0))											//<<<---   0 -> 2
		return (0);
	getcwd(buf, BUFSIZE);
	if (!ft_strcmp(buf, getpwuid(getuid())->pw_dir))
		ptr = "~";
	else
		ptr = ft_strrchr(buf, '/');
	if (mod)
	{
		if (*(ptr + 1))
			ft_dprintf(0, "\e[37m%s > \e[0m", ptr + 1);		//<<<---   0 -> 2
		else
			ft_dprintf(0, "\e[37m%s > \e[0m", ptr);			//<<<---   0 -> 2
	}
	if (*(ptr + 1))
		return (ft_strlen(ptr) + 2);
	return (ft_strlen(ptr) + 3);
}

void		exit_draw(void)
{
	unsigned	speed;

	speed = (unsigned)ft_atoi(gsh_get_env("GRAPHICS_OUTPUT_SPEED"));
	if (speed > 100000)
		speed = 100000;
	ft_printf("\n%s____\n", WHT);
	usleep(speed);
	ft_printf("    \\\n");
	usleep(speed);
	ft_printf("_    \\______\n");
	usleep(speed);
	ft_printf(" \\          \\\n");
	usleep(speed);
	ft_printf("  \\        \\ \\\n");
	usleep(speed);
	ft_printf("  |         \\_|\n");
	usleep(speed);
	ft_printf("  \\          /\n");
	usleep(speed);
	ft_printf("   \\________/\n");
	usleep(speed);
	ft_printf("%s    ||    ||\n", YLW);
	usleep(speed);
	ft_printf("   /__\\  /__\\\n%s", NON);
	usleep(speed);
}

int			gsh_exit(char **av)
{
	int chaek;

	chaek = 0;
	if (av && *av)
	{
		if (*(av + 1))
		{
			ft_dprintf(2, "%s\n", "exit: Too many arguments.");
			return (0);
		}
		chaek = ((unsigned char)ft_atoi(*av));
	}
	return (chaek + 256);
}

/*
**		//gotcha! it's a trap!
*/
