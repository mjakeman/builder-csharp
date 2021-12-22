sources = [
    'csls-plugin.c',
    'csls-service.c',
    'csls-symbol-resolver.c'
]

plugin_dir = 'lib' / 'gnome-builder' / 'plugins'

shared_library(
    'csls',
    sources,
    dependencies : deps,
    install : true,
    install_dir : plugin_dir
)

install_data('csls.plugin', install_dir : plugin_dir)
