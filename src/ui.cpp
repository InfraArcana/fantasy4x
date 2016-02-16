#include "ui.hpp"

#include "state.hpp"

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
Button::Button(const std::string text) :
    Ui_Element  (P(), P(cell_px_w * 3, cell_px_h)),
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
Popup::Popup(const std::string title,
             const std::string text,
             std::vector< std::unique_ptr<Button> >& buttons) :
    Ui_Element  (P(scr_px_w_half, scr_px_h_half), P(cell_px_w * 12, cell_px_h * 6)),
    title_      (title),
    text_       (text)
{
    const Rect      a           = area();
    const int       w           = a.p1.x - a.p0.x + 1;
    const size_t    NR_BTNS     = buttons.size();
    const int       step_size   = w / NR_BTNS;

    P btn_p(a.p0.x + (step_size / 2), a.p1.y - cell_px_h);

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

    io::draw_text(text_,
                  P(a.p0.x, a.p0.y + cell_px_h),
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
