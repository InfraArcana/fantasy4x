extern crate sdl2;

use sdl2::event::Event;
use sdl2::keycode::KeyCode;

pub fn read(sdl_ctx: &mut sdl2::Sdl, quit_game: &mut bool)
{
    for event in sdl_ctx.event_pump().poll_iter()
    {
        match event
        {
            Event::Quit {..} | Event::KeyDown
            {
                keycode: KeyCode::Escape, ..
            } =>
            {
                *quit_game = true;
            },
            _ => {}
        }
    } 
}
