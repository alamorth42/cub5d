/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:14:10 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** mlx_wall_x + mlx_get_data_addr_ret_x : get textures
** 0 NO
** 1 SO
** 2 WE
** 3 EA
** 4 S
*/

int			get_textures(t_game *g)
{
	int		res_x;
	int		res_y;
	int		i;

	res_x = g->res_x;
	res_y = g->res_y;
	if (!(g->xpm_to_img = (void **)malloc(sizeof(void *) * 5)))
		return (0);
	if (!(g->data_textures = (int **)malloc(sizeof(int *) * 5)))
		return (0);
	i = -1;
	while (++i < 5)
	{
		if (!(g->xpm_to_img[i] = mlx_xpm_file_to_image(g->mlx_init_ret,
		g->path_textures[i], &res_x, &res_y)))
			return (0);
		else
			g->data_textures[i] = (int*)mlx_get_data_addr(g->xpm_to_img[i],
			&g->bitpx, &g->size_line, &g->endian);
	}
	return (1);
}

/*
** update_pos
** raycast for each x
** draw_img_buffer
** update win with img
*/

int			update_win(t_game *g)
{
	update_pos(g);
	if (!g->sprites && !detect_sprites(g))
		handle_error(g, "malloc fail.\n");
	loop_raycast(g);
	draw_img_buffer(g);
	if (g->sprites)
		draw_sprites(g);
	mlx_put_image_to_window(g->mlx_init_ret, (void*)g->mlx_new_win_ret,
	(void*)g->mlx_new_img_ret, 0, 0);
	return (0);
}

/*
** update_pos
** raycast for each x
** draw_img_buffer
** update win with img
** O_CREAT : créer le fichier s'il n'existe pas
*/

int			create_screenshot(t_game *g)
{
	int fd;

	update_pos(g);
	if (!g->sprites && !detect_sprites(g))
		handle_error(g, "malloc fail.\n");
	loop_raycast(g);
	draw_img_buffer(g);
	if (g->sprites)
		draw_sprites(g);
	fd = open("fi.bmp", O_CREAT);
	close(fd);
	create_bmp(g);
	return (1);
}

/*
** mlx_init_ret : init
** mlx_new_win_ret : create window
** mlx_new_img_ret : create image
** img_buffer : pixels
** get_textures(g)
** mlx_hook : listen events like js
** mlx_loop_hook : run update_win in loop
** finish with mlx_loop
*/

int			ft_mlx(t_game *g)
{
	if (!(g->mlx_init_ret = mlx_init())
	|| (!(g->mlx_new_win_ret = mlx_new_window(g->mlx_init_ret, g->res_x,
	g->res_y, "cub3d win")))
	|| (!(g->mlx_new_img_ret = mlx_new_image(g->mlx_init_ret, g->res_x,
	g->res_y)))
	|| (!(g->img_buffer = (int*)mlx_get_data_addr(g->mlx_new_img_ret,
	&g->bit_pix_wdw, &g->size_line_wdw, &g->endian_wdw))))
		return (handle_error(g, "failed to init mlx\n"));
	if (!(get_textures(g)))
		return (handle_error(g, "failed to load textures\n"));
	if (g->save)
		return (create_screenshot(g));
	mlx_hook(g->mlx_new_win_ret, 2, 0, on_key_press, g);
	mlx_hook(g->mlx_new_win_ret, 3, 0, on_key_release, g);
	mlx_hook(g->mlx_new_win_ret, 17, 0, on_exit, g);
	mlx_loop_hook(g->mlx_init_ret, update_win, g);
	mlx_loop(g->mlx_init_ret);
	return (1);
}

/*
** 1. parsing
** 2. if parsing ok use mlx
*/

int			main(int argc, char **argv)
{
	t_game	*g;

	if (!(parse_args(argc, argv, &g)))
		return (-1);
	if (!(ft_mlx(g)))
		return (-1);
	return (0);
}
