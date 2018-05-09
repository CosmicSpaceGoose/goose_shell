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
	ft_printf("%s   __                 \n", WHT);
	usleep(TIME);
	ft_printf("  /  \\%s___         #   ____ ____ ____\n", YLW);
	usleep(TIME);
	ft_printf("%1$s |  %2$so%1$s |%3$s .\\        #  ||G |||S |||H ||\n\
", WHT, RED, YLW);
	usleep(TIME);
	ft_printf("%s |    |%s   \\___    #  ||__|||__|||__||\n", WHT, YLW);
	usleep(TIME);
	ft_printf("%s_/    |%s_______\\   #  |/__\\|/__\\|/__\\|\n", WHT, YLW);
	usleep(TIME);
	ft_printf("%s      |%s-----/\n", WHT, YLW);
	usleep(TIME);
	ft_printf("%s_____/%s\n", WHT, NON);
	usleep(TIME);
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
	ft_printf("\n%s____\n", WHT);
	usleep(TIME);
	ft_printf("    \\\n");
	usleep(TIME);
	ft_printf("_    \\______\n");
	usleep(TIME);
	ft_printf(" \\          \\\n");
	usleep(TIME);
	ft_printf("  \\        \\ \\\n");
	usleep(TIME);
	ft_printf("  |         \\_|\n");
	usleep(TIME);
	ft_printf("  \\          /\n");
	usleep(TIME);
	ft_printf("   \\________/\n");
	usleep(TIME);
	ft_printf("%s    ||    ||\n", YLW);
	usleep(TIME);
	ft_printf("   /__\\  /__\\\n%s", NON);
	usleep(TIME);
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
