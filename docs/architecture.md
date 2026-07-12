# Architecture

## Process boundary

The wxWidgets plugin owns configuration, viewport presets, progress display,
and the handoff to OpenCPN's GRIB plugin. It does not parse NetCDF, download
model data, regrid UKV, calculate TPXO currents, or write GRIB messages.

Those operations run in the `environmental-grib` helper process. The plugin
writes a schema-versioned job file, starts the helper asynchronously, consumes
JSON-lines progress, and reads an atomically written result file. Crashes or
format errors in provider code therefore do not execute in OpenCPN's address
space.

Passwords are supplied only through a named child-process environment
variable. Logs, job files, and displayed commands redact credentials and
credential-like URL query parameters.

## Runtime layout

On Linux the catalogue payload uses this private layout:

```text
share/opencpn/plugins/environmental_grib_pi/
  bin/environmental-grib          launcher
  libexec/environmental-grib.bin  native helper
  runtime/lib/                    non-system shared libraries
  runtime/share/eccodes/          GRIB definitions and samples
  runtime/share/proj/             PROJ database
  data/                            toolbar resources
```

The launcher sets private runtime search paths before executing the helper.
It does not alter OpenCPN's library path. The plugin itself links only against
the OpenCPN API, wxWidgets, wxJSON, zlib, and bzip2.

## Compatibility boundary

The plugin checks helper capabilities before generation. Job schema version 1
is independent of the graphical UI. Unknown options and schema versions fail
before downloads or output creation. A result file is written for both
success and failure where practical.

The generated output is a standards-based GRIB stream. Opening it does not
require a modified OpenCPN core. Automatic handoff uses an optional plugin
message; when a stock GRIB plugin does not implement that message, the UI
instructs the user to use **Open GRIB**.

## Platform scope

The first catalogue-ready target is Linux x86_64/GTK3. The source and process
protocol are portable, but Windows and macOS need native dependency builds,
runtime bundling, signing, and catalogue CI validation before release assets
for those platforms are published.
