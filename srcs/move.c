/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 20:17:20 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:14:27 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** forward || backward
*/

void	update_pos_fb(t_game *g)
{
	if (g->move_f)
	{
		if (g->map[(int)g->pos_y][(int)(g->pos_x + g->dir_x * g->speed)] == '0')
			g->pos_x += (g->dir_x * g->speed);
		if (g->map[(int)(g->pos_y + g->dir_y * g->speed)][(int)g->pos_x] == '0')
			g->pos_y += (g->dir_y * g->speed);
	}
	if (g->move_b)
	{
		if (g->map[(int)g->pos_y][(int)(g->pos_x - g->dir_x * g->speed)] == '0')
			g->pos_x -= (g->dir_x * g->speed);
		if (g->map[(int)(g->pos_y - g->dir_y * g->speed)][(int)g->pos_x] == '0')
			g->pos_y -= (g->dir_y * g->speed);
	}
}

/*
** rotate right
*/

void	update_pos_rl(t_game *g)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = g->dir_x;
	g->dir_x = g->dir_x * cos(g->speed) - g->dir_y * sin(g->speed);
	g->dir_y = old_dir_x * sin(g->speed) + g->dir_y * cos(g->speed);
	old_plane_x = g->plane_x;
	g->plane_x = g->plane_x * cos(g->speed) - g->plane_y * sin(g->speed);
	g->plane_y = old_plane_x * sin(g->speed) + g->plane_y * cos(g->speed);
}

/*
** rotate left
*/

void	update_pos_rr(t_game *g)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = g->dir_x;
	g->dir_x = g->dir_x * cos(-g->speed) - g->dir_y * sin(-g->speed);
	g->dir_y = old_dir_x * sin(-g->speed) + g->dir_y * cos(-g->speed);
	old_plane_x = g->plane_x;
	g->plane_x = g->plane_x * cos(-g->speed) - g->plane_y * sin(-g->speed);
	g->plane_y = old_plane_x * sin(-g->speed) + g->plane_y * cos(-g->speed);
}

/*
** right || left
*/

void	update_pos_lr(t_game *g)
{
	if (g->move_l)
	{
		if (g->map[(int)g->pos_y]
		[(int)(g->pos_x - g->plane_x * g->speed)] == '0')
			g->pos_x -= (g->plane_x * g->speed);
		if (g->map[(int)(g->pos_y - g->plane_y * g->speed)]
		[(int)g->pos_x] == '0')
			g->pos_y -= (g->plane_y * g->speed);
	}
	if (g->move_r)
	{
		if (g->map[(int)g->pos_y]
		[(int)(g->pos_x + g->plane_x * g->speed)] == '0')
			g->pos_x += (g->plane_x * g->speed);
		if (g->map[(int)(g->pos_y + g->plane_y * g->speed)]
		[(int)g->pos_x] == '0')
			g->pos_y += (g->plane_y * g->speed);
	}
}

/*
** dispatch
*/

void	update_pos(t_game *g)
{
	if (g->move_f || g->move_b)
		update_pos_fb(g);
	if (g->move_rl)
		update_pos_rl(g);
	if (g->move_rr)
		update_pos_rr(g);
	if (g->move_l || g->move_r)
		update_pos_lr(g);
}
