package src;

import src.game.Game;
import src.game.config.Config;

public class Run {
    public static void main(String[] args) {
        Config cfg = Config.generate();

        Game game = new Game(cfg);
        game.run();
        game.end();
    }
}
