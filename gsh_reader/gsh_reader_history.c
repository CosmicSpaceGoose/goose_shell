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

static t_hist	*gsh_r_hist_add_elem(t_hist *hist)
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

static t_hist	*gsh_r_hist_rewrite_elem(char *str, t_hist *hist)
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
	if (str && *str)
		hist->str = ft_strdup(str);
	return (hist);
}

static void		gsh_r_remove_history(t_hist *hist)
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

/*
**	mod:
**	0 - on start, create hist elem
**	1 - on return, add new elem, erase tmp
**	2 - page up
**	3 - page down
**	-1 - on shell exit, erase history
*/

static char		*gsh_r_browse_history(int mod, t_hist **hist, char *str)
{
	if (mod == 2)
	{
		if ((*hist)->tmp)
			free((*hist)->tmp);
		(*hist)->tmp = ft_strdup(str);
		(*hist) = (*hist)->prv;
		if ((*hist)->tmp)
			return ((*hist)->tmp);
		return ((*hist)->str);
	}
	if ((*hist)->tmp)
		free((*hist)->tmp);
	(*hist)->tmp = ft_strdup(str);
	(*hist) = (*hist)->nxt;
	if ((*hist)->tmp)
		return ((*hist)->tmp);
	return ((*hist)->str);
}

char			*gsh_r_history_bucket(int mod, char *str)
{
	static t_hist	*hist;

	if ((mod == 2 && !hist->prv) || (mod == 3 && !hist->nxt))
		write(0, "\a", 1);
	else if (mod == 0)
		hist = gsh_r_hist_add_elem(hist);
	else if (mod == 1)
		hist = gsh_r_hist_rewrite_elem(str, hist);
	else if (mod == 2 || mod == 3)
		return (gsh_r_browse_history(mod, &hist, str));
	else if (mod == -1)
	{
		gsh_r_remove_history(hist);
		hist = NULL;
	}
	return (NULL);
}
