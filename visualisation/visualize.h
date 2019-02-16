/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualize.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:30:15 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/08 15:55:12 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZE_H
# define VISUALIZE_H

# include <errno.h>
# include <fcntl.h>

# define COLOR_RED		"\033[0;31m"
# define COLOR_REDY		"\033[0;91m"
# define COLOR_BLUE		"\033[0;94m"
# define COLOR_CYAN		"\033[0;36m"
# define COLOR_RESET	"\033[0;0m"

typedef struct	s_field_data
{
	int			field_width;
	int			field_height;
	char		*player1;
	char		*player2;
}				t_field_data;

void			print_board(t_field_data game_data, int fd);

#endif
