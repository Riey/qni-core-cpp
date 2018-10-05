#include "internal/qni-deleter.hpp"

void qni_free_input_req(Qni__Api__InputRequest *req)
{
    switch (req->data_case)
    {
    case QNI__API__INPUT_REQUEST__DATA_STR__SELECT:
        for (size_t i = 0; i < req->str_select->n_data; i++)
        {
            delete req->str_select->data[i];
        }
        delete req->str_select;
        break;
    }

    delete req;
}

void qni_free_input_res(Qni__Api__InputResponse *res)
{
    switch (res->data_case)
    {
    case QNI__API__INPUT_RESPONSE__DATA_STR:
        delete res->str;
        break;
    }

    delete res;
}

void qni_free_print_dat(Qni__Api__ConsolePrintData *data)
{
    switch (data->data_case)
    {
    case QNI__API__CONSOLE_PRINT_DATA__DATA_PRINT:
        delete data->print;
        break;
    case QNI__API__CONSOLE_PRINT_DATA__DATA_PRINT__LINE:
        delete data->print_line;
        break;
    case QNI__API__CONSOLE_PRINT_DATA__DATA_PRINT__BUTTON:
        delete data->print_button->text;
        qni_free_input_res(data->print_button->value);
        break;
    }

    delete data;
}

void qni_free_font(Qni__Api__Font *font)
{
    delete font->font_family;
    delete font;
}

void qni_free_prog_req(Qni__Api__ProgramRequest *req)
{
    switch (req->data_case)
    {
    case QNI__API__PROGRAM_REQUEST__DATA_INPUT:
        qni_free_input_req(req->input);
        break;
    }

    delete req;
}

void qni_free_prog_res(Qni__Api__ProgramResponse *res)
{
    switch (res->data_case)
    {
    case QNI__API__PROGRAM_RESPONSE__DATA_ERR:
        qni_free_err(res->err);
        break;
    case QNI__API__PROGRAM_RESPONSE__DATA_OK__SHARE__STATE:
        delete res->ok_share_state;
        break;
    }

    delete res;
}

void qni_free_prog_com(Qni__Api__ProgramCommand *command)
{
    switch (command->data_case)
    {
    case QNI__API__PROGRAM_COMMAND__DATA_PRINT:
        qni_free_print_dat(command->print);
        break;
    case QNI__API__PROGRAM_COMMAND__DATA_UPDATE__SETTING:
        qni_free_console_setting(command->update_setting);
        break;
    }

    delete command;
}

void qni_free_console_res(Qni__Api__ConsoleResponse *res)
{
    switch (res->data_case)
    {
    case QNI__API__CONSOLE_RESPONSE__DATA_OK__INPUT:
        switch (res->ok_input->data_case)
        {
        case QNI__API__INPUT_RESPONSE__DATA_STR:
            delete res->ok_input->str;
            break;
        }
        break;
    case QNI__API__CONSOLE_RESPONSE__DATA_ERR:
        qni_free_err(res->err);
        break;
    }

    delete res;
}

void qni_free_console_setting(Qni__Api__ConsoleSettingItem *setting)
{
    switch (setting->data_case)
    {
    case QNI__API__CONSOLE_SETTING_ITEM__DATA_FONT:
        qni_free_font(setting->font);
        break;
    }

    delete setting;
}

void qni_free_err(Qni__Api__ErrorResponse *err)
{
    delete err->reason;
    delete err;
}
