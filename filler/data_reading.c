/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:55:06 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/08 18:10:53 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	read_board_params(char *str, int pos, int *a, int *b)
{
	*a = ft_atoi(&str[pos]);
	while (ft_isdigit(str[pos]))
		pos++;
	*b = ft_atoi(&str[pos]);
}

static char	*get_board_line(t_player *play_data, char *src)
{
	char			*str;
	unsigned int	n;
	unsigned int	a;

	n = ft_strlen(src);
	str = ((char*)malloc(n));
	a = -1;
	while (++a <= n - 1)
	{
		if (src[a] == '.')
			str[a] = 0;
		else if (src[a] == play_data->pl1 || src[a] ==
				ft_tolower(play_data->pl1))
			str[a] = 2;
		else if (src[a] == play_data->pl2 || src[a] ==
				ft_tolower(play_data->pl2))
			str[a] = 4;
		else
		{
			errno = 22;
			exit(1);
		}
	}
	return (str);
}

static char	*get_figure_line(char *src)
{
	char			*str;
	unsigned int	n;
	unsigned int	a;

	n = ft_strlen(src);
	str = ((char*)malloc(n));
	a = -1;
	while (++a <= n - 1)
	{
		if (src[a] == '.')
			str[a] = 0;
		else
			str[a] = 1;
	}
	free(src);
	return (str);
}

int			ft_read_board(t_player *play_data, char *str)
{
	int		n;
	char	*line;

	if (!play_data->brd_h)
		read_board_params(str, 8, &play_data->brd_h,
			&play_data->brd_w);
	free(str);
	n = -1;
	if (get_next_line(0, &line) < 1)
		return (-1);
	free(line);
	play_data->field = (char**)malloc(sizeof(char*) *
			play_data->brd_h + 1);
	while (++n < play_data->brd_h)
	{
		if (get_next_line(0, &line) < 1)
			return (-1);
		play_data->field[n] = get_board_line(play_data,
				ft_strchr(line, ' ') + 1);
		free(line);
	}
	play_data->field[n] = NULL;
	return (1);
}

int			ft_read_figure(t_player *play_data, char *str)
{
	int		n;
	char	*line;

	n = 6;
	play_data->fig_h = ft_atoi(&str[n]);
	while (ft_isdigit(str[n]))
		n++;
	play_data->fig_w = ft_atoi(&str[n]);
	free(str);
	play_data->figure = (char**)malloc(sizeof(char*) *
			play_data->fig_h + 1);
	n = 0;
	while (n < play_data->fig_h)
	{
		if (get_next_line(0, &line) < 1)
			return (-1);
		play_data->figure[n] = get_figure_line(line);
		n++;
	}
	play_data->figure[n] = NULL;
	return (1);
}
