#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include <memory>

#include "io.hpp"
#include "cmn_data.hpp"
#include "utils.hpp"

class Ui_Element
{
public:
    Ui_Element(const P& p, const P& size);

    virtual ~Ui_Element() {}

    virtual void render() const = 0;

    virtual void on_input(const Input_Data& input)
    {
        (void)input;
    }

    Rect area() const
    {
        const P size_half = size_ / 2;

        return Rect(p_ - size_half, p_ + size_half);
    }

    void set_pos(const P& p)
    {
        p_ = p;
    }

protected:
    P p_;
    P size_;

    Ui_Element* parent_element_;
    std::vector< std::unique_ptr<Ui_Element> > sub_elements_;
};

class Button : public Ui_Element
{
public:
    Button(const std::string text);

    void render() const override final;

    void on_input(const Input_Data& input) override final;

protected:
    const std::string text_;
};

class Popup : public Ui_Element
{
public:
    Popup(const std::string title,
          const std::string text,
          std::vector< std::unique_ptr<Button> >& buttons);

    void render() const override final;

    void on_input(const Input_Data& input) override final;

protected:
    const std::string title_;
    const std::string text_;
};

#endif // UI_H
