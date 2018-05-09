/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_sgnl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:24:58 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/14 14:24:59 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_SGNL_H
# define GSH_SGNL_H

const char		*g_sig[32] = {
	"SIGHUP",
	"SIGINT",
	"gsh: quit  ",
	"gsh: illegal instruction  ",
	"gsh: trace trap  ",
	"gsh: abort program  ",
	"gsh: emulate instruction executed  ",
	"gsh: floating-point exception  ",
	"gsh: killed >:[  ",
	"gsh: bus error  ",
	"gsh: segmentation violation  ",
	"gsh: non-existent system call invoked  ",
	"SIGPIPE",
	"SIGALRM",
	"SIGTERM",
	"SIGURG",
	"SIGSTOP",
	"SIGTSTP",
	"SIGCONT",
	"SIGCHLD",
	"SIGTTIN",
	"SIGTTOU",
	"SIGIO",
	"SIGXCPU",
	"SIGXFSZ",
	"SIGVTALRM",
	"SIGPROF",
	"SIGWINCH",
	"SIGINFO",
	"SIGUSR1",
	"SIGUSR2",
	NULL
};

#endif
