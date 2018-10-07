#include "qni-extern.hpp"

#include <cstring>

using namespace qni;
using namespace qni::connector;

std::shared_ptr<qni::Hub> *qni_hub_new(qni::program_start_t entry)
{
    return new std::shared_ptr<Hub>(new Hub(entry));
}

void qni_hub_exit(std::shared_ptr<qni::Hub> *hub)
{
    hub->get()->set_exit();
}

void qni_hub_delete(std::shared_ptr<qni::Hub> *hub)
{
    delete hub;
}

int qni_need_exit(const qni::ConsoleContext *ctx)
{
    return ctx->need_exit();
}

void qni_set_exit(qni::ConsoleContext *ctx)
{
    ctx->set_exit();
}

void qni_print(qni::ConsoleContext *ctx, const char *text, size_t len)
{
    auto com = std::make_unique<api::ProgramCommand>();
    com->mutable_print()->mutable_print()->assign(text, len);
    ctx->append_command(std::move(com));

    // auto print = new Qni__Api__ConsolePrintData();
    // qni__api__console_print_data__init(print);
    // print->data_case = QNI__API__CONSOLE_PRINT_DATA__DATA_PRINT;
    // print->print = new char[len];

    // memcpy(print->print, text, len);

    // auto com = new Qni__Api__ProgramCommand();
    // qni__api__program_command__init(com);
    // com->data_case = QNI__API__PROGRAM_COMMAND__DATA_PRINT;
    // com->print = print;

    // ctx->append_command(com);
}

void qni_print_line(qni::ConsoleContext *ctx, const char *text, size_t len)
{
    auto com = std::make_unique<api::ProgramCommand>();
    com->mutable_print()->mutable_print_line()->assign(text, len);
    ctx->append_command(std::move(com));
}

void qni_new_line(qni::ConsoleContext *ctx)
{
    auto com = std::make_unique<api::ProgramCommand>();
    com->mutable_print()->mutable_new_line();
    ctx->append_command(std::move(com));
}

void qni_delete_line(qni::ConsoleContext *ctx, uint32_t count)
{
    auto com = std::make_unique<api::ProgramCommand>();
    com->mutable_print()->set_delete_line(count);
    ctx->append_command(std::move(com));
}

void qni_set_font(qni::ConsoleContext *ctx, const char *font_family, size_t font_family_len, float font_size, api::FontStyle font_style)
{
    auto com = std::make_unique<api::ProgramCommand>();
    auto font = com->mutable_update_setting()->mutable_font();

    font->set_font_family(font_family, font_family_len);
    font->set_font_size(font_size);
    font->set_font_style(font_style);

    ctx->append_command(std::move(com));
}

void qni_set_text_align(qni::ConsoleContext *ctx, api::TextAlign text_align)
{
    auto com = std::make_unique<api::ProgramCommand>();
    com->mutable_update_setting()->set_text_align(text_align);
    ctx->append_command(std::move(com));
}

void qni_set_text_color(qni::ConsoleContext *ctx, uint32_t color)
{
    auto com = std::make_unique<api::ProgramCommand>();
    com->mutable_update_setting()->set_text_color(color);
    ctx->append_command(std::move(com));
}

void qni_set_back_color(qni::ConsoleContext *ctx, uint32_t color)
{
    auto com = std::make_unique<api::ProgramCommand>();
    com->mutable_update_setting()->set_back_color(color);
    ctx->append_command(std::move(com));
}

void qni_set_highlight_color(qni::ConsoleContext *ctx, uint32_t color)
{
    auto com = std::make_unique<api::ProgramCommand>();
    com->mutable_update_setting()->set_highlight_color(color);
    ctx->append_command(std::move(com));
}

int32_t qni_wait_int(qni::ConsoleContext *ctx)
{
    int32_t ret;

    api::ProgramMessage msg;

    auto req = msg.mutable_req();
    req->mutable_input()->mutable_int_();
    req->set_tag(ctx->next_req_tag());

    ctx->wait_console(msg, [&ret](api::ConsoleResponse const &res) {
        if (res.has_ok_input())
        {
            auto input = res.ok_input();

            if (input.data_case() == api::InputResponse::DataCase::kINT)
            {
                ret = input.int_();
                return true;
            }
        }

        return false;
    });

    return ret;
}
