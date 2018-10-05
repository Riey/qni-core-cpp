// #include "qni-extern.hpp"

// #include <cstring>

// using namespace qni;
// using namespace qni::connector;

// int qni_need_exit(const qni::ConsoleContext *ctx)
// {
//     return ctx->need_exit();
// }

// void qni_set_exit(qni::ConsoleContext *ctx)
// {
//     ctx->set_exit();
// }

// qni::ConsoleContext *qni_console_ctx_new()
// {
//     return new ConsoleContext();
// }

// void qni_console_ctx_delete(qni::ConsoleContext *ctx)
// {
//     delete ctx;
// }

// qni::connector::ConnectorContext *qni_connector_ctx_new(qni::ConsoleContext *console_ctx)
// {
//     return new ConnectorContext(console_ctx);
// }

// void qni_connector_ctx_delete(qni::connector::ConnectorContext *connector_ctx)
// {
//     delete connector_ctx;
// }

// void qni_print(qni::ConsoleContext *ctx, const char *text, size_t len)
// {
//     auto print = new Qni__Api__ConsolePrintData();
//     qni__api__console_print_data__init(print);
//     print->data_case = QNI__API__CONSOLE_PRINT_DATA__DATA_PRINT;
//     print->print = new char[len];

//     memcpy(print->print, text, len);

//     auto com = new Qni__Api__ProgramCommand();
//     qni__api__program_command__init(com);
//     com->data_case = QNI__API__PROGRAM_COMMAND__DATA_PRINT;
//     com->print = print;

//     ctx->append_command(com);
// }

// void qni_print_line(qni::ConsoleContext *ctx, const char *text, size_t len);
// void qni_new_line(qni::ConsoleContext *ctx);
// void qni_set_font(qni::ConsoleContext *ctx, const char *font_family, size_t font_family_len, float font_size, Qni__Api__FontStyle font_style);
// void qni_set_text_align(qni::ConsoleContext *ctx, Qni__Api__TextAlign text_align);
// void qni_set_text_color(qni::ConsoleContext *ctx, uint32_t color);
// void qni_set_back_color(qni::ConsoleContext *ctx, uint32_t color);
// void qni_set_highlight_color(qni::ConsoleContext *ctx, uint32_t color);
