/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:28:48 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/18 15:28:49 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

char		*gsh_get_env(char *name)
{
	char		*env;
	char		*ptr;
	char		**environ;
	int			i;

	i = 0;
	if ((environ = *gsh_bucket(0, 0)))
		while (environ[i])
		{
			ptr = ft_strchr(environ[i], '=');
			env = ft_strsub(environ[i], 0, ptr - environ[i]);
			if (ft_strcmp(name, env) == 0)
			{
				free(env);
				return (ptr + 1);
			}
			free(env);
			i++;
		}
	return (NULL);
}

int			gsh_unsetenv(char **av)
{
	int		i;
	char	***environ;

	if (!*av)
	{
		ft_dprintf(2, "%s", "unsetenv: Too few arguments.\n");
		return (1);
	}
	while (*av)
	{
		if ((i = set_brwse_env(*av)) == -1)
		{
			av++;
			continue ;
		}
		environ = gsh_bucket(0, 0);
		free((*environ)[i]);
		while ((*environ)[i])
		{
			(*environ)[i] = (*environ)[i + 1];
			i++;
		}
		av++;
	}
	return (0);
}
