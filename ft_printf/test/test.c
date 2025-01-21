/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:53:34 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/21 18:25:43 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ft_printf.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

#ifdef TEST
#define FMT "'%.7s', '%.6s', '%.5s', '%.4s'\n", (char *)0, (char *)0, (char *)0, (char *)0
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
#ifdef CONTROL
# define CTRLUSR "\ncontrol                    "
# define CTRLSYS "\nsyst control               "
#else
# define CTRLUSR ""
# define CTRLSYS ""
#endif
int main(void)
{
	printf("\n| length     | %d"CTRLUSR"\n---\n", ft_printf(ARGS));
	printf("\n| length     | %d"CTRLSYS"\n", printf(ARGS));
}
#endif
