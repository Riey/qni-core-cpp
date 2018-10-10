#pragma once
#include "./qni-console.hpp"
#include "./qni-connector.hpp"

extern "C"
{

    std::shared_ptr<qni::Hub> *qni_hub_new(qni::program_start_t entry);
    void qni_hub_exit(std::shared_ptr<qni::Hub> *hub);
    void qni_hub_delete(std::shared_ptr<qni::Hub> *hub);

    void qni_print(qni::ConsoleContext *ctx, const char *text, size_t len);
    void qni_print_line(qni::ConsoleContext *ctx, const char *text, size_t len);
    void qni_new_line(qni::ConsoleContext *ctx);
    void qni_delete_line(qni::ConsoleContext *ctx, uint32_t count);

    void qni_set_font(qni::ConsoleContext *ctx, const char *font_family, size_t font_family_len, float font_size, qni::api::FontStyle font_style);
    void qni_set_text_align(qni::ConsoleContext *ctx, qni::api::TextAlign text_align);
    void qni_set_text_color(qni::ConsoleContext *ctx, uint32_t color);
    void qni_set_back_color(qni::ConsoleContext *ctx, uint32_t color);
    void qni_set_highlight_color(qni::ConsoleContext *ctx, uint32_t color);

    int32_t qni_wait_int(qni::ConsoleContext *ctx);
}
