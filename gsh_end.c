/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:56:32 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/14 16:56:33 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

void	gsh_save_history(uint32_t app)
{
	t_hist	*hist;
	int		file;
	int		flags;
	int		size;

	if (!(hist = gsh_r_history_bucket(RETURN, NULL)))
		return ;
	flags = O_WRONLY | O_CREAT;
	if (app)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	if ((file = open(gsh_get_env("HISTFILE"), flags, S_IWUSR | S_IRUSR)) == -1)
		return ;
	size = ft_atoi(gsh_get_env("HISTFILESIZE"));
	while (hist->prv && (size--))
		hist = hist->prv;
	while (hist && hist->str)
	{
		ft_putendl_fd(hist->str, file);
		hist = hist->nxt;
	}
	close(file);
}

void	gsh_end(void)
{
	extern uint32_t	g_opt_n;

	if (g_opt_n & GRAPHICS)
		exit_draw();
	gsh_delete_hash_table();
	if (g_opt_n & SAVE_HIST)
		gsh_save_history(g_opt_n & APPND_HIST);
	gsh_r_history_bucket(ERASE, NULL);
	gsh_bucket(FREE_ALL, 0);
}
