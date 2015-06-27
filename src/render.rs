extern crate sdl2;

use sdl2::pixels::Color;

pub fn mk_window(sdl_ctx: &mut sdl2::Sdl) -> sdl2::video::Window
{
    return sdl_ctx.window("fantasy4x", 800, 600)
        .position_centered()
        .build()
        .unwrap();
}

pub fn process(drawer: &mut sdl2::render::RenderDrawer)
{
    drawer.set_draw_color(Color::RGB(0, 0, 0));
    drawer.clear();
    drawer.present();
}
