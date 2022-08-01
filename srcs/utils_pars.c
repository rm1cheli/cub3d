/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:14:01 by tconwy            #+#    #+#             */
/*   Updated: 2022/04/09 13:12:20 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

int	pars_texture(char *path, int side, t_zone *zone)
{
	t_img	*img;
	char	*str;

	str = (char *)malloc(sizeof(char) * ft_strlen(path));
	ft_strlcpy(str, path, ft_strlen(path));
	while (*str == ' ')
		str++;
	zone->texture[side].img = NULL;
	img = &zone->texture[side];
	img->img = mlx_xpm_file_to_image(zone->mlx->mlx_ptr,
			str, &img->line_length, &img->height);
	if (!img->img)
	{
		free (str);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		free (str);
		return (0);
	}
	free (str);
	return (1);
}

t_rgb	new_rgb(int r, int g, int b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

int	color_valid_rgb(t_rgb rgb)
{
	if (rgb.r > 255 || rgb.r < 0)
		return (0);
	if (rgb.g > 255 || rgb.g < 0)
		return (0);
	if (rgb.b > 255 || rgb.b < 0)
		return (0);
	return (1);
}

void	*array_clear(void **ptr, void *(f)(void *))
{
	while (ptr && *ptr && f)
	{
		*ptr = f(*ptr);
		ptr++;
	}
	return (NULL);
}
