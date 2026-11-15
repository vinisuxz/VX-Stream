#include <stdbool.h>
#include <stdint.h>

#include "ui.h"
#include "xsdk/gpu.h"
#include "xsdk/kernel.h"
#include "xsdk/log.h"
#include "xsdk/present.h"
#include "xsdk/splash.h"
#include "xsdk/text.h"

enum {
    VX_SPLASH_MS = 1200,
    VX_BUFFERS = 2,
    VX_SWAP_INTERVAL = 1,
    VX_BEGIN_TIMEOUT_MS = 5000,
    VX_CLEAR_ARGB = 0xFF07111Fu
};

static void handle_input(VxUiState *ui, const INPUT_GAMEPAD *pad,
                         uint16_t previous_buttons)
{
    const uint16_t pressed =
        (uint16_t)(pad->buttons & (uint16_t)~previous_buttons);

    /* Language can be changed from the menu or any opened page. */
    if (pressed & (INPUT_GAMEPAD_LEFT_SHOULDER | INPUT_GAMEPAD_RIGHT_SHOULDER))
        ui->language = ui->language == VX_LANG_PT ? VX_LANG_EN : VX_LANG_PT;

    if (ui->page_open) {
        /* B returns from the selected section to the home menu. */
        if (pressed & INPUT_GAMEPAD_B) {
            ui->page_open = false;
            ui->page = VX_PAGE_HOME;
        }
        return;
    }

    if (pressed & INPUT_GAMEPAD_DPAD_UP) {
        ui->page = ui->page == VX_PAGE_HOME
            ? (VxPage)(VX_PAGE_COUNT - 1)
            : (VxPage)(ui->page - 1);
    } else if (pressed & INPUT_GAMEPAD_DPAD_DOWN) {
        ui->page = (VxPage)(((unsigned)ui->page + 1u) % VX_PAGE_COUNT);
    }

    /* A opens the highlighted section. */
    if (pressed & INPUT_GAMEPAD_A)
        ui->page_open = true;
}

int main(void)
{
    VxUiState ui = { VX_LANG_PT, VX_PAGE_HOME, 0, false };
    xsdk_log_write("VX Stream: starting interface");
    uint16_t previous_buttons = 0;

    NTSTATUS status = xsdk_splash_show(VX_SPLASH_MS);
    if (!NT_SUCCESS(status))
        xsdk_log_write("VX Stream: splash returned 0x%08X", (unsigned)status);

    status = xsdk_gpu_open();
    if (!NT_SUCCESS(status)) {
        xsdk_log_write("VX Stream: xsdk_gpu_open failed: 0x%08X", (unsigned)status);
        return 1;
    }

    status = xsdk_text_open();
    if (!NT_SUCCESS(status)) {
        xsdk_log_write("VX Stream: xsdk_text_open failed: 0x%08X", (unsigned)status);
        (void)xsdk_gpu_close();
        return 1;
    }

    uint32_t width = 0, height = 0;
    status = xsdk_present_open(XSDK_DISPLAY_720P, VX_BUFFERS, VX_SWAP_INTERVAL,
                               &width, &height);
    if (!NT_SUCCESS(status)) {
        xsdk_log_write("VX Stream: xsdk_present_open failed: 0x%08X", (unsigned)status);
        xsdk_text_close();
        (void)xsdk_gpu_close();
        return 1;
    }

    xsdk_log_write("VX Stream: display %ux%u", (unsigned)width, (unsigned)height);

    for (;;) {
        INPUT_STATE input = { 0 };
        if (XamInputGetState(0, 0, &input) != ERROR_SUCCESS)
            input = (INPUT_STATE){ 0 };

        if (input.gamepad.buttons & INPUT_GAMEPAD_BACK)
            break;

        handle_input(&ui, &input.gamepad, previous_buttons);
        previous_buttons = input.gamepad.buttons;

        uint32_t address = 0;
        status = xsdk_present_begin(&address, VX_BEGIN_TIMEOUT_MS);
        if (!NT_SUCCESS(status)) {
            xsdk_log_write("VX Stream: present_begin failed: 0x%08X", (unsigned)status);
            break;
        }

        xsdk_gpu_set_target(width, height);
        vx_ui_draw(&ui, width, height);
        xsdk_gpu_resolve(address, width, height, VX_CLEAR_ARGB);
        xsdk_present_end();
    }

    xsdk_present_close();
    xsdk_text_close();
    status = xsdk_gpu_close();
    if (!NT_SUCCESS(status))
        xsdk_log_write("VX Stream: gpu_close failed: 0x%08X", (unsigned)status);

    xsdk_log_write("VX Stream: closed");
    return 0;
}
