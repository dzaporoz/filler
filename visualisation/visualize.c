/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:57:12 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/08 15:56:20 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualize.h"
#include "../libft/libft.h"

static void	log_str(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

static void	read_board_params(char *str, int pos, int *a, int *b)
{
	if (!(*a))
	{
		*a = ft_atoi(&str[pos]);
		while (ft_isdigit(str[pos]))
			pos++;
		*b = ft_atoi(&str[pos]);
	}
}

static void	read_players(char *str, t_field_data *data)
{
	char	*player;
	int		n;

	n = 0;
	if (ft_strstr(str, "$$$ exec p"))
	{
		while (str[n])
			n++;
		while (str[n] != '[' && str[n] != '/')
			n--;
		player = ft_strdup(&str[n] + 1);
		player[ft_strlen(player) - 1] = '\0';
		if (str[10] == '1')
			data->player1 = player;
		else
			data->player2 = player;
	}
}

static void	print_result(char *str, int fd, t_field_data *data)
{
	int		o_res;
	int		x_res;
	char	*line;

	o_res = ft_atoi(&str[9]);
	free(str);
	get_next_line(0, &line);
	x_res = ft_atoi(&line[9]);
	write(fd, line, ft_strlen(line));
	free(line);
	write(1, "\n  ", 1);
	line = (o_res > x_res) ? (ft_strjoin(COLOR_REDY, data->player1)) :
		(ft_strjoin(COLOR_BLUE, data->player2));
	write(1, line, 15);
	write(1, COLOR_RESET " win!\n\n", 13);
	close(fd);
	free(data->player1);
	free(data->player2);
	exit(0);
}

int			main(void)
{
	int				fd;
	char			*str;
	t_field_data	data;

	ft_bzero(&data, sizeof(t_field_data));
	fd = open("game_log.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXO | S_IRWXU);
	while (get_next_line(0, &str) > 0)
	{
		log_str(str, fd);
		read_players(str, &data);
		if (ft_strstr(str, "Plateau"))
		{
			read_board_params(str, 8, &data.field_height, &data.field_width);
			free(str);
			get_next_line(0, &str);
			log_str(str, fd);
			free(str);
			print_board(data, fd);
		}
		else if (ft_strstr(str, "== O fin:"))
			print_result(str, fd, &data);
		else
			free(str);
	}
	return (0);
}
