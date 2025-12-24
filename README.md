# Zephyr mquickjs Module

A Zephyr module wrapper for the [mquickjs](https://github.com/bellard/mquickjs) Javascript Engine.

## Setup

1. Add this module to your `west.yml`:

   ```yaml
   - name: mquickjs
     url: https://github.com/YOUR_USERNAME/zephyr-mquickjs
     path: modules/lib/mquickjs
     revision: main
     submodules: true
   ```

2. Enable it in your `prj.conf`:

   ```properties
   CONFIG_MQUICKJS=y
   ```

## Testing

You can build the provided sample to verify the module works:

```bash
west build -b native_sim samples/hello_world
./build/zephyr/zephyr.exe
```
