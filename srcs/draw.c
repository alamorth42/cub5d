/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 20:42:13 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** draw_floor_and_ceiling
*/

void		draw_floor_and_ceiling(t_game *g, int x, int y)
{
	g->img_buffer[y * g->res_x + x] = g->col_ceiling_hex;
	g->img_buffer[ft_min(g->res_y - y, g->res_y)
	* g->res_x + x] = g->col_floor_hex;
}

/*
** draw_wall_col
*/

void		draw_wall_col(t_game *g, int x, int y, int wall_pxl_high)
{
	int tex_y;

	if (g->sides[x] == 0 || g->sides[x] == 1)
		tex_y = (((float)y * 2. - (float)g->res_y + (float)wall_pxl_high)
		* (float)(64 / 2) / (float)wall_pxl_high);
	else
		tex_y = (((float)y * 2. - (float)g->res_y + (float)wall_pxl_high)
		* (float)(64 / 2) / (float)wall_pxl_high);
	g->img_buffer[y * g->res_x + x] =
	g->data_textures[g->sides[x]][(int)tex_y * 64 + g->tex_x[x]];
}

/*
** draw_img_buffer
*/

int			draw_img_buffer(t_game *g)
{
	int	x;
	int	y;
	int	wall_pxl_high;
	int	wall_start;
	int	wall_end;

	x = 0;
	while (x < g->res_x - 1)
	{
		wall_pxl_high = abs((int)(g->res_y / g->distances[x]));
		wall_start = ft_max((int)(g->res_y / 2 - wall_pxl_high / 2), 0);
		wall_end = ft_min((int)(g->res_y / 2 + wall_pxl_high / 2), g->res_y);
		y = 0;
		while (y < (int)wall_start)
			draw_floor_and_ceiling(g, x, y++);
		while (y < (int)wall_end)
			draw_wall_col(g, x, y++, wall_pxl_high);
		x++;
	}
	return (1);
}

/*
** draw_sprite
*/

void		draw_sprite(t_game *g, t_sprite *s)
{
	int			x;
	int			y;

	x = -1;
	while (s->x_start + ++x < s->x_end)
	{
		if (s->x_start + x >= s->first_hit_col && s->x_start +
		x <= s->last_hit_col)
		{
			s->tex_x = (int)(256 * ((s->x_start + x) - (-s->width_in_px /
			2 + s->sprite_screen_x)) * 512 / s->width_in_px) / 256;
			y = -1;
			while (s->y_start + ++y < s->y_end)
			{
				s->tex_y = ((((s->y_start + y) * 256 - g->res_y * 128 +
				s->height_in_px * 128) * 512) / s->height_in_px) / 256;
				if (g->data_textures[4][(int)s->tex_y * 512 + s->tex_x]
				!= g->data_textures[4][0])
					g->img_buffer[(s->y_start + y) * g->res_x + (s->x_start +
					x)] = g->data_textures[4][(int)s->tex_y * 512 + s->tex_x];
			}
		}
	}
}

/*
** draw_sprites
*/

void		draw_sprites(t_game *g)
{
	t_sprite	*s;
	float		inverse_coef;

	sort_sprites(g);
	s = g->sprites;
	inverse_coef = 1.0 / (g->plane_x * g->dir_y - g->plane_y * g->dir_x);
	while (s)
	{
		if (s->order > 0)
		{
			prepare_sprite(g, s, inverse_coef);
			draw_sprite(g, s);
			s->order = 0;
		}
		s = s->next;
	}
}
