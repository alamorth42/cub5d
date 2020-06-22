/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 02:24:46 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>

/*
** struct
*/

typedef struct	s_game
{
	int				save;
	int				res_x;
	int				res_y;
	int				col_floor_hex;
	int				col_ceiling_hex;
	char			*buffer;
	char			**map;
	int				map_y_len;
	int				*x_len_for_y;
	float			pos_x;
	float			pos_y;
	void			*mlx_init_ret;
	void			*mlx_new_win_ret;
	int				*mlx_new_img_ret;
	int				*img_buffer;
	char			**path_textures;
	int				**data_textures;
	void			**xpm_to_img;
	int				bitpx;
	int				size_line;
	int				endian;
	int				bit_pix_wdw;
	int				size_line_wdw;
	int				endian_wdw;
	float			*distances;
	int				*sides;
	float			*hit_wall_x;
	int				*tex_x;
	float			*hit_sprite_x;
	float			camera_x;
	float			ray_pos_x;
	float			ray_pos_y;
	float			ray_dir_x;
	float			ray_dir_y;
	float			plane_x;
	float			plane_y;
	float			dir_x;
	float			dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			speed;
	int				move_f;
	int				move_b;
	int				move_l;
	int				move_r;
	int				move_rl;
	int				move_rr;
	struct s_sprite	*sprites;

}				t_game;

typedef struct	s_sprite
{
	int					order;
	float				pos_x;
	float				pos_y;
	float				distance;
	float				dist_x;
	float				dist_y;
	float				corrected_dist_x;
	float				corrected_dist_y;
	int					sprite_screen_x;
	int					height_in_px;
	int					width_in_px;
	int					x_start;
	int					x_end;
	int					y_start;
	int					y_end;
	int					tex_x;
	int					tex_y;
	int					first_hit_col;
	int					last_hit_col;
	struct s_sprite		*next;
}				t_sprite;

/*
** main.c
*/

int				get_textures(t_game *g);
int				update_win(t_game *g);
int				create_screenshot(t_game *g);
int				ft_mlx(t_game *g);
int				main(int argc, char **argv);

/*
** parse.c
*/

int				parse_res(t_game *g, char *line);
int				build_buffer(t_game *game, char *line);
int				parse_path(t_game *g, char *line);
int				parse_line(t_game *g, char *line);
int				parse_args(int argc, char **argv, t_game **game);

/*
** parse_utils.c
*/

int				init_g(t_game *g, int argc, char **argv);
int				parse_col(char *col, int *dest);
int				check_if_map_valid(t_game *g);
int				build_map(t_game *game);

/*
** utils.c
*/

int				maga(char *line);
void			mfga(t_game *g, char *tmp, int x, int y);
void			set_direction(t_game *g, char c);
void			set_direction2(t_game *g, char c);
int				parse_path2(t_game *g, char *line);

/*
** raycast.c
*/

void			get_no_so_distances(t_game	*g, int col, int step_x, int side);
void			get_we_ea_distances(t_game	*g, int col, int step_y, int side);
void			set_step_xy_move_on_map(t_game	*g, int *step_x, int *step_y);
int				raycast(t_game	*g, int col);
int				loop_raycast(t_game	*g);

/*
** key.c
*/

int				on_key_press(int key, t_game *g);
int				on_key_release(int key, t_game *g);
int				on_exit(t_game *g);

/*
** move.c
*/

void			update_pos_fb(t_game *g);
void			update_pos_rr(t_game *g);
void			update_pos_rl(t_game *g);
void			update_pos_lr(t_game *g);
void			update_pos(t_game *g);

/*
** draw.c
*/

void			draw_floor_and_ceiling(t_game *g, int x, int y);
void			draw_wall_col(t_game *g, int x, int y, int wall_pxl_high);
int				draw_img_buffer(t_game *g);
void			draw_sprite(t_game *g, t_sprite *s);
void			draw_sprites(t_game *g);

/*
** free.c
*/

void			free_map(t_game *g);
void			free_g(t_game *g);
int				handle_error(t_game *g, char *error_msg);

/*
** bmp.c
*/

void			get_pixels(t_game *g, int fd);
unsigned char	*create_file_header(int res_y, int res_x);
unsigned char	*create_bitmap_header(int res_y, int res_x);
int				create_bmp(t_game *g);

/*
** sprite_utils.c
*/

int				count_sprites(t_game *g);
int				get_last_order(t_sprite *sprites);
void			store_sprite_hit_col(t_game *g, int hit_col);
void			swap_sprite_data(t_sprite *s1, t_sprite *s2);
void			sort_sprites(t_game *g);

/*
** sprite.c
*/

void			push_distance(t_game *g, t_sprite *new_s);
int				sort_and_add_sprite(t_game *g, int x, int y);
int				parse_sprites(t_game *g);
int				detect_sprites(t_game *g);
void			prepare_sprite(t_game *g, t_sprite *s, float inverse_coef);

#endif
