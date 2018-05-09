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
		while (hist && hist->str)
		{
			ft_printf("\t%d  %s\n", i, hist->str);
			hist = hist->nxt;
			i++;
		}
	}
	return (0);
}
