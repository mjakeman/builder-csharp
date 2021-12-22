/* csls-service.c
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

#include "csls-service.h"

#include <libide-lsp.h>

#define G_LOG_DOMAIN "csls-service"

struct _CslsService
{
  IdeLspService parent_instance;
};

G_DEFINE_FINAL_TYPE (CslsService, csls_service, IDE_TYPE_LSP_SERVICE)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

CslsService *
csls_service_new (void)
{
  return g_object_new (CSLS_TYPE_SERVICE, NULL);
}

static void
csls_service_finalize (GObject *object)
{
  CslsService *self = (CslsService *)object;

  G_OBJECT_CLASS (csls_service_parent_class)->finalize (object);
}

static void
csls_service_configure_client (IdeLspService *self,
                               IdeLspClient  *client)
{
  g_info ("Configure CSLS Service Client");
  ide_lsp_client_add_language (client, "c-sharp");
}

static void
csls_service_configure_launcher (IdeLspService         *self,
                                 IdeSubprocessLauncher *launcher)
{
  g_info ("Configure CSLS Service Launcher");
  ide_subprocess_launcher_set_argv (launcher, NULL);
  // ide_subprocess_launcher_set_run_on_host (launcher, TRUE);
  ide_subprocess_launcher_set_clear_env (launcher, FALSE);

  ide_subprocess_launcher_push_argv (launcher, "/bin/bash");
  ide_subprocess_launcher_push_argv (launcher, "--login");
  ide_subprocess_launcher_push_argv (launcher, "-c");
  ide_subprocess_launcher_push_argv (launcher, "$HOME/Projects/csharp-language-server/src/CSharpLanguageServer/bin/Debug/net6.0/CSharpLanguageServer");
}


static void
csls_service_class_init (CslsServiceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = csls_service_finalize;

  IdeLspServiceClass *lsp_service_class = IDE_LSP_SERVICE_CLASS (klass);

  lsp_service_class->configure_launcher = csls_service_configure_launcher;
  lsp_service_class->configure_client = csls_service_configure_client;
}

static void
csls_service_init (CslsService *self)
{
  g_info ("Initialised CSLS Service");
  ide_lsp_service_set_inherit_stderr (IDE_LSP_SERVICE (self), TRUE);
}
