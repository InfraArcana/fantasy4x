#include "ui.hpp"

#include "state.hpp"
#include "script.hpp"

namespace ui
{

P button_sizes[size_t(Button_Type::END)];

void init()
{
    TRACE_FUNC_BEGIN;

    // Init button sizes from script
    script::load("render.lua");

    button_sizes[size_t(Button_Type::small)]    = script::get_xy("button_size_s");
    button_sizes[size_t(Button_Type::medium)]   = script::get_xy("button_size_m");
    button_sizes[size_t(Button_Type::large)]    = script::get_xy("button_size_l");


    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    TRACE_FUNC_END;
}

} // ui

//-----------------------------------------------------------------------------
// UI element
//-----------------------------------------------------------------------------
Ui_Element::Ui_Element(const P& p, const P& size) :
    p_              (p),
    size_           (size),
    parent_element_ (nullptr),
    sub_elements_   () {}

//-----------------------------------------------------------------------------
// Button
//-----------------------------------------------------------------------------
// TODO: Size should probably be set up from script?
Button::Button(const std::string text, const Button_Type size) :
    Ui_Element  (P(), ui::button_sizes[size_t(size)]),
    text_       (text) {}

void Button::render() const
{
    io::draw_rect(area(), clr_gray);

    io::draw_text(text_, p_, clr_white_high, clr_black, X_Align::center, Y_Align::mid);
}

void Button::on_input(const Input_Data& input)
{
    if (input.mouse_btn == Mouse_Btn::left)
    {
        TRACE << "Click!" << std::endl;
    }
}

//-----------------------------------------------------------------------------
// Popup
//-----------------------------------------------------------------------------
// TODO: Size should probably be set up from script?
Popup::Popup(const std::string title,
             const std::string text,
             std::vector< std::unique_ptr<Button> >& buttons) :
    Ui_Element  (io::scr_px_mid(), P(400, 300)),
    title_      (title),
    text_       (text)
{
    const Rect      a           = area();
    const int       w           = a.p1.x - a.p0.x + 1;
    const size_t    NR_BTNS     = buttons.size();
    const int       step_size   = w / NR_BTNS;

    // TODO: This stuff should probably be set up from script?
    P btn_p(a.p0.x + (step_size / 2), a.p1.y - 24);

    for (auto& btn : buttons)
    {
        btn->set_pos(btn_p);
        sub_elements_.push_back(std::move(btn));
        btn_p.x += step_size;
    }
}

void Popup::render() const
{
    io::draw_rect(area(), clr_green);

    const Rect a = area();

    io::draw_text(title_,
                  P(p_.x, a.p0.y),
                  clr_white_high,
                  clr_black,
                  X_Align::center,
                  Y_Align::top);

    // TODO: Should probably be set up from script?
    const P text_p(a.p0.x, a.p0.y + 24);

    io::draw_text(text_,
                  text_p,
                  clr_white_high,
                  clr_black,
                  X_Align::left,
                  Y_Align::top);

    for (auto& element : sub_elements_)
    {
        element->render();
    }
}

void Popup::on_input(const Input_Data& input)
{
    for (auto& element : sub_elements_)
    {
        element->on_input(input);
    }
}
