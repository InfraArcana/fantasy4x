extern crate sdl2;

use sdl2::pixels::Color;
use sdl2::keycode::KeyCode;

fn main()
{
    let mut sdl_context = sdl2::init().video().unwrap();

    let window = sdl_context.window("fantasy4x", 800, 600)
        .position_centered()
        .build()
        .unwrap();

    let mut renderer = window.renderer().build().unwrap();

    let mut drawer = renderer.drawer();

    drawer.set_draw_color(Color::RGB(0, 0, 0));
    drawer.clear();
    drawer.present();

    let mut running = true;

    while running {
        for event in sdl_context.event_pump().poll_iter() {
            use sdl2::event::Event;
            
            match event {
                Event::Quit {..} | Event::KeyDown { keycode: KeyCode::Escape, .. } => {
                    running = false
                },
                _ => {}
            }
        }

        // The rest of the game loop goes here...

    }

    println!("Bye!");
}
