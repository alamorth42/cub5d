/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:09:12 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** init game struct
*/

int		init_g(t_game *g, int argc, char **argv)
{
	g->res_x = 0;
	g->res_y = 0;
	g->buffer = NULL;
	g->map_y_len = 0;
	g->x_len_for_y = NULL;
	g->pos_x = 0.0;
	g->pos_y = 0.0;
	g->move_f = 0;
	g->move_b = 0;
	g->move_l = 0;
	g->move_r = 0;
	g->move_rl = 0;
	g->move_rr = 0;
	g->speed = 0.1;
	g->save = 0;
	if (argc == 3 && ft_strcmp("-save", argv[2]))
		return (0);
	else if (argc == 3 && !ft_strcmp("-save", argv[2]))
		g->save = 1;
	g->sprites = NULL;
	return (1);
}

/*
** parse ceiling colors
*/

int		parse_col(char *col, int *dest)
{
	int i;
	int	pos;
	int dec_nb;

	i = -1;
	pos = 1;
	*dest = 0x000000;
	while (col[++i])
	{
		if (ft_isdigit(col[i]))
		{
			dec_nb = ft_atoi(col + i);
			if (dec_nb < 0 || dec_nb > 255)
				return (0);
			i += ft_nbrlen(dec_nb, 10) - 1;
			if (pos == 1)
				*dest += dec_nb * 65536;
			else if (pos == 2)
				*dest += dec_nb * 256;
			else if (pos == 3)
				*dest += dec_nb * 1;
			pos++;
		}
	}
	return (pos == 4 ? 1 : 0);
}

/*
** check map not valid if:
** no positioning
** a 0 in top/bottom y borders
** a 0 in middle y endpoints borders
*/

int		check_if_map_valid(t_game *g)
{
	int x;
	int y;

	if (g->pos_x == 0 && g->pos_y == 0)
		return (0);
	y = -1;
	while (++y < g->map_y_len)
	{
		x = -1;
		while (++x < g->x_len_for_y[y])
		{
			if (y == 0 && g->map[y][x] == '0')
				return (0);
			else if (y == g->map_y_len - 1 && g->map[y][x] == '0')
				return (0);
			else if ((x == 0 || x == g->x_len_for_y[y])
			&& g->map[y][x] == '0')
				return (0);
		}
	}
	return (1);
}

/*
** build map from buffer
** if * positioning just keep the last
*/

int		build_map(t_game *g)
{
	int		buffer_pos;
	int		y;
	char	*tmp;
	int		x;

	buffer_pos = 0;
	if (!(g->map = (char **)malloc(sizeof(char *) * (g->map_y_len))))
		return (0);
	y = -1;
	while (++y < g->map_y_len)
	{
		if (!(tmp = ft_substr(g->buffer, buffer_pos, g->x_len_for_y[y])))
			return (0);
		if ((tmp[0] == '0' || tmp[g->x_len_for_y[y] - 1] == '0')
		&& (g->map_y_len = y))
			return (0);
		x = -1;
		while (tmp[++x])
			mfga(g, tmp, x, y);
		if (!(g->map[y] = ft_strdup(tmp)))
			return (0);
		ft_strdel(&tmp);
		buffer_pos += g->x_len_for_y[y];
	}
	return (check_if_map_valid(g));
}
