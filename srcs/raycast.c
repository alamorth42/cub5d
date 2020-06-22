/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:57 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** compute north and south wall distances
** g->distances[col] = distance in float for hitted wall of this column
** g->hit_wall_x[col] = precicely where the ray hitted the wall (used after
** for texturing) like 0.2 or 0.8 (ranged between 0 and 1)
** g->tex_x[col] = just a cross multiplication on where the ray should hit the
** 64x64 texture
** g->sides[col] = 0 if south / 1 if north
*/

void		get_no_so_distances(t_game *g, int col, int step_x, int side)
{
	g->distances[col] = fabs((g->map_x - g->ray_pos_x
	+ (1 - step_x) / 2) / g->ray_dir_x);
	g->hit_wall_x[col] = (float)g->ray_pos_y + (((float)g->map_x - g->ray_pos_x
	+ (1. - (float)step_x) / 2.) / g->ray_dir_x) * g->ray_dir_y;
	g->hit_wall_x[col] -= (int)g->hit_wall_x[col];
	g->tex_x[col] = (int)(g->hit_wall_x[col] * 64.);
	g->sides[col] = side;
	if (g->ray_dir_x > 0)
	{
		g->tex_x[col] = 64 - g->tex_x[col] - 1;
		g->sides[col] = 1;
	}
}

/*
** compute west and east wall distances
** g->sides[col] = 2 if west / 3 if east
** see get_no_so_distances for detailed informations
*/

void		get_we_ea_distances(t_game *g, int col, int step_y, int side)
{
	g->distances[col] = fabs((g->map_y - g->ray_pos_y
	+ (1 - step_y) / 2) / g->ray_dir_y);
	g->sides[col] = side;
	g->hit_wall_x[col] = (float)g->ray_pos_x + (((float)g->map_y - g->ray_pos_y
	+ (1. - (float)step_y) / 2.) / g->ray_dir_y) * g->ray_dir_x;
	g->hit_wall_x[col] -= (int)g->hit_wall_x[col];
	g->tex_x[col] = (int)(g->hit_wall_x[col] * 64);
	if (g->ray_dir_y < 0)
	{
		g->tex_x[col] = 64 - g->tex_x[col] - 1;
		g->sides[col] = 3;
	}
}

/*
** set_step_xy_move_on_map()
** also computes distance with 1st x and y axis (side_dist) depending on ray_dir
** step_x : -1 means looking toward west / 1 east
** step_y : -1 means looking toward north / 1 south
** cf the E/W/N/S letter placed in the map
*/

void		set_step_xy_move_on_map(t_game *g, int *step_x, int *step_y)
{
	if (g->ray_dir_x < 0)
	{
		*step_x = -1;
		g->side_dist_x = (g->ray_pos_x - g->map_x) * g->delta_dist_x;
	}
	else
	{
		*step_x = 1;
		g->side_dist_x = (g->map_x + 1.0 - g->ray_pos_x) * g->delta_dist_x;
	}
	if (g->ray_dir_y < 0)
	{
		*step_y = -1;
		g->side_dist_y = (g->ray_pos_y - g->map_y) * g->delta_dist_y;
	}
	else
	{
		*step_y = 1;
		g->side_dist_y = (g->map_y + 1.0 - g->ray_pos_y) * g->delta_dist_y;
	}
}

/*
** raycast()
** if side = 0 we hit north/south wall
** else if side = 2 we hit west/east wall
*/

int			raycast(t_game *g, int col)
{
	int		hit;
	int		side;
	int		check;

	set_step_xy_move_on_map(g, &g->step_x, &g->step_y);
	hit = 0;
	side = 0;
	while (hit == 0)
	{
		check = g->side_dist_x < g->side_dist_y;
		g->side_dist_x += check ? g->delta_dist_x : 0.0;
		g->side_dist_y += check ? 0.0 : g->delta_dist_y;
		g->map_x += check ? g->step_x : 0;
		g->map_y += check ? 0 : g->step_y;
		side = check ? 0 : 2;
		if (g->map[g->map_y][g->map_x] == '1')
			hit = 1;
		else if (g->map[g->map_y][g->map_x] == '2')
			store_sprite_hit_col(g, col);
	}
	if (side == 0)
		get_no_so_distances(g, col, g->step_x, side);
	else
		get_we_ea_distances(g, col, g->step_y, side);
	return (1);
}

/*
** g->camera_x compris [-1;1] correspond a la position relative de la colonne
** par rapport au centre de l ecran (0).
** g->ray_pos = position de depart du rayon = la position de la camera/du joueur
** g->map = coordonnee int de la case ou se situe la camera/le joueur
*/

int			loop_raycast(t_game *g)
{
	int		col;

	col = 0;
	while (col < g->res_x)
	{
		g->camera_x = (2.0 * ((float)col / (float)g->res_x)) - 1.0;
		g->ray_pos_x = g->pos_x;
		g->ray_pos_y = g->pos_y;
		g->ray_dir_x = g->dir_x + g->plane_x * g->camera_x;
		g->ray_dir_y = g->dir_y + g->plane_y * g->camera_x;
		g->map_x = (int)g->ray_pos_x;
		g->map_y = (int)g->ray_pos_y;
		g->delta_dist_x = sqrt(1 + (g->ray_dir_y * g->ray_dir_y) /
			(g->ray_dir_x * g->ray_dir_x));
		g->delta_dist_y = sqrt(1 + (g->ray_dir_x * g->ray_dir_x) /
			(g->ray_dir_y * g->ray_dir_y));
		raycast(g, col++);
	}
	return (1);
}
