/* csls-search-provider.c
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

#include "csls-search-provider.h"
#include "csls-service.h"

#define G_LOG_DOMAIN "csls-search-provider"

struct _CslsSearchProvider
{
  IdeLspSearchProvider parent_instance;
};

static void search_iface_init (IdeSearchProviderInterface *iface);

G_DEFINE_FINAL_TYPE_WITH_CODE (CslsSearchProvider,
                               csls_search_provider,
                               IDE_TYPE_LSP_SEARCH_PROVIDER,
                               G_IMPLEMENT_INTERFACE (IDE_TYPE_SEARCH_PROVIDER, search_iface_init))

static void
csls_search_provider_class_init (CslsSearchProviderClass *klass)
{
}

static void
csls_search_provider_init (CslsSearchProvider *self)
{
  g_info ("Initialised CSLS Search Provider");
}

static void
csls_search_provider_load (IdeSearchProvider *self,
                           IdeContext        *context)
{
  g_info ("Bound Search Provider to CSLS Service");
  CslsServiceClass *klass = g_type_class_ref (CSLS_TYPE_SERVICE);
  ide_lsp_service_class_bind_client (klass, self);
  g_type_class_unref (klass);
}

static void
search_iface_init (IdeSearchProviderInterface *iface)
{
  iface->load = csls_search_provider_load;
}

