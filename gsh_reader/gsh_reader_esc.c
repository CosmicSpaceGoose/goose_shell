/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_esc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 13:59:59 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/25 14:00:00 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_reader.h"

static void	gsh_r_arrows(char c, t_pos *pos)
{
	size_t	new;

	if (c == 'C')
		gsh_r_shift_right(pos);
	else if (c == 'D')
		gsh_r_shift_left(pos);
	else if (c == 'A')
	{
		if (pos->kur - pos->col > pos->len)
			new = 0;
		else
			new = pos->kur - pos->col;
		while (pos->kur != new)
			gsh_r_shift_left(pos);
	}
	else if (c == 'B')
	{
		if (pos->kur + pos->col > pos->len)
			new = pos->len;
		else
			new = pos->kur + pos->col;
		while (pos->kur != new)
			gsh_r_shift_right(pos);
	}
}

void		gsh_r_home_end(char c, t_pos *pos)
{
	if (c == 'H')
		while (pos->kur)
			gsh_r_shift_left(pos);
	else if (c == 'F')
		while (pos->kur < pos->len)
			gsh_r_shift_right(pos);
}

static void	gsh_r_pgup_pgdown(char c, char *out, t_pos *pos)
{
	t_hist *elem;

	if ((elem = gsh_r_history_bucket(c - 51, out)))
	{
		while (pos->kur)
			gsh_r_shift_left(pos);
		tputs(tgetstr("cd", 0), 1, ft_putint);
		ft_bzero((void *)out, LINE_SIZE);
		if (elem->tmp)
			ft_strcpy(out, elem->tmp);
		else
			ft_strcpy(out, elem->str);
		tputs(out, 1, ft_putint);
		pos->len = ft_strlen(out);
		pos->kur = pos->len;
	}
}

static void	gsh_r_alt_esq(t_ych u, char *out, t_pos *pos)
{
	if (!u.c[1])
	{
		ft_bzero((void *)out, LINE_SIZE);
		while (pos->kur)
			gsh_r_shift_left(pos);
		pos->len = 0;
		tputs(tgetstr("cd", 0), 1, ft_putint);
	}
	else if (u.d == K_ALT_RGHT)
	{
		while (pos->kur != pos->len && out[pos->kur] == 32)
			gsh_r_shift_right(pos);
		while (pos->kur != pos->len && out[pos->kur] != 32)
			gsh_r_shift_right(pos);
	}
	else if (u.d == K_ALT_LFT)
	{
		while (pos->kur && out[pos->kur - 1] == 32)
			gsh_r_shift_left(pos);
		while (pos->kur && out[pos->kur - 1] != 32)
			gsh_r_shift_left(pos);
	}
}

void		gsh_r_esc_seq(t_ych u, char *out, t_pos *pos)
{
	if (u.c[1] == '[')
	{
		if (u.c[2] >= 'A' && u.c[2] <= 'D')
			gsh_r_arrows(u.c[2], pos);
		else if (u.d == K_DEL)
		{
			ft_memmove(out + pos->kur, out + pos->kur + 1, ft_strlen(out)
				- pos->kur + 1);
			tputs(tgetstr("cd", 0), 1, ft_putint);
			tputs(out + pos->kur, 1, ft_putint);
			if (pos->kur + 1 < pos->len)
				tputs(tgoto(tgetstr("LE", 0), 1, pos->len - pos->kur - 1)
					, 1, ft_putint);
			pos->len--;
		}
		else if (u.d == K_HOME || u.d == K_END)
			gsh_r_home_end(u.c[2], pos);
		else if (u.d == K_PG_UP || u.d == K_PG_DWN)
			gsh_r_pgup_pgdown(u.c[2], out, pos);
		else if (u.c[2] == '1')
			gsh_r_cut_copy_paste(u, out, pos);
	}
	else if (!u.c[1] || u.c[1] == '\e')
		gsh_r_alt_esq(u, out, pos);
}
