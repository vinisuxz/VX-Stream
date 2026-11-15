#ifndef VXSTREAM_UI_H
#define VXSTREAM_UI_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    VX_LANG_PT = 0,
    VX_LANG_EN = 1
} VxLanguage;

typedef enum {
    VX_PAGE_HOME = 0,
    VX_PAGE_MOVIES,
    VX_PAGE_SERIES,
    VX_PAGE_ANIME,
    VX_PAGE_SEARCH,
    VX_PAGE_SETTINGS,
    VX_PAGE_COUNT
} VxPage;

typedef struct {
    VxLanguage language;
    VxPage page;
    unsigned selected;
    bool page_open;
} VxUiState;

void vx_ui_draw(const VxUiState *state, uint32_t width, uint32_t height);

#endif
