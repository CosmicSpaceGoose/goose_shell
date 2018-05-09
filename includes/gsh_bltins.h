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

const t_fptr	g_builtin[11] = {
	{"echo", gsh_echo},
	{"cd", gsh_cd},
	{"env", gsh_env},
	{"setenv", gsh_setenv},
	{"unsetenv", gsh_unsetenv},
	{"exit", gsh_exit},
	{"help", gsh_help},
	{"history", gsh_history},
	{"set", gsh_set},
	{"unset", gsh_unset},
	{NULL, NULL}
};

#endif
