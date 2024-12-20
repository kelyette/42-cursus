/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:10:39 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/19 03:26:32 by kcsajka          ###   ########.fr       */
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
# define KEY_W          13
# define KEY_A          0
# define KEY_S          1
# define KEY_D          2
# define KEY_I          34
# define KEY_O          31
# define KEY_F          3
# define KEY_LEFT       123
# define KEY_RIGHT      124
# define KEY_DOWN       125
# define KEY_UP         126
# define KEY_COMMAND    55
# define KEY_SHIFT      56
# define KEY_ALT        58
# define KEY_TAB        48
# define KEY_ESCAPE     53

# define ON_KEYDOWN     2
# define ON_KEYUP       3
# define ON_MOUSEDOWN   4
# define ON_MOUSEUP     5
# define ON_MOUSEMOVE   6
# define ON_EXPOSE      12
# define ON_DESTROY     17

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

typedef struct s_loopstate
{
	int		i;
	int		redraw;
	int		anykey;
	int		mouse;
	t_kbind	keybinds[KEYBINDS_MAX];
	void	(*action)(t_env *, float, float, float);
}	t_ls;

// initializers
int		init_hooks(t_env *env);
int		init_loop(t_env *env);

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

// actions
int		fdfclose(t_env *env);
void	move(t_env *env, float x, float y, float z);
void	scale(t_env *env, float x, float y, float z);
void	rotate(t_env *env, float x, float y, float z);

// utils
t_kbind	*get_key(t_kbind *keybinds, int key);
int		get_complkey(t_kbind *kbds, int k1, int k2);

#endif
