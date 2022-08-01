/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:40:01 by tconwy            #+#    #+#             */
/*   Updated: 2022/04/11 13:11:38 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parce_map_closed2(t_zone *zone, int y)
{
	int	x;

	if (y >= zone->height || y < 0)
		return (0);
	x = 0;
	while (zone->matrice_help[x + y * zone->width] == ' ')
		x++;
	if (zone->matrice_help[x + y * zone->width] != '1')
		return (0);
	x = zone->width - 1;
	while (zone->matrice_help[x + y * zone->width] == ' ')
		x--;
	if (zone->matrice_help[x + y * zone->width] != '1')
		return (0);
	return (1);
}

int	parce_map_closed1(t_zone *zone, int x)
{
	int	y;

	if (x >= zone->width || x < 0)
		return (0);
	y = 0;
	while (zone->matrice_help[x + y * zone->width] == ' ')
		y++;
	if (zone->matrice_help[x + y * zone->width] != '1')
		return (0);
	y = zone->height - 1;
	while (zone->matrice_help[x + y * zone->width] == ' ')
		y--;
	if (zone->matrice_help[x + y * zone->width] != '1')
		return (0);
	return (1);
}

int	parse_maphelp(t_zone *zone)
{
	int	i;

	i = 0;
	while (i < zone->height)
	{
		if (!parce_map_closed2(zone, i))
			return (0);
		i++;
	}
	i = 0;
	while (i < zone->height)
		i++;
	while (i < zone->width)
	{
		if (!parce_map_closed1(zone, i))
			return (0);
		i++;
	}
	return (1);
}

void	re_parse_martrice(t_zone *zone)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < zone->height)
	{
		x = ft_strlen(zone->matrice[y]);
		while (x < zone->width)
		{
			zone->matrice[y] = ft_strjoin1(zone->matrice[y], " ");
			x++;
		}
		y++;
	}
}

int	parce_map(t_zone *zone)
{
	int		y;
	int		qwe;
	int		a;

	a = 0;
	qwe = 0;
	zone->matrice = ft_split(zone->matrice_help, '\n');
	search_zone(zone);
	re_parse_martrice(zone);
	y = 0;
	free (zone->matrice_help);
	zone->matrice_help = NULL;
	while (a < zone->height)
	{
		zone->matrice_help = ft_strjoin1(zone->matrice_help,
				zone->matrice[a]);
		a++;
	}
	if (parse_maphelp(zone) == 0)
		return (0);
	qwe = search_wh(zone, qwe);
	if (qwe == 0)
		return (0);
	return (1);
}
