/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 04:28:12 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** init | count_sprites
*/

int			count_sprites(t_game *g)
{
	int x;
	int y;
	int nb_sprite;

	y = -1;
	nb_sprite = 0;
	while (++y < g->map_y_len)
	{
		x = -1;
		while (++x < g->x_len_for_y[y])
		{
			if (g->map[y][x] == '2')
				nb_sprite += 1;
		}
	}
	return (nb_sprite);
}

/*
** loop | store hit col on res_x
*/

int			get_last_order(t_sprite *sprites)
{
	t_sprite	*s;
	int			order;

	s = sprites;
	order = 0;
	while (s)
	{
		if (s->order > order)
			order = s->order;
		s = s->next;
	}
	return (order + 1);
}

/*
** store hit col on res_x
*/

void		store_sprite_hit_col(t_game *g, int hit_col)
{
	t_sprite	*s;
	int			i;

	s = g->sprites;
	i = 0;
	while (s)
	{
		if (g->map_x == (int)s->pos_x && g->map_y == (int)s->pos_y)
		{
			if (s->order == 0)
			{
				s->first_hit_col = hit_col;
				s->distance = (s->pos_x - g->pos_x) * (s->pos_x - g->pos_x)
					+ (s->pos_y - g->pos_y) * (s->pos_y - g->pos_y);
				s->order = get_last_order(g->sprites);
			}
			else
				s->last_hit_col = hit_col;
		}
		s = s->next;
	}
}

/*
** loop | swap data
*/

void		swap_sprite_data(t_sprite *s1, t_sprite *s2)
{
	float	s2_pos_x;
	float	s2_pos_y;
	float	s2_distance;
	int		s2_i[3];

	s2_pos_x = s2->pos_x;
	s2_pos_y = s2->pos_y;
	s2_distance = s2->distance;
	s2_i[0] = s2->order;
	s2_i[1] = s2->first_hit_col;
	s2_i[2] = s2->last_hit_col;
	s2->pos_x = s1->pos_x;
	s2->pos_y = s1->pos_y;
	s2->distance = s1->distance;
	s2->order = s1->order;
	s2->first_hit_col = s1->first_hit_col;
	s2->last_hit_col = s1->last_hit_col;
	s1->pos_x = s2_pos_x;
	s1->pos_y = s2_pos_y;
	s1->distance = s2_distance;
	s1->order = s2_i[0];
	s1->first_hit_col = s2_i[1];
	s1->last_hit_col = s2_i[2];
}

/*
** loop | sort
*/

void		sort_sprites(t_game *g)
{
	t_sprite *s;
	t_sprite *elem;

	s = g->sprites;
	if (!s->next)
		return ;
	while (s)
	{
		elem = s;
		while (elem)
		{
			if (elem->distance < elem->next->distance)
				if (elem->next)
					swap_sprite_data(elem, elem->next);
			elem = elem->next;
		}
		s = s->next;
	}
}
