extern crate sdl2;

mod render;
mod input;

fn main()
{
    let mut sdl_ctx = sdl2::init().video().unwrap();

    let     sdl_win = render::mk_window(&mut sdl_ctx);

    let mut sdl_ren = sdl_win.renderer()
        .build()
        .unwrap();

    let mut sdl_drawer = sdl_ren.drawer();

    render::process(&mut sdl_drawer);

    let mut quit_game = false;

    while !quit_game
    {
        input::read(&mut sdl_ctx, &mut quit_game);

        // TODO: The rest of the game loop goes here...

    }

    println!("Bye!");
}
