/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicheli <rmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:22:16 by rmicheli          #+#    #+#             */
/*   Updated: 2022/04/12 12:48:08 by rmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	dda_init2(t_draw *draw)
{
	draw->line_height = (int)(1000 / draw->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + 1000 / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + 1000 / 2;
	if (draw->draw_end >= 1000)
		draw->draw_end = 1000 - 1;
}

void	while_hit(t_draw *draw, t_zone *zone)
{
	while (draw->hit == 0)
	{
		if (draw->side_dist_x < draw->side_dist_y)
		{
			draw->side_dist_x += draw->delta_dist_x;
			draw->map_x += draw->step_x;
			draw->side = 0;
		}
		else
		{
			draw->side_dist_y += draw->delta_dist_y;
			draw->map_y += draw->step_y;
			draw->side = 1;
		}
		if (zone->matr_int[draw->map_x][draw->map_y] > 0)
			draw->hit = 1;
	}
}

void	step(t_draw *draw)
{
	if (draw->ray_dir_x < 0)
	{
		draw->step_x = -1;
		draw->side_dist_x = (draw->pos_x - draw->map_x) * draw->delta_dist_x;
	}
	else
	{
		draw->step_x = 1;
		draw->side_dist_x = (draw->map_x + 1.0 - draw->pos_x)
			* draw->delta_dist_x;
	}
	if (draw->ray_dir_y < 0)
	{
		draw->step_y = -1;
		draw->side_dist_y = (draw->pos_y - draw->map_y) * draw->delta_dist_y;
	}
	else
	{
		draw->step_y = 1;
		draw->side_dist_y = (draw->map_y + 1.0 - draw->pos_y)
			* draw->delta_dist_y;
	}
}

void	dda_init(t_draw *draw, int x)
{
	draw->camera_x = 2 * x / (double)1000 - 1;
	draw->ray_dir_x = draw->dir_x + draw->plane_x * draw->camera_x;
	draw->ray_dir_y = draw->dir_y + draw->plane_y * draw->camera_x;
	draw->delta_dist_x = fabs(1 / draw->ray_dir_x);
	draw->delta_dist_y = fabs(1 / draw->ray_dir_y);
	draw->map_x = (int)draw->pos_x;
	draw->map_y = (int)draw->pos_y;
	draw->hit = 0;
}

void	dda(t_draw *draw, t_zone *zone)
{
	int			x;

	x = -1;
	draw_other(zone);
	while (++x < 1000)
	{
		dda_init(draw, x);
		step(draw);
		while_hit(draw, zone);
		if (draw->side == 0)
			draw->perp_wall_dist = (draw->side_dist_x - draw->delta_dist_x);
		else
			draw->perp_wall_dist = (draw->side_dist_y - draw->delta_dist_y);
		dda_init2(draw);
		draw_texture(draw, zone, x);
	}
	mlx_put_image_to_window(zone->mlx->mlx_ptr,
		zone->mlx->mlx_win, zone->mlx->mlx_img, 0, 0);
}
