#include "state.hpp"

#include "io.hpp"

//-----------------------------------------------------------------------------
// State implementations
//-----------------------------------------------------------------------------
void Main_Menu_State::render() const
{
    io::draw_text("This is the main menu",
                  P(0, 0),
                  clr_white_high,
                  clr_black,
                  X_Align::left,
                  Y_Align::top);
}

void Main_Menu_State::on_input(const Input_Data& input)
{
    if (input.key == 'n')
    {
        auto map_state  = std::make_unique<Map_State>();
        auto state      = std::make_unique<State>(std::move(map_state));
        states::push_state(std::move(state));
    }
}

void Main_Menu_State::on_pushed()
{
    std::vector< std::unique_ptr<Button> > buttons;

    buttons.push_back(std::make_unique<Button>("Continue", Button_Type::small));

    auto popup = std::make_unique<Popup>("Hello", "This is a game.", buttons);

    auto state = std::make_unique<State>();

    state->add_ui_element(std::move(popup));

    states::push_state(std::move(state));
}

void Map_State::render() const
{
    io::draw_text("This is the map",
                  P(io::scr_px_mid().x, 0),
                  clr_green_lgt,
                  clr_black,
                  X_Align::center,
                  Y_Align::top);
}

void Map_State::on_input(const Input_Data& input)
{
    if (input.key == 'b')
    {
        states::pop_state();
    }
}

void Map_State::on_pushed()
{
    states::pause_rendering_prev_state();
}

//-----------------------------------------------------------------------------
// State
//-----------------------------------------------------------------------------
void State::render() const
{
    if (!is_rendering_)
    {
        return;
    }

    if (state_impl_)
    {
        state_impl_->render();
    }

    for (const auto& element : ui_elements_)
    {
        element->render();
    }

}

void State::on_input(const Input_Data& input)
{
    if (state_impl_)
    {
        state_impl_->on_input(input);
    }

    const State* const state = this;

    if (!states::is_cur_state(state))
    {
        return;
    }

    for (const auto& element : ui_elements_)
    {
        element->on_input(input);

        if (!states::is_cur_state(state))
        {
            return;
        }
    }
}

void State::on_pushed()
{
    TRACE_FUNC_BEGIN;

    if (state_impl_)
    {
        state_impl_->on_pushed();
    }

    TRACE_FUNC_END;
}

void State::on_popped()
{
    TRACE_FUNC_BEGIN;

    if (state_impl_)
    {
        state_impl_->on_popped();
    }

    TRACE_FUNC_END;
}

void State::add_ui_element(std::unique_ptr<Ui_Element> element)
{
    ui_elements_.push_back(std::move(element));
}

//-----------------------------------------------------------------------------
// State keeping
//-----------------------------------------------------------------------------
namespace states
{

namespace
{

std::vector< std::unique_ptr<State> > states_;

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;

    cleanup();

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    states_.resize(0);

    TRACE_FUNC_END;
}

void render()
{
    for (const auto& state : states_)
    {
        state->render();
    }
}

void handle_input(const Input_Data& input)
{
    states_.back()->on_input(input);
}

void push_state(std::unique_ptr<State> state)
{
    TRACE_FUNC_BEGIN;

    states_.push_back(std::move(state));
    states_.back()->on_pushed();

    TRACE_FUNC_END;
}

void pop_state()
{
    TRACE_FUNC_BEGIN;

    if (!states_.empty())
    {
        states_.back()->on_popped();
        states_.pop_back();
    }

    if (!states_.empty())
    {
        states_.back()->resume_rendering();
    }

    TRACE_FUNC_END;
}

bool is_cur_state(const State* const state)
{
    if (states_.empty())
    {
        return false;
    }

    return state == states_.back().get();
}

void pause_rendering_prev_state()
{
    TRACE_FUNC_BEGIN;

    const size_t nr_states = states_.size();

    if (nr_states >= 2)
    {
        states_[nr_states - 2]->pause_rendering();
    }

    TRACE_FUNC_END;
}

} // states
