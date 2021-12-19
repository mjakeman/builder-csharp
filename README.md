# C# for GNOME Builder
A project to achieve first class support for C# inside GNOME Builder.

It currently includes LSP-integration for using OmniSharp with Builder.

## Usage Guide 
Note: OmniSharp's initialisation is currently very broken. You need to use this elaborate process to start Builder properly. Help wanted!

1. Download OmniSharp for Linux (net6.0 is ideal) and place it in your home folder so the path to the binary is `~/omnisharp/OmniSharp`.
2. Paste the files in this repo into `~/.local/share/gnome-builder/plugins`, making the folders if they do not exist.
3. VERY IMPORTANT: If you interact with a text buffer in Builder **at all**, OmniSharp will quit. Therefore, run builder like this:

Open a terminal so you can run builder from the command line. If you are using flatpak'd builder, open a shell inside the sandbox as follows:

```
flatpak run --command=sh org.gnome.Builder
```

Now run GNOME Builder with debug output enabled:

```
JSONRPC_DEBUG=1 gnome-builder -vvv
```

Open a folder containing a `sln` or `csproj` file. You must currently have no files open. If not, close all open files and then restart Builder.

This is very important. You must open a C# source file using the sidebar, DO NOT click or mouse over the source view, and alt-tab away immediately. A fullscreen window is a good idea to prevent accidental interaction.

Now alt-tab to the terminal and watch OmniSharp debug messages until they slow down or stop. You need to wait for all projects to be loaded before interacting.

When this is done, try hovering over a variable or type. You should see information pulled from OmniSharp, this means LSP integration is working (and ideally will work for the rest of the session). If an error about "stream failure" is thrown, time to try again :(

## Status
What works:
 - Hover support
 - Symbol resolution (e.g. Go to Definition) - really well actually

What doesn't work:
 - Consistent, predictable startup
 - Intellisense (needs fixes to Builder and/or OmniSharp)
 - Project integration (you cannot use the Build/Run buttons inside Builder, you'll need to use the `dotnet` cli for now)

## Contributing
Let's make C# development a first class experience on Linux. Contributions are welcome, especially if you want to help fix the LSP-Builder interaction bugs.

Meanwhile, if you're interested in using C# with GTK and friends, check out [gir.core](https://github.com/gircore/gir.core) and join us on matrix [#gircore](https://matrix.to/#/#gircore:matrix.org) (NOTE: You need a client with E2E support like Element or FractalNext).
