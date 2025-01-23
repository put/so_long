/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:54:47 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/23 21:58:28 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "minilibx-linux/mlx.h"
#include "mlx_manage.h"

int main_1(void) // TODO: Add ft_printf to the project to replace printf
{
	char *rawmap;
	char **map;
	int width;
	int height;
	int collectibles_count;

	rawmap = "1111111111\n1C00100001\n10P0101101\n10001C1E01\n1001111001\n1010000001\n101C111001\n1011100001\n10000000C1\n1111111111";
	width = getmapwidth(rawmap);
	height = getmapheight(rawmap);
	printf("Map size is %i by %i\n", width, height);
	if(verifyrect(rawmap, width))
	{
		printf("Map is rectangular\n");
		map = getsplitmap(rawmap);
		if (verifywalls(map, width))
		{
			printf("Map is correctly surrounded by walls\n");
			if (verifyobjects(rawmap))
				printf("Map has proper objects\n");
			else
				printf("ERROR: Map does NOT have proper objects!\n");
		}
		else
			printf("ERROR: Map does NOT have proper walls!\n");
	}
	else
		printf("ERROR: Map is NOT rectangular!\n");
	print_map(map, height, width);
	floodfill(rawmap, map, 2, 2);
	printf("-----------------\n");
	print_map(map, height, width);
}

void* getmlx(void)
{
	static void *mlx = NULL;
	if (!mlx)
		mlx = mlx_init();
	if (!mlx)
	{
		perror("ERROR: mlx_init() failed\n");
		exit(1);
	}
	return (mlx);
}

int handle_keypress(int keycode, void *param)
{
    void **win = (void **)param;

    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(getmlx(), *win);
        exit(0);
    }
	else
		printf("Keycode: %i\n", keycode);
    return (0);
}


int main(void)
{
    void *win;
    win = mlx_new_window(getmlx(), 800, 600, "My Window");
	int imgsize = 16;
	mlx_key_hook(win, handle_keypress, &win);
	mlx_put_image_to_window(getmlx(), win, mlx_xpm_file_to_image(getmlx(), "wall.xpm", &imgsize, &imgsize), 0, 0);
    mlx_loop(getmlx());
    return 0;
}
