/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_env_process_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 12:28:50 by dlinkin           #+#    #+#             */
/*   Updated: 2018/02/14 12:28:51 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static int	env_unset(char ***av, char *c)
{
	*c = ***av;
	(*av)++;
	if (!**av)
		return (2);
	gsh_unsetenv(*av);
	return (-1);
}

static int	env_bue(char ***av, char *c, char *path)
{
	(**av)++;
	if (!***av || ***av == 'i')
		gsh_bucket(FREE, 0);
	else if (***av == 'u')
		return (env_unset(av, c));
	else if (***av == 'P')
	{
		*c = ***av;
		(*av)++;
		if (!**av)
			return (2);
		ft_strcpy(path, **av);
	}
	else if (***av == '-')
	{
		(*av)++;
		return (0);
	}
	else
	{
		*c = ***av;
		return (1);
	}
	return (-1);
}

int			env_read_flags(char ***av, char *c, char *path)
{
	int rat;

	while (**av)
	{
		if (***av == '-')
		{
			rat = env_bue(av, c, path);
			if (rat > -1)
				return (rat);
		}
		else
			break ;
		(*av)++;
	}
	return (0);
}
