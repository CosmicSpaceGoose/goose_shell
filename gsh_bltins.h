/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_bltins.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:23:27 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/14 14:23:29 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_BLTINS_H
# define GSH_BLTINS_H

t_fptr	g_builtin[8] = {
	{"echo", gsh_echo},
	{"cd", gsh_cd},
	{"env", gsh_env},
	{"setenv", gsh_setenv},
	{"unsetenv", gsh_unsetenv},
	{"exit", gsh_exit},
	{"help", gsh_help},
	{NULL, NULL}
};

#endif
