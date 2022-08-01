/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:32:17 by tconwy            #+#    #+#             */
/*   Updated: 2022/04/11 13:32:41 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_f_c(t_zone *zone, char *colors, char id)
{
	t_rgb	rgb;
	char	**str;
	int		error;

	error = 0;
	while (*colors == ' ')
		colors++;
	str = ft_split(colors, ',');
	if (array_s((void **)str) != 3)
		error = 10;
	else
	{
		rgb = new_rgb(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
		if (!color_valid_rgb(rgb))
			error = 10;
	}
	free_array((void **)str, ft_free);
	if (error)
		return (0);
	if (id == 'F')
		zone->floor = init_color(rgb);
	else
		zone->ceiling = init_color(rgb);
	return (1);
}

int	parse_identifier(t_zone *zone)
{
	if (!pars_texture(zone->no, 0, zone))
		return (0);
	if (!pars_texture(zone->so, 1, zone))
		return (0);
	if (!pars_texture(zone->we, 2, zone))
		return (0);
	if (!pars_texture(zone->ea, 3, zone))
		return (0);
	if (!parse_f_c(zone, zone->f, 'F'))
		return (0);
	if (!parse_f_c(zone, zone->c, 'C'))
		return (0);
	return (1);
}

void	map_int_help(t_zone *zone)
{
	int	y;
	int	x;

	y = -1;
	while (zone->matrice[++y])
	{
		x = -1;
		zone->matr_int[y] = (int *)malloc(sizeof(int) * zone->width);
		while (zone->matrice[y][++x])
		{
			if (zone->matrice[y][x] == '1')
				zone->matr_int[y][x] = 1;
			else if (zone->matrice[y][x] == ' ' || zone->matrice[y][x] == '0')
				zone->matr_int[y][x] = 0;
			else if (zone->matrice[y][x] == 'W' || zone->matrice[y][x] == 'N'
					|| zone->matrice[y][x] == 'E' || zone->matrice[y][x] == 'S')
			{
				zone->pos_y = y;
				zone->pos_x = x;
				zone->c1 = zone->matrice[y][x];
				zone->matr_int[y][x] = 0;
			}
		}
	}
}

void	map_int(t_zone *zone)
{
	zone->matr_int = (int **)malloc(sizeof(int *) * zone->height);
	zone->c1 = '\0';
	map_int_help(zone);
	if (zone->c1 == '\0')
		exit (1);
	if (parse_identifier(zone) == 0)
	{
		printf("Error: failed pars text\n");
		exit (1);
	}
}
