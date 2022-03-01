/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2022 System76, Inc
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Ian Douglas Scott <idscott@system76.com>
 */

#include "cc-desktop-main-panel.h"
#include "cc-util.h"

#include <handy.h>
#include <pop_desktop_widget.h>

struct _CcDesktopMainPanel
{
  CcPanel        parent_instance;

  GtkWidget     *widget;
};

CC_PANEL_REGISTER (CcDesktopMainPanel, cc_desktop_main_panel)

static void
cc_desktop_panel_finalize (GObject *object)
{
  CcDesktopMainPanel *self = CC_DESKTOP_MAIN_PANEL (object);

  g_clear_object (&self->widget);

  G_OBJECT_CLASS (cc_desktop_main_panel_parent_class)->finalize (object);
}

static void
cc_desktop_main_panel_class_init (CcDesktopMainPanelClass *klass)
{
  GObjectClass *oclass = G_OBJECT_CLASS (klass);
  oclass->finalize = cc_desktop_panel_finalize;
}

static void
cc_desktop_main_panel_init (CcDesktopMainPanel *self)
{
  GtkWidget *clamp, *box;

  clamp = g_object_new (HDY_TYPE_CLAMP,
                        "visible", TRUE,
                        NULL);
  gtk_container_add (GTK_CONTAINER (self), clamp);

  box = g_object_new (GTK_TYPE_BOX,
                      "visible", TRUE,
                      "can-focus", FALSE,
                      "spacing", 24,
                      "margin-start", 12,
                      "margin-end", 12,
                      "margin-top", 18,
                      "margin-bottom", 18,
                      "hexpand", TRUE,
                      NULL);
  gtk_container_add (GTK_CONTAINER (clamp), box);

  gtk_container_add (GTK_CONTAINER (box), pop_desktop_widget_gcc_main_page());
}
