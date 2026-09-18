# SpiceQL

[SpiceQL Manual](https://astrogeology.usgs.gov/docs/manuals/spiceql/) ([0.1 Archive](http://sugar-spice.readthedocs.io/?badge=latest))

This Library provides a C++ interface querying, reading and writing Naif SPICE kernels. Built on the [Naif Toolkit](https://naif.jpl.nasa.gov/naif/toolkit.html).

Check out the Astrogeology Software Docs for SpiceQL examples:

- [Cassini Tutorial](https://astrogeology.usgs.gov/docs/getting-started/using-spiceql/spiceql-cassini-tutorial/)
- [pyspiceql Visualization](https://astrogeology.usgs.gov/docs/getting-started/using-spiceql/visualizing-with-pyspiceql-tutorial/)
- [REST, Python, C++ API](https://astrogeology.usgs.gov/docs/getting-started/using-spiceql/spiceql-cassini-tutorial/)
- [WebAssembly Bindings](https://astrogeology.usgs.gov/docs/getting-started/using-spiceql/spiceql-wasm/)
- [Use with Other Libraries](https://astrogeology.usgs.gov/docs/how-to-guides/SPICE/using-spiceql-with-other-libraries/)
- [Use in USGS ISIS and ALE](https://astrogeology.usgs.gov/docs/how-to-guides/SPICE/using-web-spice-in-isis-and-ale/)

NAIF Resources - Learn more about the Kernels and SPICE Information that SpiceQL queries:

- [Intro to Kernels (PDF)](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/12_intro_to_kernels)
- [SPICE Required Reading](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/index.html)

## Building The Library

### Prerequisites

#### Conda

SpiceQL uses conda to maintain dependencies.
If you don't have conda yet, we recommend installing it 
via [Miniforge](https://github.com/conda-forge/miniforge):

```sh
curl -L -O "https://github.com/conda-forge/miniforge/releases/latest/download/Miniforge3-$(uname)-$(uname -m).sh"
bash Miniforge3-$(uname)-$(uname -m).sh
```

#### Kernels

If you have ISIS and haven't downloaded kernels, use the [`downloadIsisData` command](https://astrogeology.usgs.gov/docs/how-to-guides/environment-setup-and-maintenance/isis-data-area/).

If you don't have ISIS, you can still use the script by downloading 
[the downloadIsisData script](https://raw.githubusercontent.com/USGS-Astrogeology/ISIS3/dev/isis/scripts/downloadIsisData) 
and the [rclone.conf](https://raw.githubusercontent.com/USGS-Astrogeology/ISIS3/dev/isis/config/rclone.conf).
You will need to have [rclone](https://rclone.org/install/) and python installed to run the script.

### Cloning and Building

```bash
# Clone the repo, including submodules. -j8 parellelizes for a faster clone.
git clone --recurse-submodules -j8 https://github.com/DOI-USGS/SpiceQL.git
# To clone submodules later: git submodule update --init --recursive

# Open the newly cloned repo
cd SpiceQL

# Create conda env from environment.yml 
# -n <env-name>, any name is fine.
conda env create -f environment.yml -n ssdev

# activate the new env
conda activate ssdev

# make and cd into the build directory.
mkdir build
cd build

# Configure the project, install directory can be anything, here, it's the conda env
cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX

# Optional: DB files are installed by default in $CONDA_PREFIX/etc/SpiceQL/db.
# To use files included in the repo, set env var SPICEQL_DEV_DB=True.
export SPICEQL_DEV_DB=True

# Set the environment variable(s) to point to your kernel data.
# The following env vars are used by default in order of priority: 
# (1) $SPICEROOT, (2) $ALESPICEROOT, (3) $ISISDATA.
SPICEROOT=/data/kernels/
# ALESPICEROOT=/data/kernels/
# ISISDATA=/data/kernels/

# build and install project
make install

# Optional, Run tests
ctest -j8
```

You can disable different components of the build by setting the CMAKE variables `SPICEQL_BUILD_DOCS`, `SPICEQL_BUILD_TESTS`, `SPICEQL_BUILD_BINDINGS`, or `SPICEQL_BUILD_LIB` to `OFF`. For example, the following cmake configuration command will not build the documentation or the tests:

```
cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX -DSPICEQL_BUILD_DOCS=OFF -DSPICEQL_BUILD_TESTS=OFF
```

## Bindings

The SpiceQL API is available via Python bindings in the module `pyspiceql`. The bindings are built using SWIG and are on by default. You can disable the bindings in your build by setting `SPICEQL_BUILD_BINDINGS` to `OFF` when configuring your build.

## WebAssembly / JavaScript

See Also: [SpiceQL WebAssembly Bindings](https://astrogeology.usgs.gov/docs/getting-started/using-spiceql/spiceql-wasm/)

### Setup/Installation Options

#### [GitHub Releases (Manual Download) ↗](https://github.com/DOI-USGS/SpiceQL/releases)

#### NPM Installation

```sh
# In your terminal in your project directory:
npm install @usgs-astrogeology/spiceql
```

```js
// In your javascript:
import { loadSpiceQL } from '@usgs-astrogeology/spiceql'
```

*A Module Bundler, like Vite, is required for this kind of import.*


#### Import from CDN (jsDelivr)

```js
// In your javascript:
import { loadSpiceQL } from 'https://cdn.jsdelivr.net/npm/@usgs-astrogeology/spiceql/dist/spiceql.js';
```


### Building locally

The `emscripten` dependency in `environment.yml` provides `emcc`/`emcmake` (and Node), so the conda env from [Building The Library](#building-the-library) already has everything needed.

Configure with `emcmake` (which injects the Emscripten toolchain file) and build:

```bash
conda activate ssdev            # the env you created above

# A conda env exports host (macOS/Linux) CFLAGS/CXXFLAGS/CPPFLAGS/LDFLAGS that are
# invalid for the Emscripten cross-compile and break wasm-ld. Clear them first.
unset CFLAGS CXXFLAGS CPPFLAGS LDFLAGS

emcmake cmake -S . -B build-wasm \
  -DCMAKE_BUILD_TYPE=Release \
  -DSPICEQL_WASM=ON \
  -DSPICEQL_BUILD_TESTS=OFF \
  -DSPICEQL_BUILD_BINDINGS=ON

cmake --build build-wasm -j"$(getconf _NPROCESSORS_ONLN)"
```
*If you get a permission denied error, use a lower number of cores in the last command: `-j4` or `-j1` instead of `-j"$(getconf _NPROCESSORS_ONLN)"`*

#### CMake Options:

| Option | Value | Why |
| --- | --- | --- |
| `SPICEQL_WASM` | `ON` | Selects the WASM build: excludes HDF5/HighFive and libcurl, builds CSPICE from source (patched for wasm-ld), and links everything static. Auto-forced `ON` under `emcmake` anyway. |
| `SPICEQL_BUILD_BINDINGS` | `ON` | Builds `bindings/wasm` (the Embind module + `naifspice` namespace) instead of the native language bindings. |
| `SPICEQL_BUILD_TESTS` | `OFF` | The C++ gtests are native-only; the WASM surface is exercised by the JS suite (`npm test`) instead. |
| `CMAKE_BUILD_TYPE` | `Release` | Optimized module. |

This produces the module in `build-wasm/bindings/wasm/`:

- `spiceql_wasm.js`   — the Emscripten loader (ES module)
- `spiceql_wasm.wasm` — the compiled WebAssembly
- `spiceql_wasm.data` — preloaded config DB, bundled leap-second kernel, and the
  `naifspice` signature table

The small hand-written wrappers `bindings/wasm/spiceql.js` (which you import) and
`bindings/wasm/naifspice.js` (the raw-CSPICE marshaller it uses) sit on top of those.

### Using it (minimal example)

Copy the three `spiceql_wasm.*` artifacts and both wrappers (`bindings/wasm/spiceql.js` and `bindings/wasm/naifspice.js`) next to each other (they must be co-located — `spiceql.js` imports the other two), then import `spiceql.js` locally:

```js
// example.js — run with: node example.js

import { readFileSync } from 'node:fs';
import { loadSpiceQL } from './spiceql.js';

const spiceql = await loadSpiceQL();

const frameCode = -85;              
const sclkTime = 922997380.174174;  // We'll use SpiceQL to convert Sclk to ET

// Mount Kernels
const kernelList = [];
const kernelUrls = [
    './data/base/kernels/lsk/naif0012.tls',
    './data/lro/kernels/fk/lro_frames_2014049_v01.tf',
    './data/lro/kernels/sclk/lro_clkcor_2024262_v00.tsc',
]
for (const url of kernelUrls) {
    const kernelPath = '/kernels/' + url.split('/').pop();    // Get filename, discard path
    spiceql.mountKernel(kernelPath, readFileSync(url));       // Mount as sanitized path
    kernelList.push(kernelPath)                               // Add sanitized path to list
}

// Convert Spacecraft Clock Time (sclk) to Ephemeris Time (et)
const { result: ephTime } = spiceql.doubleSclkToEt(frameCode, sclkTime, {
    mission: 'lro',
    searchKernels: false,
    kernelList,
});
console.info("Ephemeris Time", ephTime);
```

In a browser it works the same way — `import` `spiceql.js` in a
`<script type="module">` and use `fetch()` to get kernel bytes for `mountKernel`.
The five files (`spiceql.js`, `naifspice.js`, `spiceql_wasm.js`,
`spiceql_wasm.wasm`, `spiceql_wasm.data`) and your kernels just need to be
served over HTTP from the same folder (any static host works; opening the page from `file://` does not,
because the browser blocks `fetch()`):

```html
<!doctype html>
...
<script type="module">
    // Import and Load SpiceQL
    import { loadSpiceQL } from 'https://cdn.jsdelivr.net/npm/@usgs-astrogeology/spiceql/dist/spiceql.js';

    const spiceqlBasePath = 'https://cdn.jsdelivr.net/npm/@usgs-astrogeology/spiceql/dist/';
    const spiceql = await loadSpiceQL({
        moduleOverrides: { locateFile: (path) => spiceqlBasePath + path }
    });

    // Mount Kernels
    const kernelList = [];
    const kernelUrls = [
        'https://asc-isisdata.s3.us-west-2.amazonaws.com/usgs_data/base/kernels/lsk/naif0012.tls',
        'https://asc-isisdata.s3.us-west-2.amazonaws.com/usgs_data/lro/kernels/fk/lro_frames_2014049_v01.tf',
        'https://asc-isisdata.s3.us-west-2.amazonaws.com/usgs_data/lro/kernels/sclk/lro_clkcor_2024262_v00.tsc',
    ]
    for (const url of kernelUrls) {
        const kernelData = await fetch(url);                              // Fetch
        const kernelBuff = new Uint8Array(await kernelData.arrayBuffer()) // Load into Buffer
        const kernelPath = '/kernels/' + url.split('/').pop();            // Get filename, discard path
        spiceql.mountKernel(kernelPath, kernelBuff);                      // Mount as sanitized path
        kernelList.push(kernelPath)                                       // Add sanitized path to list
    }

    // Data to query with
    const frameCode = -85;
    const sclkTime = 922997380.174174;

    // Convert Spacecraft Clock Time (sclk) to Ephemeris Time (et)
    const { result: ephTime } = spiceql.doubleSclkToEt(frameCode, sclkTime, {
        mission: 'lro',
        searchKernels: false,
        kernelList,
    });
    console.info("Ephemeris Time", ephTime);
</script>
...
```

```bash
# serve the folder over HTTP, then open http://localhost:8000
python -m http.server
```

#### Raw CSPICE toolkit (`naifspice`)

Every CSPICE `*_c` function can be exposed as a JS function so you can call the
toolkit directly instead of going through the higher-level `api.h` helpers. These
wrappers are **generated at build time** by parsing CSPICE's headers.

The namespace is **opt-in**: `loadSpiceQL()` does not build it, so the ~650
wrappers are only generated when you actually want the raw toolkit. Import
`naifspice.js` and call `loadNaifspice()` with the object `loadSpiceQL()`
returned (it also attaches the result as `spiceql.naifspice`). Here is the whole
flow — load, furnish a kernel, and convert a UTC string to ET with `str2et`:

```js
import { loadSpiceQL } from './spiceql.js';
import { loadNaifspice } from './naifspice.js';
import { readFileSync } from 'node:fs';

const spiceql = await loadSpiceQL();
const nspice = loadNaifspice(spiceql);               // build + attach spiceql.naifspice

// Furnish a leap-second kernel, then convert a UTC string to ET.
spiceql.mountKernel('/kernels/naif0012.tls', readFileSync('naif0012.tls'));
nspice.furnsh('/kernels/naif0012.tls');
const et = nspice.str2et('2000 JAN 01 12:00:00');    // 64.18... ET seconds past J2000
```

Most functions get an *ergonomic* wrapper: pass the CSPICE **input** arguments in
order as plain JS values (numbers, strings, and arrays for vectors/matrices), and
the **outputs** are returned. A single output is returned directly; several are
returned as an object keyed by the CSPICE parameter name; a non-`void` C return
value joins that object under `return`. 

```js
nspice.et2utc(et, 'ISOC', 3, 32);                    // '2000-01-01T12:00:00.000'

const { radius, longitude, latitude } = ns.reclat([1, 1, 0]); // several outputs -> object
const R = ns.pxform('J2000', 'J2000', et);       // matrix output -> nested array (identity)
const { name, found } = ns.bodc2n(399, 32);      // { name: 'EARTH', found: true }
```

A signalled SPICE error is thrown as a JS `Error` carrying the SPICE short and
long messages, and the toolkit is reset so the module stays usable afterward.

A minority of functions (those using CSPICE aggregate types like `SpiceCell`,
callbacks, or output buffers whose size is only known at runtime) cannot be
marshalled automatically. They are still callable in **raw** form under their
literal CSPICE name (with the `_c` suffix) at `spiceql.naifspice.raw.<fn>_c`,
where every argument is passed straight through as a number (pointers are
addresses). Manage memory yourself with the helpers on the namespace — `malloc`,
`free`, `getValue`, `setValue`, `toCString`, `fromCString`:

```js
const { malloc, free, setValue, getValue } = ns;
const vin = malloc(3 * 8), vout = malloc(3 * 8);
for (let i = 0; i < 3; i++) setValue(vin + i * 8, i + 1, 'double');
ns.raw.vsclg_c(2.0, vin, 3, vout);               // scale [1,2,3] by 2 (ndim=3)
const scaled = [0, 1, 2].map((i) => getValue(vout + i * 8, 'double')); // [2, 4, 6]
free(vin); free(vout);
```

The suffix-dropped top-level name of a raw-only function forwards to its raw
form, so `ns.bodvrd === ns.raw.bodvrd_c`.

#### Managing kernels manually (KernelSet / load / unload)

Passing `kernelList` furnishes and unfurnishes those kernels for the duration of a single call. If you want to furnish a set of kernels once and reuse them across many calls, manage the CSPICE pool yourself. Any call made with `searchKernels:false` and no `kernelList` uses whatever is already furnished.

`spiceql.KernelSet` is the RAII helper: constructing it furnishes the kernels, and `unload()` unfurnishes them. It accepts an array of kernel paths (grouped by type automatically) or a `{ type: [paths] }` object.

```js
import { loadSpiceQL } from './spiceql.js';
import { readFileSync } from 'node:fs';

const spiceql = await loadSpiceQL();
spiceql.mountKernel('/kernels/naif0012.tls', readFileSync('naif0012.tls'));
spiceql.mountKernel('/kernels/lro.tsc', readFileSync('lro_clkcor_2020184_v00.tsc'));

// Furnish a set once...
const ks = new spiceql.KernelSet(['/kernels/naif0012.tls', '/kernels/lro.tsc']);

// ...then make as many calls as you like with searchKernels:false and no
// kernelList; they read the kernels already in the pool.
const opts = { searchKernels: false };
const et = spiceql.strSclkToEt(-85, '1/281199081:48971', opts).result;
const utc = spiceql.etToUtc(et, { ...opts, format: 'ISOC', precision: 3 }).result;
console.log(spiceql.getLoadedKernels());   // ['/kernels/naif0012.tls', '/kernels/lro.tsc']

// Unfurnish when done. KernelSet is a C++ object, so free it explicitly
// (garbage collection will NOT do it for you): unload() then delete().
ks.unload();
ks.delete();

// A subsequent pool-only call now fails because nothing is furnished:
try {
  spiceql.strSclkToEt(-85, '1/281199081:48971', opts);
} catch (e) {
  console.error(e.message);  // SPICE(KERNELVARNOTFOUND) ...
}
```

For finer control there are also free functions that furnish/unfurnish individual kernels: `spiceql.load(path)`, `spiceql.unload(path)`, `spiceql.getLoadedKernels()`, and `spiceql.isLskLoaded()`.

Notes:
- Kernel **search** throws in the WASM build (no HDF5 inventory) — always pass an explicit `kernelList` with `searchKernels:false`, or furnish kernels yourself.
- A `KernelSet` (and any Embind object) must be freed with `.delete()`; it is not garbage-collected. `unload()` unfurnishes the kernels but keeps the object usable (you can `load()` more into it).
- The remote REST transport (`useWeb:true`) is **not supported** in the WASM build and throws. Awaiting `fetch()` from inside wasm would require suspending the stack (JSPI), which through Embind forces the entire JS API to become async. If you need the hosted service, call the SpiceQL REST API (`https://astrogeology.usgs.gov/apis/spiceql/latest/`) directly from JavaScript with `fetch()` and use the WASM module only for local-kernel work (`useWeb:false`).

### Testing

The JS bindings have a test suite that runs with Node's built-in test runner (no extra dependencies). After building:

```bash
npm test
```

See [bindings/wasm/tests/README.md](bindings/wasm/tests/README.md) for details.

## Memoization Header Library 

SpiceQL has a simple memoization header only library at `Spiceql/include/memo.h`. This can cache function results on disk using a binary archive format mapped using a combined hash of a function ID and it's input parameters. 

TLDR 
```C++
#include "memo.h"

int func(int) { ... }
memoization::disk c("cache_path");

// use case 1: wrap function call
// (function ID, the function to wrap and then params
int result1 = c("func_id", func, 3);

// use case 2: wrap function
// (cache object, function ID, function)
auto func_memoed = memoization::make_memoized(c, "func_id", func);
int result2 = func_memoed(3);

assert(result1 == result2);
```

## How to Pull a Release
1. Create a branch with the new version name (e.g., `1.0`)
2. Update the version info in following files:
  - `code.json` - Append to the metadata with the updated version info
  - `CMakeLists.txt` - Update the project `VERSION` value
  - `CHANGELOG.md` - Create a new section with the version number, date, and changes made in the upcoming release
  - `docs/conf.py` - Update the version
  - `recipe/meta.yaml` - Update the package version
3. Tag a release candidate from the version branch
