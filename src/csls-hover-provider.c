/* csls-hover-provider.c
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

#include "csls-hover-provider.h"
#include "csls-service.h"

#define G_LOG_DOMAIN "csls-symbol-resolver"

struct _CslsHoverProvider
{
  IdeLspHoverProvider parent_instance;
};

G_DEFINE_FINAL_TYPE (CslsHoverProvider, csls_hover_provider, IDE_TYPE_LSP_HOVER_PROVIDER)

static void
csls_hover_provider_finalize (GObject *object)
{
  CslsHoverProvider *self = (CslsHoverProvider *)object;

  G_OBJECT_CLASS (csls_hover_provider_parent_class)->finalize (object);
}

static void
csls_hover_provider_prepare (IdeLspHoverProvider *self)
{
  g_object_set (self,
                "category", "c-sharp",
                "priority", 200,
                NULL);

  g_info ("Bound Hover Provider to CSLS Service");
  CslsServiceClass *klass = g_type_class_ref (CSLS_TYPE_SERVICE);
  ide_lsp_service_class_bind_client (klass, self);
  g_type_class_unref (klass);
}

static void
csls_hover_provider_class_init (CslsHoverProviderClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = csls_hover_provider_finalize;

  IdeLspHoverProviderClass *lsp_class = IDE_LSP_HOVER_PROVIDER_CLASS (klass);

  lsp_class->prepare = csls_hover_provider_prepare;
}

static void
csls_hover_provider_init (CslsHoverProvider *self)
{
  g_info ("Initialised CSLS Hover Provider");
}
