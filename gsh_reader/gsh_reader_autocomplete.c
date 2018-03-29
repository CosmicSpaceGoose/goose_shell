/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_autocomplete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:32:41 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/29 18:32:43 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_reader.h"
#include "gsh_core.h"

void	gsh_r_autocomplete(char *out, t_pos *pos)
{
	extern t_fptr	g_builtin[8];

	ft_dprintf(2, "%s %zu %s\n", out, pos->kur, (g_builtin[0]).name);
}