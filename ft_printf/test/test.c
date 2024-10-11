/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:53:34 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/11 14:25:24 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ft_printf.h"
#include "ft_utils.h"
#include "ft_formats.h"
#include <string.h>
#include <limits.h>

#ifdef TEST
int	main(void)
{
	printf("string: \"%.4s\"", (char *)0);
}
#elif !defined(FORMAT)
int	main(void)
{
	ft_printf("%s!", "format and / or vars macros undefined");
	printf("\n---\n%s!", "format and / or vars macros undefined");
	fflush(stdout);
}
#else
int main(void)
{
#ifdef VARS
	ft_printf(FORMAT, VARS);
	printf("\n---\n"FORMAT, VARS);
#else
	ft_printf(FORMAT);
	printf("\n---\n"FORMAT);
#endif
}
#endif
