/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 17:32:34 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/08 17:32:36 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		check_push(t_player *play_data, int pos_y, int pos_x)
{
	int figure_y;
	int figure_x;
	int possibility_flag;

	possibility_flag = 0;
	figure_y = -1;
	while (++figure_y < play_data->fig_h)
	{
		figure_x = -1;
		while (++figure_x < play_data->fig_w)
		{
			if (play_data->figure[figure_y][figure_x] == 1 &&
				play_data->field[pos_y + figure_y][pos_x + figure_x] == 2)
			{
				possibility_flag++;
				if (possibility_flag > 1)
					return (0);
			}
			else if (play_data->figure[figure_y][figure_x] == 1 &&
					play_data->field[pos_y + figure_y][pos_x + figure_x] == 4)
				return (0);
		}
	}
	return (possibility_flag);
}

int		put_figure(int y, int x)
{
	char *str;

	ft_putstr((str = ft_itoa(y)));
	ft_putchar(' ');
	free(str);
	ft_putendl((str = ft_itoa(x)));
	free(str);
	return (1);
}

void	get_min_dist(t_player *play_data, t_strategy *logic_data,
		int y, int x)
{
	int x_counter;
	int y_counter;
	int y_max;
	int x_max;

	y_max = play_data->brd_h;
	x_max = play_data->brd_w;
	y_counter = -1;
	while (++y_counter < y_max)
	{
		x_counter = -1;
		while (++x_counter < x_max)
			if (play_data->field[y_counter][x_counter] == 4)
				if ((ABS(y - y_counter) + ABS(x - x_counter))
					< logic_data->dist_min)
					logic_data->dist_min = (ABS(y - y_counter) +
											ABS(x - x_counter));
	}
}

void	get_manhattan_distance(t_player *play_data, t_strategy
*logic_data, int y, int x)
{
	int x_counter;
	int y_counter;
	int y_max;
	int x_max;
	int figure_dist;

	figure_dist = logic_data->dist_min;
	y_max = play_data->fig_h;
	x_max = play_data->fig_w;
	y_counter = -1;
	while (++y_counter < y_max)
	{
		x_counter = -1;
		while (++x_counter < x_max)
			if (play_data->figure[y_counter][x_counter] == 1)
				get_min_dist(play_data, logic_data, y_counter
													+ y, x_counter + x);
	}
	if (logic_data->dist_min < figure_dist)
	{
		logic_data->y_min = y;
		logic_data->x_min = x;
	}
}

int		go_to_enemy_strategy(t_player *play_data,
								t_strategy *logic_data)
{
	int x_counter;
	int y_counter;
	int y_max;
	int x_max;

	y_max = play_data->brd_h - play_data->fig_h;
	x_max = play_data->brd_w - play_data->fig_w;
	logic_data->x_min = play_data->brd_w;
	logic_data->y_min = play_data->brd_h;
	y_counter = -1;
	logic_data->dist_min = play_data->brd_w + play_data->brd_h;
	while (++y_counter <= y_max)
	{
		x_counter = -1;
		while (++x_counter <= x_max)
			if (check_push(play_data, y_counter, x_counter))
			{
				get_manhattan_distance(play_data, logic_data,
									y_counter, x_counter);
			}
	}
	if (logic_data->dist_min != play_data->brd_w + play_data->brd_h)
		return (put_figure(logic_data->y_min, logic_data->x_min));
	write(1, "0 0\n", 4);
	return (0);
}
