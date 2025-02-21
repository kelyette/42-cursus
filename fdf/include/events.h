/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:10:39 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/21 15:35:08 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H
# include "mlx.h"

# include "env.h"
# include "drawers.h"

# ifndef KEYBINDS_MAX
#  define KEYBINDS_MAX 32
# endif

# define MOUSE1         1
# define MOUSE2         2
# define MOUSE3         3

# ifdef COCOA
#  define KEY_W          13
#  define KEY_A          0
#  define KEY_S          1
#  define KEY_D          2
#  define KEY_Q          12
#  define KEY_E          14
#  define KEY_I          34
#  define KEY_O          31
#  define KEY_F          3
#  define KEY_COMMA      43
#  define KEY_DOT        47
#  define KEY_LEFT       123
#  define KEY_RIGHT      124
#  define KEY_DOWN       125
#  define KEY_UP         126
#  define KEY_TAB        48
#  define KEY_ESCAPE     53
#  define KEY_NUMPAD0    82
#  define KEY_NUMPAD1    83
#  define KEY_NUMPAD2    84
#  define KEY_NUMPAD3    85
#  define KEY_NUMPAD4    86
#  define KEY_NUMPAD5    87
#  define KEY_NUMPAD6    88
#  define KEY_NUMPAD7    89
#  define KEY_NUMPAD8    91
#  define KEY_NUMPAD9    92

#  define ON_KEYDOWN     2
#  define ON_KEYUP       3
#  define ON_MOUSEDOWN   4
#  define ON_MOUSEUP     5
#  define ON_MOUSEMOVE   6
#  define ON_EXPOSE      12
#  define ON_DESTROY     17
# else
#  define KEY_W          119
#  define KEY_A          97
#  define KEY_S          115
#  define KEY_D          100
#  define KEY_Q          113
#  define KEY_E          101
#  define KEY_I          105
#  define KEY_O          111
#  define KEY_F          102
#  define KEY_COMMA      44
#  define KEY_DOT        46
#  define KEY_LEFT       0xff51
#  define KEY_RIGHT      0xff53
#  define KEY_DOWN       0xff54
#  define KEY_UP         0xff52
#  define KEY_TAB        0xff09
#  define KEY_ESCAPE     0xff1b
#  define KEY_NUMPAD0    0xffb0
#  define KEY_NUMPAD1    0xffb1
#  define KEY_NUMPAD2    0xffb2
#  define KEY_NUMPAD3    0xffb3
#  define KEY_NUMPAD4    0xffb4
#  define KEY_NUMPAD5    0xffb5
#  define KEY_NUMPAD6    0xffb6
#  define KEY_NUMPAD7    0xffb7
#  define KEY_NUMPAD8    0xffb8
#  define KEY_NUMPAD9    0xffb9

#  define ON_KEYDOWN     2
#  define ON_KEYUP       3
#  define ON_MOUSEDOWN   4
#  define ON_MOUSEUP     5
#  define ON_MOUSEMOVE   6
#  define ON_EXPOSE      12
#  define ON_DESTROY     17
# endif

# define DEFAULTACTION  rotate

enum e_keybind_t
{
	KBOnce,
	KBHold,
	MClick,
	MHold
};

typedef struct s_keybind
{
	int	code;
	int	type;
	int	state;
}	t_kbind;

typedef struct s_infonode
{
	char	*title;
	char	*valstr;
	int		type;
	int		precision;
	void	*valptr;
}	t_info;

typedef struct s_loopstate
{
	int		i;
	float	delta;
	int		redraw;
	int		anykey;
	int		mouse;
	t_info	*info;
	int		info_count;
	t_kbind	keybinds[KEYBINDS_MAX];
	void	(*action)(t_env *, float, float, float);
	int		showaxes;
}	t_ls;

// initializers
int		init_hooks(t_env *env);
int		init_loop(t_env *env);
int		init_info(t_env *env);

// special events
int		evf_loop(t_env *env);

// mouse events
int		evf_mouse(int btn, int x, int y, t_env *env);
int		evf_mousemove(int x, int y, t_env *env);
int		evf_mousedown(int btn, int x, int y, t_env *env);
int		evf_mouseup(int btn, int x, int y, t_env *env);

// keyboard events
int		evf_key(int key, t_env *env);
int		evf_keyloop(t_env *env);
int		evf_keydown(int key, t_env *env);
int		evf_keyup(int key, t_env *env);

// info
void	draw_info(t_env *env);
void	free_info(t_info *info, int count);

// actions
int		fdfclose(t_env *env, int code);
void	move(t_env *env, float x, float y, float z);
void	scale(t_env *env, float x, float y, float z);
void	rotate(t_env *env, float x, float y, float z);

// utils
t_kbind	*get_key(t_kbind *keybinds, int key);
int		get_complkey(t_kbind *kbds, int k1, int k2);
char	*ftoa(float f, int precision);
char	*v2toa(t_vec2 v, int precision);
char	*v3toa(t_vec3 v, int precision);

#endif
