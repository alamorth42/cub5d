/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamorth <alamorth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:28:07 by alamorth          #+#    #+#             */
/*   Updated: 2019/12/27 23:02:32 by alamorth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** get_res
** hanlde min/max res
** malloc some tabs
*/

int		parse_res(t_game *g, char *line)
{
	int i;

	i = -1;
	while (!ft_isdigit(line[++i]))
		;
	if (!(g->res_x = ft_atoi(line + i)))
		return (0);
	i += ft_nbrlen(g->res_x, 10);
	while (!ft_isdigit(line[++i]))
		;
	if (!(g->res_y = ft_atoi(line + i)))
		return (0);
	g->res_x = ft_set_int_in_range(100, g->res_x, 2560);
	g->res_y = ft_set_int_in_range(60, g->res_y, 1440);
	if (!(g->x_len_for_y = (int *)malloc(sizeof(int) * 10000))
		|| !(g->distances = (float *)malloc(sizeof(float) * (g->res_x)))
		|| !(g->sides = (int *)malloc(sizeof(int) * (g->res_x)))
		|| !(g->hit_wall_x = (float *)malloc(sizeof(float) * (g->res_x)))
		|| !(g->tex_x = (int *)malloc(sizeof(int) * (g->res_x)))
		|| !(g->path_textures = (char **)malloc(sizeof(char *) * 5)))
		return (0);
	i = 0;
	while (i < 5)
		g->path_textures[i++] = (char *)NULL;
	return (1);
}

/*
** store map in buffer previous to build map tab
*/

int		build_buffer(t_game *g, char *line)
{
	int		len;
	char	*line_trim;
	char	*tmp;

	if (!(line_trim = ft_strfulltrim(line, " ")))
		return (0);
	len = ft_strlen(line_trim);
	if (g->map_y_len == 0)
	{
		if (!(g->buffer = ft_strdup(line_trim)))
			return (0);
		ft_strcpy(g->buffer, line_trim);
	}
	else
	{
		tmp = g->buffer;
		if (!(g->buffer = ft_strjoin(g->buffer, line_trim)))
			return (0);
		ft_strdel(&tmp);
	}
	ft_strdel(&line_trim);
	g->x_len_for_y[g->map_y_len] = len;
	g->map_y_len += 1;
	return (1);
}

/*
** parse path and floor/ceiling colors
*/

int		parse_path(t_game *g, char *line)
{
	if ((line[0] == 'N' && line[1] == 'O')
		&& !(g->path_textures[0] = ft_substr(line,
			maga(line), ft_strlen(line))))
		return (0);
	else if ((line[0] == 'S' && line[1] == 'O')
		&& !(g->path_textures[1] = ft_substr(line,
			maga(line), ft_strlen(line))))
		return (0);
	else if ((line[0] == 'W' && line[1] == 'E')
		&& !(g->path_textures[2] = ft_substr(line,
			maga(line), ft_strlen(line))))
		return (0);
	else
		return (parse_path2(g, line));
	return (1);
}

/*
** parse_res
** build_buffer
** parse_path
*/

int		parse_line(t_game *g, char *line)
{
	if (line[0] == 'R' && line[1] == ' ' && !parse_res(g, line))
		return (0);
	else if (line[0] == '0')
		return (0);
	else if (line[0] == '1' && !build_buffer(g, line))
		return (0);
	else if (!parse_path(g, line))
		return (0);
	return (1);
}

/*
** check arg range
** check fd
** init game struct
** loop for each file line and parse_line
*/

int		parse_args(int argc, char **argv, t_game **g)
{
	int		fd;
	char	*line;
	int		gnl_ret;

	if (argc == 0 || argc > 3)
		return (handle_error(NULL, "argc must be 1 or 2 if -save opt.\n"));
	if (!ft_str_end_with(argv[1], ".cub"))
		return (handle_error(NULL, "file extension not valid.\n"));
	if (!(fd = open(argv[1], O_RDONLY)))
		return (handle_error(NULL, "fd not valid.\n"));
	if (!(*g = (t_game *)malloc(sizeof(t_game))))
		return (handle_error(NULL, "malloc error.\n"));
	if (!init_g(*g, argc, argv))
		return (handle_error(NULL, "argv[2] not valid.\n"));
	line = NULL;
	gnl_ret = 1;
	while (gnl_ret)
	{
		gnl_ret = get_next_line(fd, &line);
		if (gnl_ret < 0 || !parse_line(*g, line))
			return (handle_error(*g, "error while reading .cub.\n"));
		ft_strdel(&line);
	}
	close(fd);
	return (build_map(*g) ? 1 : handle_error(*g, "map is not valid\n"));
}
