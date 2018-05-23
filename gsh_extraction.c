/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_extraction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:29:31 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/23 14:29:32 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

void		gsh_extraction(char **line, int err)
{
	char	*tmp;
	size_t	size;

	if (err == 1)
	{
		gsh_reader(&tmp, write(0, "> ", 2));
		size = ft_strlen(*line);
		*line = ft_realloc(size + ft_strlen(tmp), size, *line);
		ft_strcat(*line, tmp);
		free(tmp);
	}
	else if (err == 2)
	{
		gsh_reader(&tmp, write(0, "quot ", 5));
		size = ft_strlen(*line);
		*line = ft_realloc(size + ft_strlen(tmp) + 1, size, *line);
		ft_strcat(*line, "\n");
		ft_strcat(*line, tmp);
		free(tmp);
	}
}

int			gsh_chaek_extr(char *line)
{
	char	*ptr;
	int		chk[2];

	*chk = 0;
	chk[1] = 0;
	if ((ptr = ft_strrchr(line, '\\')) && *(ptr + 1) == '\0'
		&& *(ptr - 1) != '\\')
		return (1);
	while (*line)
	{
		if (*line == '\\')
			line++;
		else if (*line == '\'' && !chk[1])
			*chk ^= 1;
		else if (*line == '\"' && !*chk)
			chk[1] ^= 1;
		line++;
	}
	if (*chk || chk[1])
		return (2);
	return (0);
}
