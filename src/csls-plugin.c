/* csls-plugin.c
 *
 * Copyright 2021 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define G_LOG_DOMAIN "csls-plugin"

#include <glib-object.h>
#include <libpeas/peas.h>
#include <libide-code.h>
#include <libide-foundry.h>
#include <libide-gui.h>

_IDE_EXTERN void
peas_register_types (PeasObjectModule *module)
{

  // ide_g_file_add_ignored_pattern (".flatpak-builder");

  g_info ("Initialised csls for builder\n");

  /*peas_object_module_register_extension_type (module,
                                              IDE_TYPE_BUILD_SYSTEM_DISCOVERY,
                                              GBP_TYPE_FLATPAK_BUILD_SYSTEM_DISCOVERY);
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_BUILD_TARGET_PROVIDER,
                                              GBP_TYPE_FLATPAK_BUILD_TARGET_PROVIDER);
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_CONFIG_PROVIDER,
                                              GBP_TYPE_FLATPAK_CONFIG_PROVIDER);
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_DEPENDENCY_UPDATER,
                                              GBP_TYPE_FLATPAK_DEPENDENCY_UPDATER);
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_RUNTIME_PROVIDER,
                                              GBP_TYPE_FLATPAK_RUNTIME_PROVIDER);
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_PIPELINE_ADDIN,
                                              GBP_TYPE_FLATPAK_PIPELINE_ADDIN);*/
}

