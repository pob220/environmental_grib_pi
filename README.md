# EnvironmentalGRIB for OpenCPN

EnvironmentalGRIB is a companion plugin which downloads, converts, merges,
and validates weather, wave, ocean-current, and astronomical tidal-current
model data as an OpenCPN-compatible GRIB file. The stock OpenCPN GRIB plugin
remains responsible for displaying the resulting file.

The provider/conversion engine is a pinned native C++ helper. It runs outside
the OpenCPN process, uses a versioned JSON job protocol, reports structured
progress, and never places Copernicus passwords in command arguments or job
files.

## Supported sources

- Weather: NOAA GFS and HRRR, Met Office UKV, DWD ICON-EU, ECMWF IFS/AIFS
  Open Data, or an existing GRIB.
- Waves: NOAA GFS Wave and Copernicus Marine Global Waves.
- Currents: TPXO10 local model/cache, Marine.ie Irish Sea, NOAA RTOFS,
  Copernicus NWS/Global, an existing GRIB, NetCDF, or synthetic test data.

Some sources require provider credentials or separately licensed local model
data. These are not bundled with the plugin.

## Build

```sh
git clone --recurse-submodules \
  https://github.com/pob220/environmental_grib_pi.git
cd environmental_grib_pi
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$(nproc)"
ctest --test-dir build --output-on-failure
```

Linux catalogue builds bundle the helper's non-system runtime libraries and
ecCodes/PROJ data by default. Configure with
`-DBUNDLE_GENERATOR_RUNTIME=OFF` only for developer/system-package builds
which explicitly provide those dependencies.

## Architecture and testing

See [docs/architecture.md](docs/architecture.md) and
[docs/catalogue-release.md](docs/catalogue-release.md). The native helper and
its protocol are maintained in the
[environmental-grib-generator](https://github.com/pob220/environmental-grib-generator)
repository and pinned here as a submodule.

Generated model data is for planning and experimentation. It is not an
official navigation product and does not replace notices to mariners,
observations, forecasts, or prudent seamanship.

## License

Plugin code is GPL-3.0-or-later. The native helper is MIT licensed. Bundled
third-party components retain their respective licenses.
