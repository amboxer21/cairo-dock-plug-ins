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

#include <stdlib.h>
#include <string.h>

#include "applet-struct.h"
#include "applet-search.h"
#include "applet-dialog.h"
#include "applet-notifications.h"


//\___________ Define here the action to be taken when the user left-clicks on your icon or on its subdock or your desklet. The icon and the container that were clicked are available through the macros CD_APPLET_CLICKED_ICON and CD_APPLET_CLICKED_CONTAINER. CD_APPLET_CLICKED_ICON may be NULL if the user clicked in the container but out of icons.
CD_APPLET_ON_CLICK_BEGIN
	cd_toggle_dialog ();
CD_APPLET_ON_CLICK_END


//\___________ Same as ON_CLICK, but with middle-click.
CD_APPLET_ON_MIDDLE_CLICK_BEGIN
	
CD_APPLET_ON_MIDDLE_CLICK_END


//\___________ Define here the entries you want to add to the menu when the user right-clicks on your icon or on its subdock or your desklet. The icon and the container that were clicked are available through the macros CD_APPLET_CLICKED_ICON and CD_APPLET_CLICKED_CONTAINER. CD_APPLET_CLICKED_ICON may be NULL if the user clicked in the container but out of icons. The menu where you can add your entries is available throught the macro CD_APPLET_MY_MENU; you can add sub-menu to it if you want.
static GtkWidget *s_pMenu = NULL;
static GList *s_pEventList = NULL;
void cd_recent_events_reset_uri_list (void)
{
	s_pEventList = NULL;
	return;
	if (s_pEventList != NULL)
	{
		g_list_foreach (s_pEventList, (GFunc) g_free, NULL);
		g_list_free (s_pEventList);
		s_pEventList = NULL;
	}
}
static gboolean _on_delete_menu (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	cd_debug ("*** menu deleted");
	s_pMenu = NULL;
	cd_recent_events_reset_uri_list ();
	return FALSE;
}
static void _open_file (GtkMenuItem *menu_item, gchar *cCommand)
{
	cd_debug ("%s (%s)", __func__, cCommand);
	
	cairo_dock_launch_command (cCommand);
	
	cd_recent_events_reset_uri_list ();
}
static void _on_delete_events (int iNbEvents, gpointer data)
{
	if (iNbEvents > 0)
	{
		cairo_dock_show_temporary_dialog_with_icon_printf (D_("%d event(s) deleted"), myIcon, myContainer, 3e3, "same icon", iNbEvents);
	}
	if (iNbEvents != 0)
	{
		cd_trigger_search ();
	}
	CD_APPLET_STOP_DEMANDING_ATTENTION;
}
static void _clear_today_events (GtkMenuItem *menu_item, gpointer data)
{
	cd_delete_recent_events (1, (CDOnDeleteEventsFunc)_on_delete_events, data);
	CD_APPLET_DEMANDS_ATTENTION ("pulse", 30);
}
static void _clear_all_events (GtkMenuItem *menu_item, gpointer data)
{
	cd_delete_recent_events (1e6, (CDOnDeleteEventsFunc)_on_delete_events, data);  // in Maverick we get the following error: ZeitgeistEngine instance has no attribute 'delete_log'. so we just delete as much events as possible.
	CD_APPLET_DEMANDS_ATTENTION ("pulse", 30);
}
static void _on_find_related_events (ZeitgeistResultSet *pEvents, Icon *pIcon)
{
	cd_debug ("%s ()", __func__);
	cd_recent_events_reset_uri_list ();
	if (s_pMenu == NULL)
		return;
	
	ZeitgeistEvent     *event;
	ZeitgeistSubject   *subject;
	gint                i,n;
	GtkWidget *pMenuItem = NULL, *pSubMenu = NULL;
	const gchar *cEventURI;
	gchar *cName = NULL, *cURI = NULL, *cIconName = NULL;
	gchar *cCommand;
	double fOrder;
	int iVolumeID;
	gboolean bIsDirectory;
	
	pSubMenu = CD_APPLET_ADD_SUB_MENU_WITH_IMAGE (D_("Recent files"), s_pMenu, GTK_STOCK_FILE);
	while (zeitgeist_result_set_has_next (pEvents))
	{
		event = zeitgeist_result_set_next (pEvents);
		n = zeitgeist_event_num_subjects (event);
		for (i = 0; i < n; i++)
		{
			subject = zeitgeist_event_get_subject (event, i);
			cEventURI = zeitgeist_subject_get_uri (subject);
			cd_debug (" + %s", cEventURI);
			
			cairo_dock_fm_get_file_info (cEventURI, &cName, &cURI, &cIconName, &bIsDirectory, &iVolumeID, &fOrder, 0);
			//g_free (cName);
			//g_free (cURI);
			
			gchar *cPath = g_filename_from_uri (cEventURI, NULL, NULL);  // some programs dont support URI, so we feed them with path.
			cCommand = g_strdup_printf ("%s \"%s\"", pIcon->cCommand, cPath);
			g_free (cPath);
			s_pEventList = g_list_prepend (s_pEventList, cCommand);
			
			CD_APPLET_ADD_IN_MENU_WITH_STOCK_AND_DATA (zeitgeist_subject_get_text (subject), cIconName, _open_file, pSubMenu, cCommand);
			//g_free (cIconName);
		}
	}
	if (pSubMenu)
	{
		gtk_widget_show_all (pSubMenu);  // sinon des fois il n'apparait pas au 1er survol de son entree.
		gtk_widget_show_all (s_pMenu);
	}
	cd_debug ("items added");
}
CD_APPLET_ON_BUILD_MENU_PROTO
{
	cd_debug ("%s (%s...)", __func__, CD_APPLET_CLICKED_ICON && CD_APPLET_CLICKED_ICON->pMimeTypes ?CD_APPLET_CLICKED_ICON->pMimeTypes[0] : "");
	CD_APPLET_ENTER;
	if (CD_APPLET_CLICKED_ICON != NULL)
	{
		GtkWidget *pMenuItem, *image;
		
		if (CD_APPLET_CLICKED_ICON == myIcon)
		{
			GtkWidget *pSubMenu = CD_APPLET_CREATE_MY_SUB_MENU ();
			CD_APPLET_ADD_ABOUT_IN_MENU (pSubMenu);
			
			CD_APPLET_ADD_IN_MENU_WITH_STOCK_AND_DATA (D_("Delete today's events"), GTK_STOCK_CLEAR, _clear_today_events, CD_APPLET_MY_MENU, myApplet);
			
			CD_APPLET_ADD_IN_MENU_WITH_STOCK_AND_DATA (D_("Delete all events"), GTK_STOCK_DELETE, _clear_all_events, CD_APPLET_MY_MENU, myApplet);
		}
		else if (CD_APPLET_CLICKED_ICON->pMimeTypes != NULL)
		{
			cd_find_recent_related_files ((const gchar **)CD_APPLET_CLICKED_ICON->pMimeTypes, (CDOnGetEventsFunc)_on_find_related_events, CD_APPLET_CLICKED_ICON);
			s_pMenu = pAppletMenu;
			g_signal_connect (G_OBJECT (pAppletMenu), "destroy", G_CALLBACK (_on_delete_menu), NULL);
		}
	}
	CD_APPLET_LEAVE (CAIRO_DOCK_LET_PASS_NOTIFICATION);
}


void cd_on_shortkey (const char *keystring, CairoDockModuleInstance *myApplet)
{
	CD_APPLET_ENTER;
	cd_toggle_dialog ();
	CD_APPLET_LEAVE ();
}
