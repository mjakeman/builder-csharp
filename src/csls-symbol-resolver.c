/* csls-symbol-resolver.c
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

#include "csls-symbol-resolver.h"
#include "csls-service.h"

#define G_LOG_DOMAIN "csls-symbol-resolver"

struct _CslsSymbolResolver
{
  IdeLspSymbolResolver parent_instance;
};

static void symbol_iface_init (IdeSymbolResolverInterface *iface);

G_DEFINE_FINAL_TYPE_WITH_CODE (CslsSymbolResolver,
                               csls_symbol_resolver,
                               IDE_TYPE_LSP_SYMBOL_RESOLVER,
                               G_IMPLEMENT_INTERFACE (IDE_TYPE_SYMBOL_RESOLVER, symbol_iface_init))

static void
csls_symbol_resolver_class_init (CslsSymbolResolverClass *klass)
{
}

static void
csls_symbol_resolver_init (CslsSymbolResolver *self)
{
  g_info ("Initialised CSLS Symbol Resolver");
}

static void
csls_symbol_resolver_load (IdeSymbolResolver *self)
{
  g_info ("Bound Symbol Resolver to CSLS Service");
  CslsServiceClass *klass = g_type_class_ref (CSLS_TYPE_SERVICE);
  ide_lsp_service_class_bind_client (klass, self);
  g_type_class_unref (klass);
}

static void
symbol_iface_init (IdeSymbolResolverInterface *iface)
{
  iface->load = csls_symbol_resolver_load;
}

