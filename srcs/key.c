/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:39:39 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** https://github.com/VBrazhnik/
** FdF/wiki/How-to-handle-mouse-buttons-and-key-presses%3F
** 13 'w' -> avance
** 1  's' -> recule
** 126 up arrow -> avance
** 125 down arrow -> recule
** 12 'q' -> decale a gauche
** 14 'e' -> decale a droite
** 0  'a' -> rotate camera gauche
** 2  'd' -> rotate camera droite
** 123 left arrow -> rotate camera gauche
** 124 right arrow -> rotate camera droite
** 53 ESC
** 69 '+' -> accelerer
** 79 '-' -> ralentir
*/

int		on_key_press(int key, t_game *g)
{
	if (key == 13 || key == 126)
		g->move_f = 1;
	else if (key == 1 || key == 125)
		g->move_b = 1;
	else if (key == 12)
		g->move_l = 1;
	else if (key == 14)
		g->move_r = 1;
	else if (key == 0 || key == 123)
		g->move_rl = 1;
	else if (key == 2 || key == 124)
		g->move_rr = 1;
	else if (key == 69)
		g->speed = g->speed < .3 ? g->speed + .04 : g->speed;
	return (0);
}

int		on_key_release(int key, t_game *g)
{
	if (key == 13 || key == 126)
		g->move_f = 0;
	else if (key == 1 || key == 125)
		g->move_b = 0;
	else if (key == 12)
		g->move_l = 0;
	else if (key == 14)
		g->move_r = 0;
	else if (key == 0 || key == 123)
		g->move_rl = 0;
	else if (key == 2 || key == 124)
		g->move_rr = 0;
	else if (key == 53)
	{
		free_g(g);
		exit(0);
	}
	else if (key == 78)
		g->speed = g->speed > .05 ? g->speed - .04 : g->speed;
	return (0);
}

/*
** on_exit for red cross close
*/

int		on_exit(t_game *g)
{
	free_g(g);
	exit(0);
	return (1);
}
