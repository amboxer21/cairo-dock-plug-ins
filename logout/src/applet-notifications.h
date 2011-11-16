/**
* This file is a part of the Cairo-Dock project
*
* Copyright : (C) see the 'copyright' file.
* E-mail    : see the 'copyright' file.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __LOGOUT_NOTIFICATIONS__
#define  __LOGOUT_NOTIFICATIONS__


#include <cairo-dock.h>


CD_APPLET_ON_CLICK_H

CD_APPLET_ON_MIDDLE_CLICK_H

CD_APPLET_ON_BUILD_MENU_H


void cd_logout_set_timer (void);


void cd_logout_check_reboot_required (CairoDockFMEventType iEventType, const gchar *cURI, gpointer data);

void cd_logout_check_reboot_required_init (void);


void cd_logout_on_keybinding_pull (const gchar *keystring, gpointer user_data);


#endif
