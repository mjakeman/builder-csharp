import threading
import os

from gi.repository import Gio
from gi.repository import GLib
from gi.repository import GObject
from gi.repository import Ide

_ = Ide.gettext

_DOTNET = 'dotnet'

class MsbuildBuildSystemDiscovery(Ide.SimpleBuildSystemDiscovery):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.props.glob = '*.csproj'
        self.props.hint = 'msbuild_plugin'
        self.props.priority = 2000

class MsbuildBuildSystem(Ide.Object, Ide.BuildSystem):
    project_file = GObject.Property(type=Gio.File)

    def do_get_id(self):
        return 'msbuild'

    def do_get_display_name(self):
        return 'MSBuild'

    def do_get_priority(self):
        return 2000
        
    def do_supports_language(self, language):
        return language in ('c-sharp',)
        
def locate_dotnet_from_config(config):
    dotnet = _DOTNET

    if config:
        runtime = config.get_runtime()
        if config.getenv('DOTNET_ROOT'):
            cargo = os.path.join(config.getenv('DOTNET_ROOT'), 'dotnet')
        elif not runtime or not runtime.contains_program_in_path(_DOTNET):
            dotnet_in_home = os.path.expanduser('~/.dotnet/dotnet')
            if os.path.exists(dotnet_in_home):
                dotnet = dotnet_in_home

    return dotnet


class MsbuildPipelineAddin(Ide.Object, Ide.PipelineAddin):
    """
    The MsbuildPipelineAddin is responsible for creating the necessary build
    stages and attaching them to phases of the build pipeline.
    """

    def do_load(self, pipeline):
        context = self.get_context()
        build_system = Ide.BuildSystem.from_context(context)

        if type(build_system) != MsbuildBuildSystem:
            return
            
        project_file = build_system.props.project_file
#        if project_file.get_basename() != 'Cargo.toml':
#            project_file = project_file.get_child('Cargo.toml')

        project_dir = os.path.dirname(project_file.get_path())
        config = pipeline.get_config()
        builddir = pipeline.get_builddir()
        runtime = config.get_runtime()
        srcdir = pipeline.get_srcdir()
        config_opts = config.get_config_opts()

        # We might need to use dotnet cli from ~/.dotnet/
        dotnet = locate_dotnet_from_config(config)

        # Fetch dependencies so that we no longer need network access
        fetch_launcher = pipeline.create_launcher()
        fetch_launcher.set_cwd(srcdir)
        fetch_launcher.push_argv(dotnet)
        fetch_launcher.push_argv('restore')
        self.track(pipeline.attach_launcher(Ide.PipelinePhase.DOWNLOADS, 0, fetch_launcher))

        build_launcher = pipeline.create_launcher()
        build_launcher.set_cwd(srcdir)
        build_launcher.push_argv(dotnet)
        build_launcher.push_argv('build')

        clean_launcher = pipeline.create_launcher()
        clean_launcher.set_cwd(srcdir)
        clean_launcher.push_argv(dotnet)
        clean_launcher.push_argv('clean')

        build_stage = Ide.PipelineStageLauncher.new(context, build_launcher)
        build_stage.set_name(_("Building project"))
        build_stage.set_clean_launcher(clean_launcher)
        build_stage.connect('query', self._query)
        self.track(pipeline.attach(Ide.PipelinePhase.BUILD, 0, build_stage))

        install_launcher = pipeline.create_launcher()
        install_launcher.set_cwd(srcdir)
        install_launcher.push_argv(dotnet)
        install_launcher.push_argv('publish')
#        install_launcher.push_argv('-Dmaven.test.skip=true')
        install_stage = Ide.PipelineStageLauncher.new(context, install_launcher)
        install_stage.set_name(_("Installing project"))
        self.track(pipeline.attach(Ide.PipelinePhase.INSTALL, 0, install_stage))

    def _query(self, stage, pipeline, targets, cancellable):
        stage.set_completed(False)

class MsbuildBuildTarget(Ide.Object, Ide.BuildTarget):

    def do_get_install_directory(self):
        return None

    def do_get_name(self):
        return 'dotnet-run'

    def do_get_language(self):
        return 'c-sharp'

    def do_get_cwd(self):
        context = self.get_context()
        project_file = Ide.BuildSystem.from_context(context).project_file
        if project_file.query_file_type(0, None) == Gio.FileType.DIRECTORY:
            return project_file.get_path()
        else:
            return project_file.get_parent().get_path()

    def do_get_argv(self):
        return ["dotnet", "run"]

    def do_get_argv(self):
        context = self.ref_context()
        config_manager = Ide.ConfigManager.from_context(context)
        config = config_manager.get_current()
        dotnet = locate_dotnet_from_config(config)

        return [dotnet, 'run']


    def do_get_priority(self):
        return 0

class MsbuildBuildTargetProvider(Ide.Object, Ide.BuildTargetProvider):

    def do_get_targets_async(self, cancellable, callback, data):
        task = Ide.Task.new(self, cancellable, callback)
        task.set_priority(GLib.PRIORITY_LOW)

        context = self.get_context()
        build_system = Ide.BuildSystem.from_context(context)

        if type(build_system) != MsbuildBuildSystem:
            task.return_error(GLib.Error('Not msbuild build system',
                                         domain=GLib.quark_to_string(Gio.io_error_quark()),
                                         code=Gio.IOErrorEnum.NOT_SUPPORTED))
            return

        task.targets = [build_system.ensure_child_typed(MsbuildBuildTarget)]
        task.return_boolean(True)

    def do_get_targets_finish(self, result):
        if result.propagate_boolean():
            return result.targets
