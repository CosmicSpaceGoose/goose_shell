/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 17:00:12 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/08 17:00:14 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

int			gsh_h_usage(int err)
{
	if (err == 1)
		ft_putendl_fd("history: -d option requires an argument", 2);
	if (err == 2)
		ft_putendl_fd("history: numeric argument required", 2);
	ft_putendl_fd("history usage:\n\thistory [-c] [-d offset] [n]\n\t\
history -awrn [filename]\n\thistory -ps arg [arg...]", 2);
	return (1);
}

static void	gsh_h_print_last(int num)
{
	int		i;
	t_hist	*hist;

	i = 0;
	hist = gsh_r_history_bucket(RETURN, NULL);
	while (hist->nxt)
		hist = hist->nxt;
	while (hist->prv && i < num)
	{
		hist = hist->prv;
		i++;
	}
	while (hist->nxt)
	{
		ft_printf("%5d  %s\n", hist->no, hist->str);
		hist = hist->nxt;
	}
}

static int	gsh_h_sum_func(char **av)
{
	t_hist	*hist;

	if (!*av)
	{
		hist = gsh_r_history_bucket(RETURN, NULL);
		while (hist->prv)
			hist = hist->prv;
		while (hist)
		{
			ft_printf("%5d  %s\n", hist->no, hist->str);
			hist = hist->nxt;
		}
	}
	else if (ft_isnumber(*av))
		gsh_h_print_last(ft_atoi(*av));
	else
		return (gsh_h_usage(2));
	return (0);
}

static int	gsh_h_write_history(char *str, int mod)
{
	int		fd;
	t_hist	*hist;

	if (!str)
		str = gsh_get_env("HISTFILE");
	if ((fd = open(str, mod, S_IRUSR | S_IWUSR)) != -1)
	{
		hist = gsh_r_history_bucket(RETURN, NULL);
		while (hist->prv)
			hist = hist->prv;
		while (hist)
		{
			write(fd, hist->str, ft_strlen(hist->str));
			write(fd, "\n", 1);
			hist = hist->nxt;
		}
		close(fd);
		return (0);
	}
	return (1);
}

int			gsh_history(char **av)
{
	if (*av && **av == '-')
	{
		if (*(*av + 1) == '-')
			return (gsh_h_sum_func(av + 1));
		if (*(*av + 1) == 'c')
			gsh_r_history_bucket(ERASE, NULL);
		else if (*(*av + 1) == 's')
			gsh_h_add_record();
		else if (*(*av + 1) == 'p')
			gsh_h_show_without_add(av + 1);
		else if (*(*av + 1) == 'd')
			return (gsh_h_erase_elem(*(av + 1)));
		else if (*(*av + 1) == 'a')
			return (gsh_h_write_history(*(av + 1), 01011));
		else if (*(*av + 1) == 'n')
			gsh_h_read_history(*(av + 1));
		else if (*(*av + 1) == 'r')
			gsh_h_init_history(*(av + 1));
		else if (*(*av + 1) == 'w')
			return (gsh_h_write_history(*(av + 1), 03001));
		else
			return (gsh_h_usage(0));
		return (0);
	}
	return (gsh_h_sum_func(av));
}
