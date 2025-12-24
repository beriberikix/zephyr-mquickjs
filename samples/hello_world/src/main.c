#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <string.h>
#include "mquickjs.h"

static uint8_t js_mem[8192];

static JSValue js_print(JSContext *ctx, JSValue *this_val, int argc, JSValue *argv) {
    const char *str;
    for (int i = 0; i < argc; i++) {
        if (i != 0) printk(" ");
        str = JS_ToCString(ctx, argv[i]);
        if (!str) return JS_EXCEPTION;
        printk("%s", str);
        JS_FreeCString(ctx, str);
    }
    printk("\n");
    return JS_UNDEFINED;
}

void main(void) {
    printk("--- mquickjs Sample Start ---\n");

    JSContext *ctx = JS_NewContext(js_mem, sizeof(js_mem), &js_stdlib);
    if (!ctx) {
        printk("Failed to create context.\n");
        return;
    }

    // Register 'print'
    JSValue global_obj = JS_GetGlobalObject(ctx);
    JS_SetPropertyStr(ctx, global_obj, "print",
                      JS_NewCFunction(ctx, js_print, "print", 1));
    JS_FreeValue(ctx, global_obj);

    // Run Script
    const char *code = "print('Hello from Javascript!'); var x = 10; print('x * 2 =', x * 2);";
    JSValue ret = JS_Eval(ctx, code, strlen(code), "<input>", 0);

    if (JS_IsException(ret)) {
        printk("JS Error\n");
    }

    JS_FreeValue(ctx, ret);
    JS_FreeContext(ctx);
    printk("--- mquickjs Sample End ---\n");
}
