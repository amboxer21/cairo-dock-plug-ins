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


#ifndef __APPLET_RAYS__
#define  __APPLET_RAYS__


#include <cairo-dock.h>


#define cd_animations_load_rays_texture(...) CD_APPLET_LOAD_LOCAL_TEXTURE ("ray.png")


gboolean cd_animations_update_rays_system (CairoParticleSystem *pParticleSystem, gboolean bContinue);


CairoParticleSystem *cd_animations_init_rays (Icon *pIcon, CairoDock *pDock, double dt);


void cd_animations_rewind_rays_particle (CairoParticle *p, double dt, double fHeight);


#endif
