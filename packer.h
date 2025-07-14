/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:23:36 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:23:39 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PACKER_H)
# define PACKER_H

#include <stdarg.h>

/* I have the right to use functions
 * from <stdarg.h> since ft_printf()
 * already uses it in my project anyway */
void	**pack_args(int nargs, ...);

#endif
