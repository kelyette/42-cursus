/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:53:34 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/26 17:22:39 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ft_printf.h"
#include <string.h>
#include <limits.h>

#ifdef TEST
#define FMT "%#x, %#x\n", 0xfa, 0x0
int	main(void)
{
	ft_printf(FMT);
	printf(FMT);
}
/*int	main(void)
{
	int i = ft_printf(FMT);
	printf("(%d)\n", i);
	i = printf(FMT);
	printf("(%d)\n", i);
}*/
#elif !defined(FORMAT)
int	main(void)
{
	ft_printf("%s!", "format and / or vars macros undefined");
	printf("\n---\n%s!", "format and / or vars macros undefined");
	fflush(stdout);
}
#else
#ifdef VARS
# define ARGS FORMAT, VARS
#else
# define ARGS FORMAT
#endif
int main(void)
{
	int u = ft_printf(ARGS);
	printf("\n| length     | %d\n---\n", u);
	int s = printf(ARGS);
	printf("\n| length     | %d\n", s);
}
#endif
