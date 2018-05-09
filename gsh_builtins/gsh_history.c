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

void		gsh_r_remove_history(t_hist *hist)
{
	t_hist *tmp;

	while (hist->prv)
		hist = hist->prv;
	while (hist)
	{
		tmp = hist;
		hist = hist->nxt;
		if (tmp->str)
			free(tmp->str);
		if (tmp->tmp)
			free(tmp->tmp);
		free(tmp);
		tmp = NULL;
	}
	hist = NULL;
}

int			gsh_history(char **av)
{
	t_hist	*hist;
	int		i;

	if (!*av)
	{
		hist = gsh_r_history_bucket(-2, NULL);
		while (hist->prv)
			hist = hist->prv;
		i = 1;
		while (hist->nxt)
		{
			ft_printf("%5d  %s\n", i, hist->str);
			hist = hist->nxt;
			i++;
		}
	}
	return (0);
}
