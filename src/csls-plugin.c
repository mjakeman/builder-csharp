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

#include "csls-service.h"
#include "csls-symbol-resolver.h"
#include "csls-hover-provider.h"
#include "csls-search-provider.h"

_IDE_EXTERN void
peas_register_types (PeasObjectModule *module)
{
  g_info ("CSLS for Builder");

  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_LSP_SERVICE,
                                              CSLS_TYPE_SERVICE);

  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_SYMBOL_RESOLVER,
                                              CSLS_TYPE_SYMBOL_RESOLVER);

  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_HOVER_PROVIDER,
                                              CSLS_TYPE_HOVER_PROVIDER);

  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_SEARCH_PROVIDER,
                                              CSLS_TYPE_SEARCH_PROVIDER);
}

