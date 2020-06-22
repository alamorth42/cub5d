/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 18:52:32 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** init | push distance
*/

void		push_distance(t_game *g, t_sprite *new_s)
{
	t_sprite *s;
	t_sprite *prev_s;

	s = g->sprites;
	prev_s = NULL;
	while (s)
	{
		if (new_s->distance > s->distance)
		{
			if (prev_s)
				prev_s->next = new_s;
			new_s->next = s;
			if (!prev_s)
				g->sprites = new_s;
			return ;
		}
		prev_s = s;
		s = s->next;
	}
	prev_s->next = new_s;
}

/*
** init | create sorted linked list
*/

int			sort_and_add_sprite(t_game *g, int x, int y)
{
	t_sprite *new_s;

	if (!(new_s = (t_sprite *)malloc(sizeof(t_sprite))))
		return (0);
	new_s->pos_x = x + .5;
	new_s->pos_y = y + .5;
	new_s->distance = ((x + .5) - g->pos_x) * ((x + .5) - g->pos_x)
	+ ((y + .5) - g->pos_y) * ((y + .5) - g->pos_y);
	new_s->next = NULL;
	new_s->order = 0;
	if (!g->sprites)
		g->sprites = new_s;
	else
		push_distance(g, new_s);
	return (1);
}

/*
** init | parse_sprites
*/

int			parse_sprites(t_game *g)
{
	int x;
	int y;

	y = -1;
	while (++y < g->map_y_len)
	{
		x = -1;
		while (++x < g->x_len_for_y[y])
		{
			if (g->map[y][x] == '2' && !sort_and_add_sprite(g, x, y))
				return (0);
		}
	}
	return (1);
}

int			detect_sprites(t_game *g)
{
	int		nb_sprite;

	nb_sprite = 0;
	if (!(nb_sprite = count_sprites(g)))
		return (1);
	return (parse_sprites(g));
}

/*
** loop | prepare sprite drawing
*/

void		prepare_sprite(t_game *g, t_sprite *s, float inverse_coef)
{
	s->dist_x = s->pos_x - g->pos_x;
	s->dist_y = s->pos_y - g->pos_y;
	s->corrected_dist_x = inverse_coef *
		(g->dir_y * s->dist_x - g->dir_x * s->dist_y);
	s->corrected_dist_y = inverse_coef * (-g->plane_y *
		s->dist_x + g->plane_x * s->dist_y);
	s->sprite_screen_x = (int)((g->res_x / 2) *
		(1 + s->corrected_dist_x / s->corrected_dist_y));
	s->height_in_px = abs((int)((float)g->res_y / s->corrected_dist_y));
	s->width_in_px = abs((int)((float)g->res_y / s->corrected_dist_y));
	s->y_start = ft_max((int)(g->res_y / 2 - s->height_in_px / 2), 0);
	s->y_end = ft_min((int)(g->res_y /
		2 + s->height_in_px / 2), g->res_y - 1);
	s->x_start = ft_max((int)(-s->width_in_px /
		2 + s->sprite_screen_x), 0);
	s->x_end = ft_min((int)(s->width_in_px /
		2 + s->sprite_screen_x), g->res_x - 1);
}
