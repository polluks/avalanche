/* Avalanche
 * (c) 2022-3 Chris Young
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
*/

#ifndef AVALANCHE_CONFIG_H
#define AVALANCHE_CONFIG_H 1

struct avalanche_config {
	char *progname;
	
	char *sourcedir; /* default source dir for ASL */
	char *dest; /* default destination */
	char *tmpdir;
	int tmpdirlen;

	BOOL disable_asl_hook;
	ULONG viewmode; /* [1 = list, 0 = browser] */
	BOOL virus_scan;
	BOOL debug;
	BOOL ignorefs;
	BOOL disable_vscan_menu;
	BOOL drag_lock;
	BOOL aiss;
	ULONG closeaction; /* [1 = quit, 2 = hide, 0 = cancel] -- same as quit req */

	ULONG win_x;
	ULONG win_y;
	ULONG win_w;
	ULONG win_h;
	ULONG progress_size;

	int cx_pri;
	BOOL cx_popup;
	char *cx_popkey;
};

void config_window_open(struct avalanche_config *config);
ULONG config_window_get_signal(void);
ULONG config_window_handle_input(UWORD *code);
BOOL config_window_handle_input_events(struct avalanche_config *config, ULONG result, UWORD code);

#endif
