# Only build if the Kconfig option is enabled
if(CONFIG_MQUICKJS)

    zephyr_library()

    # Sources relative to this root file
    zephyr_library_sources(
        mquickjs/mquickjs.c
        mquickjs/cutils.c
        mquickjs/mqjs_stdlib.c
    )

    # Conditionally compile the internal math library
    # If we are NOT using the hardware FPU, we likely need the internal libm
    if(NOT CONFIG_MQUICKJS_USE_FPU)
        zephyr_library_sources(mquickjs/libm.c)
    endif()

    zephyr_include_directories(mquickjs)

endif()