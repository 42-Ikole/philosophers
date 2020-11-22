/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 08:23:26 by akramp        #+#    #+#                 */
/*   Updated: 2020/11/20 17:22:34 by ingmar        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/*
** Format and reset codes :P
*/

# define COLOR_RESET 	"\033[37m"
# define BOLD			"\e[1m"
# define ITALIC			"\e[3m"
# define FORMAT_RESET	"\e[0m"

/*
** Colors :3
*/

# define COLOR_RED 		"\033[38;5;196m"
# define COLOR_GREEN	"\033[38;5;46m"
# define COLOR_BLUE 	"\033[38;5;51m"
# define COLOR_BLU		"\033[38;5;190m"
# define COLOR_ORANGE	"\033[38;5;214m"
# define COLOR_PURPLE	"\033[38;5;98m"
# define COLOR_YELLOW	"\033[38;5;220m"
# define COLOR_PINK		"\033[38;5;205m"
# define COLOR_YOS		"\033[38;5;226"

/*
** ingmars eating colors
*/

# define COLOR_EATING	"\033[38;5;113m"
# define COLOR_SLEEPING "\033[38;5;117m"
# define COLOR_PICK_FORK "\033[38;5;218m"
# define COLOR_DROP_FORK "\033[38;5;166m"
# define COLOR_THINKING "\033[38;5;101m"
# define COLOR_APPEAR "\033[38;5;198m"

/*
** Inverted colors :0
*/

# define COLOR_IGREY	"\x1b[40m"
# define COLOR_IRED		"\x1b[41m"
# define COLOR_IGREEN	"\x1b[42m"
# define COLOR_IYELLOW	"\x1b[43m"
# define COLOR_IBLUE	"\x1b[44m"
# define COLOR_IPURPLE	"\x1b[45m"
# define COLOR_ICYAN	"\x1b[46m"
# define COLOR_IWHITE	"\x1b[47m"

#endif
