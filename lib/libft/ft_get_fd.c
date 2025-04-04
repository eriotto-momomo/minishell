/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timmi <timmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:16:05 by timmi             #+#    #+#             */
/*   Updated: 2025/04/04 16:29:13 by timmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 @brief	Open a file and return its file descriptor, with configurable mode.
 @details	This function opens the file at the given path with either read or write access.
			If `writable` is set, the file is opened in write mode with `O_CREAT`, and either
			`O_TRUNC` or `O_APPEND` depending on the `append` flag.
			If `writable` is not set, the file is opened in read-only mode.
			In case of failure, an error message is printed using `perror`.
 @param	path		The path to the file.
 @param	writable	Set to 1 to open the file for writing, or 0 for reading.
 @param	append		If `writable` is true, set this to 1 to append to the file instead of truncating it.
			
 @return	The file descriptor on success, or -1 on failure.
*/
static int	get_fd(char *path, int writable, int append)
{
	int	fd;
	int	flags;

	if (writable)
	{
		flags = O_WRONLY | O_CREAT;
		if (append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
	}
	else
	{
		flags = O_RDONLY;
	}
	fd = open(path, flags, 0644);
	if (fd == -1)
		perror(path);
	return (fd);
}
