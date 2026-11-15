#include "ui.h"

#include "xsdk/text.h"

#define WHITE       0xFFF3F7FFu
#define MUTED       0xFF9BAFCBu
#define BLUE        0xFF39A0FFu
#define ACCENT      0xFF62B5FFu

static const char *const labels_pt[VX_PAGE_COUNT] = {
    "Inicio", "Filmes", "Series", "Animes", "Pesquisar", "Configuracoes"
};
static const char *const labels_en[VX_PAGE_COUNT] = {
    "Home", "Movies", "Series", "Anime", "Search", "Settings"
};

static void draw_home(const VxUiState *state, uint32_t height)
{
    const char *const *labels =
        state->language == VX_LANG_PT ? labels_pt : labels_en;

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
        state->language == VX_LANG_PT
            ? "A: abrir    LB/RB: idioma    BACK: sair"
            : "A: open    LB/RB: language    BACK: exit");
}

static void draw_section(const VxUiState *state, uint32_t height)
{
    const char *title = "";
    const char *message = "";
    const char *hint = "";

    if (state->language == VX_LANG_PT) {
        switch (state->page) {
        case VX_PAGE_HOME:
            title = "Inicio";
            message = "Bem-vindo ao VX Stream.";
            break;
        case VX_PAGE_MOVIES:
            title = "Filmes";
            message = "O catalogo de filmes sera conectado na proxima etapa.";
            break;
        case VX_PAGE_SERIES:
            title = "Series";
            message = "O catalogo de series sera conectado na proxima etapa.";
            break;
        case VX_PAGE_ANIME:
            title = "Animes";
            message = "O catalogo de animes sera conectado na proxima etapa.";
            break;
        case VX_PAGE_SEARCH:
            title = "Pesquisar";
            message = "A busca ainda sera implementada.";
            break;
        case VX_PAGE_SETTINGS:
            title = "Configuracoes";
            message = "Idioma: Portugues";
            break;
        default:
            title = "VX Stream";
            message = "Opcao indisponivel.";
            break;
        }
        hint = "B: voltar ao menu    LB/RB: alterar idioma    BACK: sair";
    } else {
        switch (state->page) {
        case VX_PAGE_HOME:
            title = "Home";
            message = "Welcome to VX Stream.";
            break;
        case VX_PAGE_MOVIES:
            title = "Movies";
            message = "The movie catalog will be connected in the next step.";
            break;
        case VX_PAGE_SERIES:
            title = "Series";
            message = "The series catalog will be connected in the next step.";
            break;
        case VX_PAGE_ANIME:
            title = "Anime";
            message = "The anime catalog will be connected in the next step.";
            break;
        case VX_PAGE_SEARCH:
            title = "Search";
            message = "Search will be implemented in a later step.";
            break;
        case VX_PAGE_SETTINGS:
            title = "Settings";
            message = "Language: English";
            break;
        default:
            title = "VX Stream";
            message = "Unavailable option.";
            break;
        }
        hint = "B: back to menu    LB/RB: change language    BACK: exit";
    }

    xsdk_text_draw(64, 42, 3, BLUE, "VX STREAM");
    xsdk_text_draw(66, 150, 2, ACCENT, title);
    xsdk_text_draw(66, 230, 1, WHITE, message);
    xsdk_text_draw(64, (int32_t)height - 58, 1, MUTED, hint);
}

void vx_ui_draw(const VxUiState *state, uint32_t width, uint32_t height)
{
    (void)width;
    if (state->page_open)
        draw_section(state, height);
    else
        draw_home(state, height);
}
