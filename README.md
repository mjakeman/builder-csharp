# C# for GNOME Builder
A project to achieve first class support for C# inside GNOME Builder.

The language server [csharp-ls](https://github.com/razzmatazz/csharp-language-server) is used to
provide symbol and metadata information. Ideally, we will one day support OmniSharp, however
various desync bugs makes it near-unusable in the mean time.

`builder-csharp` is packaged as a flatpak extension to GNOME Builder.

## Prerequisites
The `csharp-ls` language server is used. Clone the `csharp-ls` build repository
at the PATH `~/Projects`. Build it and ensure the `CSharpLanguageServer` executable
can be found at the path `$HOME/Projects/csharp-language-server/src/CSharpLanguageServer/bin/Debug/net6.0/CSharpLanguageServer`.

In future, the language server will be included inside the flatpak sandbox.

## Building
You will need the latest `master` version of GNOME Builder. You can obtain it
from the `gnome-nightly` flatpak repository.

Dependencies:
 1. Latest GNOME Builder from `gnome-nightly` flatpak repo installed
 2. `org.freedesktop.Sdk.Extension.dotnet6` installed from `flathub`
 3. `flatpak-builder`
 
Run the following to build and install the plugin:

```
flatpak-builder _build --install --force-clean org.gnome.Builder.Plugin.CSharp.json
```

You can uninstall the plugin at any time and reset to a "clean slate":

```
flatpak remove org.gnome.Builder.Plugin.CSharp
```

## Contributing
Let's make C# development a first class experience on Linux. Contributions are welcome, especially if you want to help fix the LSP-Builder interaction bugs.

Meanwhile, if you're interested in using C# with GTK and friends, check out [gir.core](https://github.com/gircore/gir.core) and join us on matrix [#gircore](https://matrix.to/#/#gircore:matrix.org) (NOTE: You need a client with E2E support like Element or FractalNext).
