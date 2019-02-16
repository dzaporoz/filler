/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:55:36 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/08 16:35:15 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "filler.h"

static void	free_matrix(t_player *data)
{
	char **point;

	point = data->field;
	while (point[0])
	{
		free(point[0]);
		point++;
	}
	free(data->field);
	point = data->figure;
	while (point[0])
	{
		free(point[0]);
		point++;
	}
	free(data->figure);
}

static void	play(char pl1, char pl2)
{
	t_player			play_data;
	char				*str;
	int					retur;
	static t_strategy	logic_data;

	ft_bzero(&play_data, sizeof(struct s_player));
	play_data.pl1 = pl1;
	play_data.pl2 = pl2;
	while (1)
	{
		if (get_next_line(0, &str) < 1)
			return ;
		if (ft_strstr(str, "Plateau"))
			ft_read_board(&play_data, str);
		else if (ft_strstr(str, "Piece"))
		{
			ft_read_figure(&play_data, str);
			retur = go_to_enemy_strategy(&play_data, &logic_data);
			free_matrix(&play_data);
			if (!retur)
				return ;
		}
		else
			free(str);
	}
}

int			main(void)
{
	char *str;

	str = NULL;
	if (get_next_line(0, &str) > 0 && ft_strlen(str) > 20 && ft_strstr(str,
				"$$$ exec p") && (str[10] == '1' || str[10] == '2'))
	{
		(str[10] == '1') ? play('O', 'X') : play('X', 'O');
		free(str);
	}
	else if (errno)
	{
		if (!errno)
			errno = 22;
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		perror("Filler error");
	}
	return (0);
}
