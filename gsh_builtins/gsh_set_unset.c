/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_set_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 17:00:34 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/08 17:00:35 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static int	gsh_list_shvar(void)
{
	char	**environ;

	if ((environ = gsh_bucket(RETURN_ENV, 0)))
	{
		while (*environ)
		{
			ft_putendl(*environ);
			environ++;
		}
	}
	if ((environ = gsh_bucket(RETURN_SH, 0)))
	{
		while (*environ)
		{
			ft_putendl(*environ);
			environ++;
		}
	}
	return (0);
}

int			gsh_set(char **av)
{
	int i;

	if (!*av)
		return (gsh_list_shvar());
	i = 0;
	while (av[i])
		i++;
	if (ft_strchr(*av, '='))
	{
		ft_dprintf(2, "%s%s\n", "set: Nonvalid name: ", *av);
		return (1);
	}
	if (i > 2)
	{
		ft_dprintf(2, "%s", "set: Too many arguments.\n");
		return (1);
	}
	else if (i == 1)
		set_add_env(*av, "", SH);
	else
		set_add_env(*av, *(av + 1), SH);
	return (0);
}

int			gsh_unset(char **av)
{
	int		i;
	char	**environ;

	if (!*av)
	{
		ft_dprintf(2, "%s", "unsetenv: Too few arguments.\n");
		return (1);
	}
	while (*av)
	{
		if ((i = set_brwse_env(*av, SH)) != -1)
		{
			environ = gsh_bucket(RETURN_SH, 0);
			free(environ[i]);
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
		}
		av++;
	}
	return (0);
}
