/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:26:49 by dlinkin           #+#    #+#             */
/*   Updated: 2018/04/25 18:26:51 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**		CREATE PIPELINE (or not) AND CHCK REDIRECTIONS
**
**		pps[0] - total number of pipes,
**		pps[1] - position in pipe's chain,
**		pps[2] - redirection true/false.
*/

static void	gsh_count_pipes(t_orba **z, int *pps)
{
	int		ttl;

	ttl = 0;
	while (*z)
	{
		if ((*z)->red)
			pps[2] |= 1;
		if ((*z)->tok == 'p')
			ttl++;
		else if ((*z)->tok == 'e' || (*z)->tok == 'o' || (*z)->tok == 'a')
			break ;
		z++;
	}
	if (!pps[0] && ttl)
		pps[0] = ttl;
	if (pps[0] && !ttl)
		pps[1] = END_PPL;
	else if (pps[0] != ttl)
		pps[1] = MIDDLE_PPL;
	else if (pps[0] && pps[0] == ttl)
		pps[1] = BEGIN_PPL;
	else
		pps[1] = 0;
}

static int	gsh_rewind(t_orba ***z)
{
	if ((**z)->tok == 'e' || (**z)->tok == 'p')
	{
		(*z)++;
		return (1);
	}
	else if (((**z)->tok == 'a' && ((*z)++) && ft_atoi(gsh_get_env("?")))
		|| ((**z)->tok == 'o' && ((*z)++) && !ft_atoi(gsh_get_env("?"))))
	{
		while (**z && (**z)->tok != 'o' && (**z)->tok != 'a'
			&& (**z)->tok != 'e')
			(*z)++;
		return (1);
	}
	return (0);
}

void		gsh_cycle(t_orba **z, int *pps, int *fds, int *cp)
{
	while (*z)
	{
		if (gsh_rewind(&z))
			continue ;
		gsh_count_pipes(z, pps);
		if (fds == NULL && pps[0])
			gsh_open_close_pipes(&fds, &cp, pps[0] * 2, 1);
		if (pps[1] > 1)
			fds += 2;
		if (pps[2] && pps[1] < 2)
			gsh_open_files(z);
		if (gsh_seek(*z, pps, fds) > 255)
			break ;
		if (pps[2])
			gsh_close_files(*z, pps);
		z++;
		if (fds && (!*z || (*z)->tok == 'e' || (*z)->tok == 'a'
			|| (*z)->tok == 'o'))
		{
			gsh_open_close_pipes(&fds, &cp, pps[0] * 2, 0);
			pps[0] = 0;
			pps[1] = 0;
			pps[2] = 0;
		}
	}
}
