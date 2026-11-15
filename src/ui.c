#include "ui.h"

#include <stddef.h>
#include "xsdk/text.h"

#define WHITE       0xFFF3F7FFu
#define MUTED       0xFF9BAFCBu
#define BLUE        0xFF39A0FFu
#define DEEP_BLUE   0xFF10294Au
#define ACCENT      0xFF62B5FFu

static const char *const labels_pt[VX_PAGE_COUNT] = {
    "Inicio", "Filmes", "Series", "Animes", "Pesquisar", "Configuracoes"
};
static const char *const labels_en[VX_PAGE_COUNT] = {
    "Home", "Movies", "Series", "Anime", "Search", "Settings"
};

static const char *const hints_pt =
    "A: selecionar    LB/RB: idioma    BACK: sair";
static const char *const hints_en =
    "A: select    LB/RB: language    BACK: exit";

void vx_ui_draw(const VxUiState *state, uint32_t width, uint32_t height)
{
    (void)height;
    const char *const *labels =
        state->language == VX_LANG_PT ? labels_pt : labels_en;

    /* The GPU target is cleared by main.c. Text is drawn over that frame. */
    xsdk_text_draw(64, 42, 3, BLUE, "VX STREAM");
    xsdk_text_draw(66, 112, 1, MUTED,
        state->language == VX_LANG_PT
            ? "FILMES  |  SERIES  |  ANIMES"
            : "MOVIES  |  SERIES  |  ANIME");

    xsdk_text_draw(66, 174, 2, WHITE,
        state->language == VX_LANG_PT
            ? "Seu entretenimento."
            : "Your entertainment.");

    for (unsigned i = 0; i < VX_PAGE_COUNT; ++i) {
        const int32_t y = 260 + (int32_t)i * 48;
        if (i == (unsigned)state->page) {
            xsdk_text_draw(68, y, 2, ACCENT, ">");
            xsdk_text_draw(104, y, 2, WHITE, labels[i]);
        } else {
            xsdk_text_draw(104, y, 2, MUTED, labels[i]);
        }
    }

    xsdk_text_draw(64, (int32_t)height - 58, 1, MUTED,
        state->language == VX_LANG_PT ? hints_pt : hints_en);

    /* Width is retained for later responsive card layout. */
    (void)width;
    (void)DEEP_BLUE;
}
