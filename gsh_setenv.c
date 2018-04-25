/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:35:07 by dlinkin           #+#    #+#             */
/*   Updated: 2018/02/14 14:35:09 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

int			set_brwse_env(char *name)
{
	char		**environ;
	char		*env;
	char		*ptr;
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
				return (i);
			}
			free(env);
			i++;
		}
	return (-1);
}

static void	set_new_env(char *env)
{
	char	**new_env;
	char	**environ;
	int		i;

	i = 0;
	if ((environ = *gsh_bucket(0, 0)))
		while (environ[i])
			i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	new_env[i + 1] = NULL;
	new_env[i] = ft_strdup(env);
	while (i)
	{
		new_env[i - 1] = ft_strdup(environ[i - 1]);
		i--;
	}
	if (environ)
		gsh_bucket(2, 0);
	gsh_bucket(1, new_env);
}

void		set_add_env(char *name, char *value)
{
	int		i;
	char	*env;
	char	*ptr;
	char	***environ;

	ptr = ft_strjoin(name, "=");
	env = ft_strjoin(ptr, value);
	free(ptr);
	if ((i = set_brwse_env(name)) == -1)
		set_new_env(env);
	else
	{
		environ = gsh_bucket(0, 0);
		free((*environ)[i]);
		(*environ)[i] = ft_strdup(env);
	}
	free(env);
}

int			gsh_setenv(char **av)
{
	int i;

	if (!*av)
		return (gsh_list_env());
	i = 0;
	while (av[i])
		i++;
	if (ft_strchr(*av, '='))
	{
		ft_dprintf(2, "%s%s\n", "setenv: Nonvalid name: ", *av);
		return (1);
	}
	if (i > 2)
	{
		ft_dprintf(2, "%s", "setenv: Too many arguments.\n");
		return (1);
	}
	else if (i == 1)
		set_add_env(*av, "");
	else
		set_add_env(*av, *(av + 1));
	return (0);
}
