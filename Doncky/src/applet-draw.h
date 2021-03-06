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


#ifndef __APPLET_DRAW__
#define  __APPLET_DRAW__

#include <cairo-dock.h>
#include "applet-struct.h"

void ltrim( gchar* str, const gchar* t );
void rtrim( gchar* str, const gchar* t );
gchar *g_str_replace (gchar *cString, const gchar cWord, const gchar cReplace);
void cd_doncky_get_color_from_xml (gchar *cNodeContent, double *fColor);
void cd_doncky_export_color_to_conf (double *fColor, const gchar *cGroupName, const gchar *cParam, GldiModuleInstance *myApplet);
// gchar *g_str_position (const gchar *cString, const int iPosition, const char cSeparator);
double _Ko_to_Mo (GldiModuleInstance *myApplet , double fValueInKo);
double _Ko_to_Go (GldiModuleInstance *myApplet , double fValueInKo);

void cd_launch_command (GldiModuleInstance *myApplet);

gboolean cd_retrieve_command_result (GldiModuleInstance *myApplet);


void cd_applet_draw_my_desklet (GldiModuleInstance *myApplet, int iWidth, int iHeight);

void cd_applet_update_my_icon (GldiModuleInstance *myApplet);


#endif
