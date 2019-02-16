/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_board.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:38:47 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/12/06 18:38:51 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualize.h"
#include "../libft/libft.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*fresh;
	size_t	len;

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		if ((fresh = (char*)malloc(len + 1)))
		{
			len = ft_strlen(s1) + ft_strlen(s2);
			ft_bzero(fresh, len + 1);
			fresh = ft_strcat(fresh, s1);
			fresh = ft_strcat(fresh, s2);
			free(s1);
			return (fresh);
		}
		else
			return (NULL);
	}
	else if (s1)
		return (ft_strdup(s1));
	else if (s2)
		return (ft_strdup(s2));
	else
		return (NULL);
}

static char	*ft_join_minus(size_t len, char *str)
{
	char *ch;
	char *new;

	if (len <= 0)
		return (str);
	ch = "----------------------------------------";
	while (len)
	{
		if (len <= 40)
		{
			new = ft_strjoin(str, &ch[40 - len]);
			free(str);
			new = ft_strjoin_free(new, "\n");
			return (new);
		}
		new = ft_strjoin(str, ch);
		free(str);
		str = new;
		len -= 40;
	}
	return (str);
}

static char	*add_element(char c, char *str)
{
	if (c == 'O')
		return (ft_strjoin_free(str, COLOR_REDY "\u2588" COLOR_RESET));
	else if (c == 'o')
		return (ft_strjoin_free(str, COLOR_RED "\u2588" COLOR_RESET));
	else if (c == 'X')
		return (ft_strjoin_free(str, COLOR_BLUE "\u2588" COLOR_RESET));
	else if (c == 'x')
		return (ft_strjoin_free(str, COLOR_CYAN "\u2588" COLOR_RESET));
	else
		return (ft_strjoin_free(str, " "));
}

void		print_board(t_field_data game_data, int fd)
{
	int		n;
	char	*str;
	char	*str2;
	char	*tmp;

	n = -1;
	str2 = strdup("");
	while (++n < game_data.field_height)
	{
		get_next_line(0, &str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		tmp = ft_strchr(str, ' ');
		str2 = ft_strjoin_free(str2, "|");
		while (*(++tmp) != '\0')
			str2 = add_element(*tmp, str2);
		str2 = ft_strjoin_free(str2, "|\n");
		free(str);
	}
	str2 = ft_strjoin_free(str2, " ");
	str2 = ft_join_minus(game_data.field_width, str2);
	system("clear");
	write(1, str2, ft_strlen(str2));
	free(str2);
}
