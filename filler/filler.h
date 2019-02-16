/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:54:22 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/07 18:55:18 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_FILLER_H
# define FILLER_FILLER_H

# include <errno.h>
# include "../libft/libft.h"

# define ABS(x) (((x) < 0) ? ((x) * -1) : (x))

typedef struct	s_strategy
{
	int x_min;
	int y_min;
	int dist_min;
}				t_strategy;

typedef struct	s_player
{
	char		pl1;
	char		pl2;
	int			brd_w;
	int			brd_h;
	char		**field;
	int			fig_w;
	int			fig_h;
	char		**figure;
}				t_player;

int				ft_read_figure(t_player *play_data, char *str);
int				ft_read_board(t_player *play_data, char *str);
int				go_to_enemy_strategy(t_player *play_data,
		t_strategy *logic_data);

#endif
