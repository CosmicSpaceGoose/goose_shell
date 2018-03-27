/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 12:58:35 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/26 12:58:37 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_reader.h"

t_hist	*gsh_r_hist_add_elem(t_hist *hist)
{
	if (!hist)
	{
		hist = (t_hist *)malloc(sizeof(t_hist));
		hist->tmp = ft_strdup("");
		hist->str = NULL;
		hist->prv = NULL;
		hist->nxt = NULL;
	}
	else if (hist->str)
	{
		hist->nxt = (t_hist *)malloc(sizeof(t_hist));
		hist->nxt->tmp = ft_strdup("");
		hist->nxt->str = NULL;
		hist->nxt->prv = hist;
		hist->nxt->nxt = NULL;
		return (hist->nxt);
	}
	return (hist);
}

t_hist	*gsh_r_hist_rewrite_elem(char *str, t_hist *hist)
{
	while (hist->prv)
		hist = hist->prv;
	while (hist->nxt)
	{
		free(hist->tmp);
		hist->tmp = NULL;
		hist = hist->nxt;
	}
	if (hist->tmp)
	{
		free(hist->tmp);
		hist->tmp = NULL;
	}
	if (*str)
		hist->str = ft_strdup(str);
	return (hist);
}

void	gsh_r_remove_history(t_hist *hist)
{
	t_hist *tmp;

	while (hist)
	{
		tmp = hist;
		hist = hist->nxt;
		if (tmp->str)
		{
			ft_putendl_fd(tmp->str, 2);
			free(tmp->str);
		}
		if (tmp->tmp)
		{
			ft_putendl_fd(tmp->tmp, 2);
			free(tmp->tmp);
		}
		free(tmp);
		tmp = NULL;
	}
}

/*
**	mod:
**	0 - on start, create hist elem
**	1 - on return, add new elem, erase tmp
**	2 - page up
**	3 - page down
**	-1 - on shell exit, erase history
*/

char	*gsh_r_history_bucket(int mod, char *str)
{
	static t_hist	*hist;

	if (hist)
		ft_dprintf(2, "%p str=%s tmp=%s prv=%p nxt=%p\n", hist, hist->str, hist->tmp, hist->prv, hist->nxt);
	if (mod == 0)
		hist = gsh_r_hist_add_elem(hist);
	else if (mod == 1)
		hist = gsh_r_hist_rewrite_elem(str, hist);
	else if (mod == 2)
	{
		if (!hist->prv)
			write(0, "\a", 1);
		else
		{
			if (hist->tmp)
				free(hist->tmp);
			hist->tmp = ft_strdup(str);
			hist = hist->prv;
			if (hist->tmp)
				return (hist->tmp);
			return (hist->str);
		}
	}
	else if (mod == 3)
	{
		if (!hist->nxt)
			write(0, "\a", 1);
		else
		{
			if (hist->tmp)
				free(hist->tmp);
			hist->tmp = ft_strdup(str);
			hist = hist->nxt;
			if (hist->tmp)
				return (hist->tmp);
			return (hist->str);
		}
	}
	else if (mod == -1)
	{
		gsh_r_remove_history(hist);
		hist = NULL;
	}
	return (NULL);
}