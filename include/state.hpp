#ifndef STATE_HPP
#define STATE_HPP

#include "ui.hpp"

#include <vector>
#include <memory>

//-----------------------------------------------------------------------------
// By default, a state only calls rendering and input on its UI elements.
// To add more functionality, provide the state with a state implementation.
//-----------------------------------------------------------------------------

class State_Impl
{
public:
    State_Impl() {}

    virtual ~State_Impl() {}

    virtual void render() const {}

    virtual void on_input(const Input_Data& input)
    {
        (void)input;
    }

    virtual void on_pushed() {}

    virtual void on_popped() {}
};

class Main_Menu_State : public State_Impl
{
public:
    Main_Menu_State() {}

    ~Main_Menu_State() {}

    void render() const override;

    void on_input(const Input_Data& input) override;

    void on_pushed() override;
};

class Map_State : public State_Impl
{
public:
    Map_State() {}

    ~Map_State() {}

    void render() const override;

    void on_input(const Input_Data& input) override;

    void on_pushed() override;
};

class State final
{
public:
    State(std::unique_ptr<State_Impl> state_impl) :
        state_impl_     (std::move(state_impl)),
        ui_elements_    (),
        is_rendering_   (true) {}

    State() :
        State(nullptr) {}

    ~State() {}

    void render() const;

    void on_input(const Input_Data& input);

    void on_pushed();

    void on_popped();

    void add_ui_element(std::unique_ptr<Ui_Element> element);

    void pause_rendering()
    {
        is_rendering_ = false;
    }

    void resume_rendering()
    {
        is_rendering_ = true;
    }

private:
    std::unique_ptr<State_Impl> state_impl_;

    std::vector< std::unique_ptr<Ui_Element> > ui_elements_;

    bool is_rendering_;
};

namespace states
{

void init();

void cleanup();

void render();

void handle_input(const Input_Data& input);

void push_state(std::unique_ptr<State> state);

void pop_state();

bool is_cur_state(const State* const state);

void pause_rendering_prev_state();

} // states

#endif // STATE_HPP
