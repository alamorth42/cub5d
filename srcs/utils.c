/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:30:49 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:18:34 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			maga(char *line)
{
	int		i;

	i = 0;
	while (line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	return (i);
}

void		mfga(t_game *g, char *tmp, int x, int y)
{
	if (ft_strchr("NSWE", tmp[x]))
	{
		g->pos_x = x + 0.5;
		g->pos_y = y + 0.5;
		set_direction(g, tmp[x]);
		tmp[x] = '0';
	}
}

/*
** set_direction depending letter
*/

void		set_direction(t_game *g, char c)
{
	if (c == 'E')
	{
		g->dir_x = 1;
		g->dir_y = 0;
		g->plane_x = 0;
		g->plane_y = -1;
	}
	else if (c == 'N')
	{
		g->dir_x = 0;
		g->dir_y = -1;
		g->plane_x = -1;
		g->plane_y = 0;
	}
	else
		set_direction2(g, c);
}

void		set_direction2(t_game *g, char c)
{
	if (c == 'W')
	{
		g->dir_x = -1;
		g->dir_y = 0;
		g->plane_x = 0;
		g->plane_y = 1;
	}
	else
	{
		g->dir_x = 0;
		g->dir_y = 1;
		g->plane_x = 1;
		g->plane_y = 0;
	}
}

/*
** parse path and floor/ceiling colors
*/

int			parse_path2(t_game *g, char *line)
{
	if ((line[0] == 'E' && line[1] == 'A')
		&& !(g->path_textures[3] = ft_substr(line,
			maga(line), ft_strlen(line))))
		return (0);
	else if ((line[0] == 'S' && line[1] == ' ')
		&& !(g->path_textures[4] = ft_substr(line,
			maga(line), ft_strlen(line))))
		return (0);
	else if ((line[0] == 'F' && line[1] == ' ')
		&& !parse_col(line, &(g->col_floor_hex)))
		return (0);
	else if ((line[0] == 'C' && line[1] == ' ')
		&& !parse_col(line, &(g->col_ceiling_hex)))
		return (0);
	return (1);
}
