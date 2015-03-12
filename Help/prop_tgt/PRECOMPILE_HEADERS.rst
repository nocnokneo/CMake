PRECOMPILE_HEADERS
------------------

List of header files to precompile.

Precompiling header files can speed up compilation by creating a partially
processed version of some header files, and then using that version during
compilations rather than repeatedly parsing the original headers.
List all header files that should be precompiled in the PRECOMPILE_HEADERS
property.   If precompiled headers are not supported by the platform, this
property will be ignored.
