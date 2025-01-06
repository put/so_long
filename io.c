/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:18:53 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/06 01:20:52 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char *read_file_to_string(const char *filename) { //TODO: Rewrite with GNL
    int fd = open(filename, O_RDONLY);
    if (fd == -1) return perror("Error opening file"), NULL;

    size_t size = 1024, total = 0;
    char *content = malloc(size);
    if (!content) return perror("Error allocating memory"), close(fd), NULL;

    ssize_t bytes;
    while ((bytes = read(fd, content + total, size - total - 1)) > 0) {
        total += bytes;
        if (total >= size - 1) {
            size *= 2;
            char *temp = realloc(content, size);
            if (!temp) return perror("Error reallocating memory"), free(content), close(fd), NULL;
            content = temp;
        }
    }
    if (bytes == -1) return perror("Error reading file"), free(content), close(fd), NULL;

    content[total] = '\0';
    close(fd);
    return content;
}