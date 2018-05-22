/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_graphics.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:25:01 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/17 14:25:03 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_GRAPHICS_H
# define GSH_GRAPHICS_H

/*
**	must be equal with BLTN_NUM in gsh_builtins.h
*/

# define BLTN_NUM 12

const char			*g_help[12] = {
	" - change working directory",
	" - print some text in terminal",
	" - env managment & run program",
	" - exit goose_shell",
	" - print this help massege",
	" - modificate shell history",
	" - set local variable",
	" - set environment variable",
	" - change shell behavior",
	" - delete local variable",
	" - delete environment variable",
	0
};

#endif
