/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyburgh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:54:40 by amyburgh          #+#    #+#             */
/*   Updated: 2018/10/24 21:48:12 by amyburgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Dispatch table[24]
// http://www.cplusplus.com/reference/cstdio/printf/

const t_dispatch	g_select[] = {

	{'s', &fmt_s},
/*	{'S', &fmt_ss},

	{'p', &fmt_p},

	{'d', &fmt_d},
	{'D', &fmt_dd},
	{'i', &fmt_d},

	{'o', &fmt_o},
	{'O', &fmt_oo},
	{'u', &fmt_u},
	{'U', &fmt_uu},
	{'x', &fmt_x},
	{'X', &fmt_xx},

	{'c', &fmt_c},
	{'C', &fmt_cc},

 ---------- BONUS ----------

	{'e', &fmt_e},
	{'E', &fmt_ee},
	{'f', &fmt_f},
	{'F', &fmt_ff},
	{'g', &fmt_g},
	{'G', &fmt_gg},
	{'a', &fmt_a},
	{'A', &fmt_aa},

	{'n', &fmt_n},

	{'%', &fmt_percent}
	*/
};
