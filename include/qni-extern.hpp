#pragma once
#include "./qni.hpp"
#include "./qni-connector.hpp"

extern "C"
{
    int qni_need_exit(const qni::ConsoleContext *ctx);
    void qni_set_exit(qni::ConsoleContext *ctx);

    qni::ConsoleContext *qni_console_ctx_new();
    void qni_console_ctx_delete(qni::ConsoleContext *ctx);

    qni::connector::ConnectorContext *qni_connector_ctx_new(qni::ConsoleContext *console_ctx);
    void qni_connector_ctx_delete(qni::connector::ConnectorContext *connector_ctx);

    void qni_print(qni::ConsoleContext *ctx, const char *text, size_t len);
    void qni_print_line(qni::ConsoleContext *ctx, const char *text, size_t len);
    void qni_new_line(qni::ConsoleContext *ctx);
    void qni_set_font(qni::ConsoleContext *ctx, const char *font_family, size_t font_family_len, float font_size, qni::api::FontStyle font_style);
    void qni_set_text_align(qni::ConsoleContext *ctx, qni::api::TextAlign text_align);
    void qni_set_text_color(qni::ConsoleContext *ctx, uint32_t color);
    void qni_set_back_color(qni::ConsoleContext *ctx, uint32_t color);
    void qni_set_highlight_color(qni::ConsoleContext *ctx, uint32_t color);
}
